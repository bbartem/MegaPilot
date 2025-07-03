#include <Adafruit_MCP23X17.h>
#include <EncButton.h>
#include <GyverOS.h>
#include <GyverIO.h>
#include <PubSubClient.h>
#include <Ethernet.h>

// MQTT настройки
const char* mqtt_server = "192.168.1.51";
const int mqtt_port = 1883;
const char* mqtt_client_id = "MegaPilot";

// Топики для каждого выхода
const char* outputTopics[] = {
  "outputState/Remote_1",
  "outputState/Camera",
  "outputState/Stage",
  "outputState/Microphones",
  "outputState/Switching",
  "outputState/Broadcast",
  "outputState/Monitors",
  "outputState/Portal",
  "outputState/Light(lectern)",
  "outputState/Screen",
  "outputState/Scenario_2",
  "outputState/Scenario_1",
  "outputState/Light(choir)",
  "outputState/Light(piano)",
  "outputState/Light(1)",
  "outputState/Light(2)"
};

// Топики для functionState
const char* functionTopics[] = {
  "functionState/Room",
  "functionState/Remote_2",
  "functionState/Null",
  "functionState/Balcon",
  "functionState/Null",
  "functionState/Null",
  "functionState/Null",
  "functionState/Led",
  "functionState/Null",
  "functionState/Null",
  "functionState/Null",
  "functionState/Null",
  "functionState/Null",
  "functionState/Null",
  "functionState/Null",
  "functionState/Null"
};

// MQTT и Ethernet клиенты
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
Adafruit_MCP23X17 mcp3;

#define addr1 0x24
#define addr2 0x22
#define addr3 0x23

const uint8_t OUTPUT_PINS1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
const uint8_t OUTPUT_PINS3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
const uint8_t INPUT_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

bool buttonState[16];
bool outputState[16];
bool functionState[16];

VirtButton btns[16];  // Массив кнопок

bool mqttEnabled = true; // Флаг доступности MQTT
unsigned long lastMqttAttempt = 0;
const unsigned long mqttRetryInterval = 30000; // 30 секунд между попытками переподключения
byte mqttAttemptCount = 0;
const byte maxMqttAttempts = 3; // Максимальное количество попыток подключения

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

// Функция обратного вызова для MQTT сообщений
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  if (!mqttEnabled) return;
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  // Преобразуем payload в строку
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';
  Serial.println(message);
  
  // Обработка outputState топиков
  for (int i = 0; i < 16; i++) {
    if (strcmp(topic, outputTopics[i]) == 0) {
      // Обновляем состояние выхода
      if (strcmp(message, "true") == 0 || strcmp(message, "1") == 0) {
        outputState[i] = true;
      } else if (strcmp(message, "false") == 0 || strcmp(message, "0") == 0) {
        outputState[i] = false;
      }
      
      // Применяем новое состояние к выходу
      mcp1.digitalWrite(OUTPUT_PINS1[i], outputState[i]);
      
      Serial.print("Output ");
      Serial.print(i);
      Serial.print(" set to ");
      Serial.println(outputState[i]);
      return;
    }
  }
  
  // Обработка functionState топиков
  for (int i = 0; i < 16; i++) {
    if (strcmp(topic, functionTopics[i]) == 0 && strcmp(functionTopics[i], "functionState/Null") != 0) {
      // Обновляем состояние функции
      if (strcmp(message, "true") == 0 || strcmp(message, "1") == 0) {
        functionState[i] = true;
      } else if (strcmp(message, "false") == 0 || strcmp(message, "0") == 0) {
        functionState[i] = false;
      }
      
      // Применяем новое состояние к выходу
      mcp3.digitalWrite(OUTPUT_PINS3[i], functionState[i]);
      
      Serial.print("Function ");
      Serial.print(i);
      Serial.print(" (");
      Serial.print(functionTopics[i]);
      Serial.print(") set to ");
      Serial.println(functionState[i]);
      return;
    }
  }
  
  Serial.println("Topic not recognized");
}

// Подключение к MQTT брокеру
void reconnectMQTT() {
  if (!mqttEnabled) return;
  
  if (mqttAttemptCount >= maxMqttAttempts) {
    if (mqttEnabled) {
      mqttEnabled = false;
      Serial.println("MQTT disabled after 3 failed attempts. System will continue to work without MQTT.");
      mcp3.digitalWrite(OUTPUT_PINS3[7], false);
    }
    return;
  }

  if (millis() - lastMqttAttempt < mqttRetryInterval && lastMqttAttempt != 0) {
    return;
  }

  lastMqttAttempt = millis();
  mqttAttemptCount++;
  
  Serial.print("Attempting MQTT connection (attempt ");
  Serial.print(mqttAttemptCount);
  Serial.print("/");
  Serial.print(maxMqttAttempts);
  Serial.println(")...");
  
  if (mqttClient.connect(mqtt_client_id)) {
    Serial.println("connected");
    mqttAttemptCount = 0; // Сброс счетчика попыток при успешном подключении
    
    // Подписываемся на все outputState топики
    for (int i = 0; i < 16; i++) {
      mqttClient.subscribe(outputTopics[i]);
      Serial.print("Subscribed to ");
      Serial.println(outputTopics[i]);
    }
    
    // Подписываемся на все functionState топики (кроме Null)
    for (int i = 0; i < 16; i++) {
      if (strcmp(functionTopics[i], "functionState/Null") != 0) {
        mqttClient.subscribe(functionTopics[i]);
        Serial.print("Subscribed to ");
        Serial.println(functionTopics[i]);
      }
    }
  } else {
    Serial.print("failed, rc=");
    Serial.print(mqttClient.state());
    Serial.println(" try again later");
    
    if (mqttAttemptCount >= maxMqttAttempts) {
      mqttEnabled = false;
      Serial.println("MQTT disabled after 3 failed attempts. System will continue to work without MQTT.");
    }
  }
}

// Инициализация Ethernet
void initEthernet() {
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  
  Serial.println("Initializing Ethernet...");
  if (Ethernet.begin(mac)) {
    Serial.print("Ethernet IP: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println("Failed to configure Ethernet using DHCP");
    while (1) {
      delay(1000);
      Serial.println("Retrying Ethernet connection...");
      if (Ethernet.begin(mac)) break;
    }
  }
}

void setup() {
  Serial.begin(9600);
  
  // Инициализация MCP
  mcp1.begin_I2C(addr1); 
  mcp2.begin_I2C(addr2); 
  mcp3.begin_I2C(addr3);

  for (uint8_t pin : OUTPUT_PINS1) mcp1.pinMode(pin, OUTPUT);
  for (uint8_t pin : OUTPUT_PINS3) mcp3.pinMode(pin, OUTPUT);
  for (uint8_t pin : INPUT_PINS) mcp2.pinMode(pin, INPUT_PULLUP);

  for (int i = 0; i < 16; i++) { buttonState[i] = 0; }
  for (int i = 0; i < 16; i++) { functionState[i] = 1; }
  for (int i = 0; i < 16; i++) { outputState[i] = 0; }

  outputState[9] = 1; // Экран 

  updateOutputs1(OUTPUT_PINS1, outputState);
  updateOutputs2(OUTPUT_PINS3, functionState);

  // Инициализация кнопок
  for (int i = 0; i < 16; i++) { 
    btns[i].tick(!mcp2.digitalRead(INPUT_PINS[i]));
  }

  // Инициализация Ethernet и MQTT
  initEthernet();
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(mqttCallback);

  Serial.println("Start MegaPilot_v6.0.2 with MQTT");
}

void loop() {
  // Поддерживаем соединение с MQTT брокером, если оно активно
  if (mqttEnabled) {
    if (!mqttClient.connected()) {
      reconnectMQTT();
    } else {
      mqttClient.loop();
    }
  }

  // Обработка входящих команд из Serial
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    // Проверяем формат команды: "топик:значение"
    int colonIndex = input.indexOf(':');
    if (colonIndex != -1) {
      String topic = input.substring(0, colonIndex);
      String value = input.substring(colonIndex + 1);
      
      // Проверяем, есть ли такой топик в нашем списке
      bool topicFound = false;
      for (int i = 0; i < 16; i++) {
        if (topic.equals(outputTopics[i])) {
          topicFound = true;
          
          // Определяем значение (поддерживаем true/false/1/0)
          bool state;
          if (value.equalsIgnoreCase("true") || value.equals("1")) {
            state = true;
          } else if (value.equalsIgnoreCase("false") || value.equals("0")) {
            state = false;
          } else {
            Serial.println("Invalid value. Use true/false or 1/0");
            break;
          }
          
          // Обновляем состояние выхода
          outputState[i] = state;
          mcp1.digitalWrite(OUTPUT_PINS1[i], state);
          
          // Отправляем сообщение, если MQTT доступен
          if (mqttEnabled && mqttClient.connected()) {
            mqttClient.publish(outputTopics[i], state ? "true" : "false", true);
            Serial.print("Published to ");
          } else {
            Serial.print("Updated locally (MQTT not available) ");
          }
          Serial.print(outputTopics[i]);
          Serial.print(": ");
          Serial.println(state ? "true" : "false");
          break;
        }
      }
      
      if (!topicFound) {
        Serial.println("Topic not found in outputTopics array");
      }
    } else {
      Serial.println("Invalid format. Use 'topic:value'");
    }
  }

  // Обработка кнопок
  for (int i = 0; i < 16; i++) {
    btns[i].tick(!mcp2.digitalRead(INPUT_PINS[i]));
    
    if (i != 10 && i != 11) {
      if (btns[i].click()) {
        outputState[i] = !outputState[i];
        mcp1.digitalWrite(OUTPUT_PINS1[i], outputState[i]);
        
        // Публикуем новое состояние в MQTT, если доступно
        if (mqttEnabled && mqttClient.connected()) {
          mqttClient.publish(outputTopics[i], outputState[i] ? "true" : "false", true);
          Serial.print("Published to MQTT: ");
        } else {
          Serial.print("Updated locally (MQTT not available): ");
        }
        Serial.print("btnClick: ");
        Serial.print(i);
        Serial.print(" - ");
        Serial.println(outputState[i]);
        btns[i].clear();
      }
    }
    if (i != 10 && i != 11) {
      if (btns[i].hold()) {
        functionState[i] = !functionState[i];
        mcp3.digitalWrite(OUTPUT_PINS3[i], functionState[i]);

        // Публикуем новое состояние в MQTT, если доступно
        if (mqttEnabled && mqttClient.connected()) {
          mqttClient.publish(functionTopics[i], functionState[i] ? "true" : "false", true);
          Serial.print("Published to MQTT: ");
        } else {
          Serial.print("Updated locally (MQTT not available): ");
        }
        Serial.print("btnHold: ");
        Serial.print(i);
        Serial.print(" - ");
        Serial.println(functionState[i]);
        btns[i].clear();
      }
    }
    if (i == 10) {
      if (btns[i].hold()) {
        outputState[i] = true;
        mcp1.digitalWrite(OUTPUT_PINS1[i], true);
        
        // Публикуем новое состояние в MQTT, если доступно
        if (mqttEnabled && mqttClient.connected()) {
          mqttClient.publish(outputTopics[i], "true", true);
          Serial.print("Published to MQTT: ");
        } else {
          Serial.print("Updated locally (MQTT not available): ");
        }
        Serial.println("btnHold: Scenario_2 activated");
        btns[i].clear();
      }
    }
    
    // Обработка удержания для кнопки 11 (Scenario_1)
    if (i == 11) {
      if (btns[i].hold()) {
        outputState[i] = true;
        mcp1.digitalWrite(OUTPUT_PINS1[i], true);
        
        // Публикуем новое состояние в MQTT, если доступно
        if (mqttEnabled && mqttClient.connected()) {
          mqttClient.publish(outputTopics[i], "true", true);
          Serial.print("Published to MQTT: ");
        } else {
          Serial.print("Updated locally (MQTT not available): ");
        }
        Serial.println("btnHold: Scenario_1 activated");
        btns[i].clear();
      }
    }
  }
}