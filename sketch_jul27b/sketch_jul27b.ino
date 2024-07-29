#include <Adafruit_MCP23X17.h>
#include <EncButton.h>
#include <GyverOS.h>
#include <GyverIO.h>

GyverOS<2> OS;

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

bool buttonState[16];
bool outputState[16];
bool functionState[16];

bool script1 = false;
bool script2 = false;

bool checkScriptLed = true;

VirtButton btns[16];  // Массив кнопок

void printAllValues() {
  Serial.println("OUTPUT_PINS1:");
  printArray(OUTPUT_PINS1, 16);

  Serial.println("OUTPUT_PINS3:");
  printArray(OUTPUT_PINS3, 16);

  Serial.println("INPUT_PINS:");
  printArray(INPUT_PINS, 16);

  Serial.println("buttonState:");
  printArray(buttonState, 16);

  Serial.println("outputState:");
  printArray(outputState, 16);

  Serial.println("functionState:");
  printArray(functionState, 16);
}

template<typename T>
void printArray(const T* arr, size_t size) {
  for (size_t i = 0; i < size; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
}


void checkScript() {
  checkScriptLed = !checkScriptLed;
  mcp3.digitalWrite(OUTPUT_PINS3[7], checkScriptLed);
  Serial.println("OUTPUT_PIN23 - ");
  Serial.println(!checkScriptLed);
}

void updateOutputs1(const uint8_t* pins, bool* stateArray) {
  for (int i = 0; i < 16; i++) {
    mcp1.digitalWrite(pins[i], stateArray[i]);
    Serial.println("updateOutputs1");
    Serial.println(i);
  }
}

void updateOutputs2(const uint8_t* pins, bool* stateArray) {
  for (int i = 0; i < 16; i++) {
    mcp3.digitalWrite(pins[i], stateArray[i]);
    Serial.println("updateOutputs2");
    Serial.println(i);
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
    Serial.println("Лампочка");

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
  //printAllValues();
  // for (int i = 0; i < 16; i++) {
  //   btns[i].tick();
  //   // Serial.println("checkButtons");
  //   // Serial.println(i);
  // }
  
  // // Обработка на клик
  // for (int i = 0; i < 16; i++) {
  //   if (btns[i].click()) {
  //     outputState[i] = !outputState[i];
  //     mcp1.digitalWrite(OUTPUT_PINS1[i], outputState[i]);
  //     Serial.print("btn: ");
  //     Serial.print(i);
  //     Serial.print(" - ");
  //     Serial.println(outputState[i]);
  //   }
  // }
  
  // // Дверь подсобка
  // if (btns[0].hold()) {
  //   functionState[0] = !functionState[0];
  //   mcp3.digitalWrite(OUTPUT_PINS3[0], functionState[0]);
  //   Serial.print("\t Function ");
  //   Serial.print(0);
  //   Serial.print(": ");
  //   Serial.println(!functionState[0]);
  //   delay(100);
  //   functionState[0] = !functionState[0];
  //   mcp3.digitalWrite(OUTPUT_PINS3[0], functionState[0]);
  //   Serial.print("\t Function ");
  //   Serial.print(0);
  //   Serial.print(": ");
  //   Serial.println(!functionState[0]);
  //   blinkLed(1);
  // }
  
  // // Пульт2
  // if (btns[1].hold()) {
  //   functionState[1] = !functionState[1];
  //   mcp3.digitalWrite(OUTPUT_PINS3[1], functionState[1]);
  //   Serial.print("\t Function ");
  //   Serial.print(1);
  //   Serial.print(": ");
  //   Serial.println(!functionState[1]);
  //   blinkLed(2);
  // }
  
  // // Сценарий 2
  // if (btns[10].click()) {
  //   script2 = !script2;
  //   Serial.print("btn: Scenario 2 - ");
  //   Serial.println(script2 ? "ON" : "OFF");
  //   if (script2) {
  //     Serial.println("Scenario 2 (ON) started");
  //     checkScript();
  //     for (int i = 0; i < numElementsScenario2ON; i++) {
  //       int index = indicesScenario2ON[i]; // Получаем текущий индекс
  //       outputState[index] = 1; // Изменяем значение на 1
  //       Serial.print("OUTPUT_PIN[");
  //       Serial.print(index);
  //       Serial.println("] = 1");
  //       delay(500);
  //     }
  //     Serial.println("Scenario 2 (ON) finished");
  //     checkScript();
  //   } else {
  //     Serial.println("Scenario 2 (OFF) started");
  //     checkScript();
  //     for (int i = 0; i < numElementsScenarioOFF; i++) {
  //       int index = indicesScenarioOFF[i]; // Получаем текущий индекс
  //       outputState[index] = 0; // Изменяем значение на 0
  //       Serial.print("OUTPUT_PIN[");
  //       Serial.print(index);
  //       Serial.println("] = 0");
  //       delay(500);
  //     }
  //     Serial.println("Scenario 2 (OFF) finished");
  //     checkScript();
  //   }
  // }
  
  // // Сценарий 1
  // if (btns[11].click()) {
  //   script1 = !script1;
  //   Serial.print("btn: Scenario 1 - ");
  //   Serial.println(script1 ? "ON" : "OFF");

  //   if (script1) {
  //     Serial.println("Scenario 1 (ON) started");
  //     checkScript();
  //     for (int i = 0; i < numElementsScenario1ON; i++) {
  //       int index = indicesScenario1ON[i]; // Получаем текущий индекс
  //       outputState[index] = 1; // Изменяем значение на 1
  //       Serial.print("OUTPUT_PIN[");
  //       Serial.print(index);
  //       Serial.println("] = 1");
  //       delay(500);
  //     }
  //     Serial.println("Scenario 1 (ON) finished");
  //     checkScript();
  //   } else {
  //     Serial.println("Scenario 1 (OFF) started");
  //     checkScript();
  //     for (int i = 0; i < numElementsScenarioOFF; i++) {
  //       int index = indicesScenarioOFF[i]; // Получаем текущий индекс
  //       outputState[index] = 0; // Изменяем значение на 0
  //       Serial.print("OUTPUT_PIN[");
  //       Serial.print(index);
  //       Serial.println("] = 0");
  //       delay(500);
  //     }
  //     Serial.println("Scenario 1 (OFF) finished");
  //     checkScript();
  //   }
  // }
}

void setup() {
  Serial.begin(9600);
  // OS.attach(0, checkButtons, 50);
  // OS.attach(1, printAllValues, 3000);
  mcp1.begin_I2C(addr1); 
  mcp2.begin_I2C(addr2); 
  mcp3.begin_I2C(addr3);

  for (uint8_t pin : OUTPUT_PINS1) mcp1.pinMode(pin, OUTPUT);
  for (uint8_t pin : OUTPUT_PINS3) mcp3.pinMode(pin, OUTPUT);
  for (uint8_t pin : INPUT_PINS) mcp2.pinMode(pin, INPUT_PULLUP);

  for (int i = 0; i < 16; i++) { buttonState[i] = 0; }
  for (int i = 0; i < 16; i++) { functionState[i] = 1; }
  for (int i = 0; i < 16; i++) { outputState[i] = 0; }

  updateOutputs1(OUTPUT_PINS1, outputState);
  updateOutputs2(OUTPUT_PINS3, functionState);

  // Инициализация кнопок
  for (int i = 0; i < 16; i++) { 
    btns[i+1].tick(!mcp2.digitalRead(INPUT_PINS[i]));
  }

  outputState[9] = 0; // Экран 
  //blinkLed(5);
  Serial.println("Start MegaPilot_v5.0");
  printAllValues();
}

void loop() {
  for (int i = 0; i < 16; i++) { 
    btns[i+1].tick(!mcp2.digitalRead(INPUT_PINS[i]));
    // Обработка на клик
    if (btns[i+1].click()) {
      outputState[i] = !outputState[i];
      mcp1.digitalWrite(OUTPUT_PINS1[i], outputState[i]);
      Serial.print("btn: ");
      Serial.print(i);
      Serial.print(" - ");
      Serial.println(outputState[i]);
    }
    if (btns[1].hold()) {
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
    }
    if (btns[2].hold()) {
      functionState[1] = !functionState[1];
      mcp3.digitalWrite(OUTPUT_PINS3[1], functionState[1]);
      Serial.print("\t Function ");
      Serial.print(1);
      Serial.print(": ");
      Serial.println(!functionState[1]);
    }
    if (btns[11].click()) {
    script2 = !script2;
    Serial.print("btn: Scenario 2 - ");
    Serial.println(script2 ? "ON" : "OFF");
    if (script2) {
      Serial.println("Scenario 2 (ON) started");
      checkScript();
      for (int i = 0; i < numElementsScenario2ON; i++) {
        int index = indicesScenario2ON[i]; // Получаем текущий индекс
        outputState[index] = 1; // Изменяем значение на 1
        Serial.print("OUTPUT_PIN[");
        Serial.print(index);
        Serial.println("] = 1");
        delay(200);
      }
      Serial.println("Scenario 2 (ON) finished");
      checkScript();
    } else {
      Serial.println("Scenario 2 (OFF) started");
      checkScript();
      for (int i = 0; i < numElementsScenarioOFF; i++) {
        int index = indicesScenarioOFF[i]; // Получаем текущий индекс
        outputState[index] = 0; // Изменяем значение на 0
        Serial.print("OUTPUT_PIN[");
        Serial.print(index);
        Serial.println("] = 0");
        delay(200);
      }
      Serial.println("Scenario 2 (OFF) finished");
      checkScript();
    }
  }
  if (btns[12].click()) {
    script1 = !script1;
    Serial.print("btn: Scenario 1 - ");
    Serial.println(script1 ? "ON" : "OFF");

    if (script1) {
      Serial.println("Scenario 1 (ON) started");
      checkScript();
      for (int i = 0; i < numElementsScenario1ON; i++) {
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
      for (int i = 0; i < numElementsScenarioOFF; i++) {
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
  
}
