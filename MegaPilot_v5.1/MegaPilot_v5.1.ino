#include <Adafruit_MCP23X17.h>
#include <EncButton.h>
#include <GyverOS.h>
#include <GyverIO.h>
#include <Ethernet.h>
#include <PubSubClient.h>

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
bool relayState[16] = {1};

bool script1 = false;
bool script2 = false;

bool checkScriptLed = true;

Button btns[16];  // Массив кнопок

// Network settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 12);
IPAddress server(192, 168, 1, 40);

EthernetClient ethClient;
PubSubClient client(ethClient);

// Callback function for MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  // Convert payload to a string
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  // Parse the topic and payload
  if (String(topic) == "home/relay") {
    int relay = message.toInt();
    outputState[relay] = !outputState[relay];
    mcp1.digitalWrite(OUTPUT_PINS1[relay], outputState[relay]);
  }
}

bool reconnect(int attempts) {
  int attempt = 0;
  while (!client.connected() && attempt < attempts) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ArduinoClient")) {
      Serial.println("connected");
      client.publish("home/status", "Arduino connected");
      client.subscribe("home/relay");
      return true;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      attempt++;
    }
  }
  return false;
}

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
    btns[i].tick();
  }
  // Обработка на клик
  for (int i = 0; i < 16; ++i) {
    if (btns[i].click()) {
      outputState[i] = !outputState[i];
      mcp1.digitalWrite(OUTPUT_PINS1[i], outputState[i]);
      Serial.print("btns: ");
      Serial.print(i);
      Serial.print(" - ");
      Serial.println(outputState[i]);
    }
  }
 // Дверь подсобка
  if (btns[0].hold()) {
    relayState[0] = !relayState[0];
    mcp3.digitalWrite(OUTPUT_PINS3[0], relayState[0]);
    Serial.print("\t Function ");
    Serial.print(0);
    Serial.print(": ");
    Serial.println(!relayState[0]);
    delay(100);
    relayState[0] = !relayState[0];
    mcp3.digitalWrite(OUTPUT_PINS3[0], relayState[0]);
    Serial.print("\t Function ");
    Serial.print(0);
    Serial.print(": ");
    Serial.println(!relayState[0]);
    blinkLed(1);
  }
 // Пульт2
  if (btns[1].hold()) {
    relayState[1] = !relayState[1];
    mcp3.digitalWrite(OUTPUT_PINS3[1], relayState[1]);
    Serial.print("\t Function ");
    Serial.print(1);
    Serial.print(": ");
    Serial.println(!relayState[1]);
    blinkLed(2);
  }
  
// Сценарий 2
  if (btns[10].click()) {
    script2 = !script2;
    Serial.print("btns: Scenario 2 - ");
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
  if (btns[11].click()) {
    script1 = !script1;
    Serial.print("btns: Scenario 1 - ");
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
  Serial.println("Start MegaPilot_v5.1");

  mcp1.begin_I2C(addr1); 
  mcp2.begin_I2C(addr2); 
  mcp3.begin_I2C(addr3);

  for (uint8_t pin : OUTPUT_PINS1) mcp1.pinMode(pin, OUTPUT);
  for (uint8_t pin : OUTPUT_PINS3) mcp3.pinMode(pin, OUTPUT);
  for (uint8_t pin : INPUT_PINS) mcp2.pinMode(pin, INPUT_PULLUP);

  updateOutputs(OUTPUT_PINS1, mcp1, outputState);
  updateOutputs(OUTPUT_PINS3, mcp3, relayState);

  // Инициализация кнопок
  for (int i = 0; i < 16; ++i) {
    btns[i].init(INPUT_PINS[i]);
  }

  outputState[9] = 1; // Экран 

  blinkLed(5);

  Ethernet.begin(mac, ip);
  client.setServer(server, 1883);
  client.setCallback(callback);

  if (!reconnect(3)) {
    Serial.println("MQTT connection failed, running in standalone mode.");
    blinkLed(15);
  }
}

void loop() {
  OS.tick();
  if (client.connected()) {
    client.loop();
  }
}
