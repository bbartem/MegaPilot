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

const uint8_t scenario1ON[] = {0, 1, 2, 3, 4, 5, 6, 7, 14, 15, 8, 13};
const uint8_t scenario2ON[] = {0, 2, 3, 4, 6, 7};
const uint8_t scenarioOFF[] = {5, 6, 7, 0, 1, 2, 3, 4, 14, 15, 12, 13, 8};

int indicesScenario1ON[] = {0, 1, 2, 3, 4, 5, 6, 7, 14, 15, 8, 13}; // Сценарий включения Скрипта1
int indicesScenario2ON[] = {0, 2, 3, 4, 6, 7}; // Сценарий включения Скрипта2
int indicesScenarioOFF[] = {5, 6, 7, 0, 1, 2, 3, 4, 14, 15, 12, 13, 8}; // Сценарий выключения всего

bool buttonState[16];
bool outputState[16];
bool functionState[16];

bool script1 = false;
bool script2 = false;

bool checkScriptLed = true;

VirtButton btns[16];  // Массив кнопок

unsigned long previousMillis = 0; // Переменная для хранения времени
const unsigned long intervalHold0 = 100; // Интервал в миллисекундах (100 мс)
const unsigned long intervalClick = 500; // Интервал в миллисекундах (500 мс)

unsigned long blinkStartTime = 0;
int remainingBlinks = 0;
bool isBlinking = false;
bool ledState = true;
unsigned long blinkInterval = 200; // Интервал мигания в миллисекундах

void printAllValues() {
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

void sequentialToggle(const int* indices, int size, bool state, const uint8_t* outputPins) {
  checkScript();
  for (int i = 0; i < size; i++) {
    uint8_t pinIndex = indices[i];
    
    for (int j = 0; j < 16; j++) {
      if (OUTPUT_PINS1[j] == pinIndex) {
        outputState[j] = state;
        break;
      }
    }

    mcp1.digitalWrite(outputPins[i], state);
    Serial.print("Pin ");
    Serial.print(pinIndex);
    Serial.print(" ");
    Serial.print(state ? "ON" : "OFF");
    Serial.println();

    previousMillis = millis(); 
    while (millis() - previousMillis < intervalClick) { }
  }
  checkScript();
}


void checkScript() {
  checkScriptLed = !checkScriptLed;
  mcp3.digitalWrite(OUTPUT_PINS3[7], checkScriptLed);
  Serial.println("OUTPUT_PIN23 - ");
  Serial.println(!checkScriptLed);
}

void blinkLamp(int blinkCount) {
  remainingBlinks = blinkCount * 2;
  isBlinking = true;
  blinkStartTime = millis();
}

void updateOutputs1(const uint8_t* pins, bool* stateArray) {
  for (int i = 0; i < 16; i++) {
    mcp1.digitalWrite(pins[i], stateArray[i]);
    Serial.println("Инициализация_1 - Реле:");
    Serial.println(i);
  }
}

void updateOutputs2(const uint8_t* pins, bool* stateArray) {
  for (int i = 0; i < 16; i++) {
    mcp3.digitalWrite(pins[i], stateArray[i]);
    Serial.println("Инициализация_2 - Реле:");
    Serial.println(i);
  }
}

void setup() {
  Serial.begin(9600);
  mcp1.begin_I2C(addr1); 
  mcp2.begin_I2C(addr2); 
  mcp3.begin_I2C(addr3);

  for (uint8_t pin : OUTPUT_PINS1) mcp1.pinMode(pin, OUTPUT);
  for (uint8_t pin : OUTPUT_PINS3) mcp3.pinMode(pin, OUTPUT);
  for (uint8_t pin : INPUT_PINS) mcp2.pinMode(pin, INPUT_PULLUP);

  for (int i = 0; i < 16; i++) { buttonState[i] = 0; }
  for (int i = 0; i < 16; i++) { functionState[i] = 1; }
  for (int i = 0; i < 16; i++) { outputState[i] = 0; }

  outputState[9] = 0; // Экран 

  updateOutputs1(OUTPUT_PINS1, outputState);
  updateOutputs2(OUTPUT_PINS3, functionState);

  // Инициализация кнопок
  for (int i = 0; i < 16; i++) { 
    btns[i].tick(!mcp2.digitalRead(INPUT_PINS[i]));
  }

  Serial.println("Start MegaPilot_v5.0");
  blinkLamp(5);
  printAllValues();
}

void loop() {
  for (int i = 0; i < 16; i++) {
    btns[i].tick(!mcp2.digitalRead(INPUT_PINS[i]));
    if (i != 10 && i != 11) {
      // Обработка на клик
      if (btns[i].click()) {
        outputState[i] = !outputState[i];
        mcp1.digitalWrite(OUTPUT_PINS1[i], outputState[i]);
        Serial.print("btn: ");
        Serial.print(i);
        Serial.print(" - ");
        Serial.println(outputState[i]);
      }
    }
  }
  handleScenarioButton(10, scenario2ON, indicesScenario2ON, script2);
  handleScenarioButton(11, scenario1ON, indicesScenario1ON, script1);
  
  if (isBlinking && remainingBlinks > 0) {
    if (millis() - blinkStartTime >= blinkInterval) {
      blinkStartTime = millis();
      ledState = !ledState;
      mcp3.digitalWrite(OUTPUT_PINS3[7], ledState);
      remainingBlinks--;

      if (remainingBlinks == 0) {
        isBlinking = false;
        mcp3.digitalWrite(OUTPUT_PINS3[7], HIGH);
      }
    }
  }
  delay(20);
}

void handleScenarioButton(int btnIndex, const uint8_t* scenarioON, const int* indicesScenarioON, bool& script) {
  if (btns[btnIndex].hold()) {
    outputState[btnIndex] = !outputState[btnIndex];
    mcp1.digitalWrite(OUTPUT_PINS1[btnIndex], outputState[btnIndex]);
    Serial.print("btn: Scenario ");
    Serial.print(btnIndex - 9);
    Serial.print(" - ");
    Serial.println(script ? "OFF" : "ON");
    if (!script) {
      Serial.println("Scenario (ON) started");
      sequentialToggle(indicesScenarioON, sizeof(indicesScenarioON) / sizeof(indicesScenarioON[0]), 1, scenarioON);
      Serial.println("Scenario (ON) finished");
    } else {
      Serial.println("Scenario (OFF) started");
      sequentialToggle(indicesScenarioOFF, sizeof(indicesScenarioOFF) / sizeof(indicesScenarioOFF[0]), 0, scenarioOFF);
      Serial.println("Scenario (OFF) finished");
    }
    script = !script;
    delay(500); // Задержка для предотвращения зацикливания
  }
}
