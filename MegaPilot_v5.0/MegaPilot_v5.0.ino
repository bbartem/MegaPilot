#include <Adafruit_MCP23X17.h>
#include <EncButton.h>
#include <GyverOS.h>
#include <GyverIO.h>

GyverOS<1> OS;

Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
Adafruit_MCP23X17 mcp3;

#define addr1 0x24
#define addr2 0x22
#define addr3 0x23

const uint8_t OUTPUT_PINS1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
const uint8_t OUTPUT_PINS3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
const uint8_t INPUT_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

int indicesScenario1ON[] = {0, 1, 2, 3, 4, 5, 6, 7, 14, 15, 8, 13}; // Сценарий включения Скрипта1
int indicesScenario2ON[] = {0, 2, 3, 4, 6, 7}; // Сценарий включения Скрипта2
int indicesScenarioOFF[] = {5, 6, 7, 0, 1, 2, 3, 4, 14, 15, 12, 13, 8}; // Сценарий выключения всего

int numElementsScenario1ON = sizeof(indicesScenario1ON) / sizeof(indicesScenario1ON[0]);
int numElementsScenario2ON = sizeof(indicesScenario2ON) / sizeof(indicesScenario2ON[0]);
int numElementsScenarioOFF = sizeof(indicesScenarioOFF) / sizeof(indicesScenarioOFF[0]);

bool buttonState[16] = {0};
bool outputState[16] = {0};
bool functionState[16] = {1};

bool script1 = false;
bool script2 = false;

bool checkScriptLed = true;

EncButton<EB_TICK, VIRT_BTN> btn[16];

// EncButton<EB_TICK, VIRT_BTN> btn0;
// EncButton<EB_TICK, VIRT_BTN> btn1;
// EncButton<EB_TICK, VIRT_BTN> btn2;
// EncButton<EB_TICK, VIRT_BTN> btn3;
// EncButton<EB_TICK, VIRT_BTN> btn4;
// EncButton<EB_TICK, VIRT_BTN> btn5;
// EncButton<EB_TICK, VIRT_BTN> btn6;
// EncButton<EB_TICK, VIRT_BTN> btn7;
// EncButton<EB_TICK, VIRT_BTN> btn8;
// EncButton<EB_TICK, VIRT_BTN> btn9;
// EncButton<EB_TICK, VIRT_BTN> btn10;
// EncButton<EB_TICK, VIRT_BTN> btn11;
// EncButton<EB_TICK, VIRT_BTN> btn12;
// EncButton<EB_TICK, VIRT_BTN> btn13;
// EncButton<EB_TICK, VIRT_BTN> btn14;
// EncButton<EB_TICK, VIRT_BTN> btn15;

void checkScript() {
  checkScriptLed = !checkScriptLed;
  mcp3.digitalWrite(OUTPUT_PINS3[7], checkScriptLed);
  Serial.println("OUTPUT_PIN23 - ");
  Serial.println(!checkScriptLed);
}

void updateOutputs(const uint8_t* pins, Adafruit_MCP23X17 &mcp, bool* stateArray) {
  for (int i = 0; i < 16; ++i) {
    mcp.digitalWrite(pins[i], stateArray[i]);
  }
}

// Мигание светодиодом
void blinkLed(uint8_t times) {
  static uint32_t lastBlinkTime = 0;
  static uint8_t blinkCount = 0;
  static bool ledState = false;

  if (times == 0) return; // Нечего делать

  if (millis() - lastBlinkTime >= 500) { // 500 мс интервал
    lastBlinkTime = millis();
    ledState = !ledState;
    mcp3.digitalWrite(OUTPUT_PINS3[7], ledState);

    if (ledState == false) {
      blinkCount++;
      if (blinkCount >= times * 2) { // Учитываем включение и выключение
        blinkCount = 0;
        return; // Завершение мигания
      }
    }
  }
}

void checkButtons() {
  for (int i = 0; i < 16; ++i) {
    btn[i].tick(!mcp2.digitalRead(INPUT_PINS[i]));
  }
  
// Обработка на клик
  for (int i = 0; i < 16; ++i) {
    if (btn[i].click()) {
      outputState[i] = !outputState[i];
      mcp1.digitalWrite(OUTPUT_PINS1[i], outputState[i]);
      Serial.print("btn: ");
      Serial.print(i);
      Serial.print(" - ");
      Serial.println(outputState[i]);
    }
  }
 // Дверь подсобка
  if (btn[0].hold()) {
    functionState[0] = !functionState[0];
    mcp3.digitalWrite(OUTPUT_PINS3[0], functionState[0]);
    Serial.print("\t Function ");
    Serial.print(0);
    Serial.print(": ");
    Serial.println(!functionState[0]);
    delay(100);
    functionState[0] = !functionState[0];
    mcp3.digitalWrite(OUTPUT_PINS3[0], functionState[0]);
    Serial.print("\t Function ");
    Serial.print(0);
    Serial.print(": ");
    Serial.println(!functionState[0]);
    blinkLed(1);
  }
 // Пульт2
  if (btn[1].hold()) {
    functionState[1] = !functionState[1];
    mcp3.digitalWrite(OUTPUT_PINS3[1], functionState[1]);
    Serial.print("\t Function ");
    Serial.print(1);
    Serial.print(": ");
    Serial.println(!functionState[1]);
    blinkLed(2);
  }
  
// Сценарий 2
  if (btn[10].click()) {
    script2 = !script2;
    Serial.print("btn: Scenario 2 - ");
    Serial.println(script2 ? "ON" : "OFF");
    if (script2) {
      Serial.println("Scenario 2 (ON) started");
      checkScript();
      for (int i = 0; i < numElementsScenario2ON; ++i) {
        int index = indicesScenario2ON[i]; // Получаем текущий индекс
        outputState[index] = 1; // Изменяем значение на 1
        Serial.print("OUTPUT_PIN[");
        Serial.print(index);
        Serial.println("] = 1");
        delay(500);
      }
      Serial.println("Scenario 2 (ON) finished");
      checkScript();
    } else {
      Serial.println("Scenario 2 (OFF) started");
      checkScript();
      for (int i = 0; i < numElementsScenarioOFF; ++i) {
        int index = indicesScenarioOFF[i]; // Получаем текущий индекс
        outputState[index] = 0; // Изменяем значение на 0
        Serial.print("OUTPUT_PIN[");
        Serial.print(index);
        Serial.println("] = 0");
        delay(500);
      }
      Serial.println("Scenario 2 (OFF) finished");
      checkScript();
    }
  }
// Сценарий 1
  if (btn[11].click()) {
    script1 = !script1;
    Serial.print("btn: Scenario 1 - ");
    Serial.println(script1 ? "ON" : "OFF");

    if (script1) {
      Serial.println("Scenario 1 (ON) started");
      checkScript();
      for (int i = 0; i < numElementsScenario1ON; ++i) {
        int index = indicesScenario1ON[i]; // Получаем текущий индекс
        outputState[index] = 1; // Изменяем значение на 1
        Serial.print("OUTPUT_PIN[");
        Serial.print(index);
        Serial.println("] = 1");
        delay(500);
      }
      Serial.println("Scenario 1 (ON) finished");
      checkScript();
    } else {
      Serial.println("Scenario 1 (OFF) started");
      checkScript();
      for (int i = 0; i < numElementsScenarioOFF; ++i) {
        int index = indicesScenarioOFF[i]; // Получаем текущий индекс
        outputState[index] = 0; // Изменяем значение на 0
        Serial.print("OUTPUT_PIN[");
        Serial.print(index);
        Serial.println("] = 0");
        delay(500);
      }
      Serial.println("Scenario 1 (OFF) finished");
      checkScript();
    }
  }
}

void setup() {
  Serial.begin(9600);
  OS.attach(0, checkButtons, 50);
  Serial.println("Start MegaPilot_v5.0");

  mcp1.begin_I2C(addr1); 
  mcp2.begin_I2C(addr2); 
  mcp3.begin_I2C(addr3);

  for (uint8_t pin : OUTPUT_PINS1) mcp1.pinMode(pin, OUTPUT);
  for (uint8_t pin : OUTPUT_PINS3) mcp3.pinMode(pin, OUTPUT);
  for (uint8_t pin : INPUT_PINS) mcp2.pinMode(pin, INPUT_PULLUP);

  updateOutputs(OUTPUT_PINS1, mcp1, outputState);
  updateOutputs(OUTPUT_PINS3, mcp3, functionState);

  outputState[9] = 1; // Экран 

  blinkLed(5);
}

void loop() {
  OS.tick();
}
