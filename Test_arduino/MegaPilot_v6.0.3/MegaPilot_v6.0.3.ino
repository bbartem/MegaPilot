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
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(mqtt_client_id)) {
      Serial.println("connected");
      
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
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Инициализация Ethernet
void initEthernet() {
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192, 168, 1, 52);
  IPAddress dns(192, 168, 1, 1);      // обычно шлюз или DNS
  IPAddress gateway(192, 168, 1, 1);  // ваш шлюз
  IPAddress subnet(255, 255, 255, 0); // маска сети
  
  Serial.println("Initializing Ethernet with static IP...");

  Ethernet.begin(mac, ip, dns, gateway, subnet);

  delay(1000); // Ждём немного

  Serial.print("Ethernet IP: ");
  Serial.println(Ethernet.localIP());
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

  Serial.println("Start MegaPilot_v6.0.1 with MQTT");
}

void loop() {
  // Поддерживаем соединение с MQTT брокером
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();

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
          
          // Отправляем сообщение с retain=true
          mqttClient.publish(outputTopics[i], state ? "true" : "false", true);
          
          Serial.print("Published to ");
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
        
        // Публикуем новое состояние в MQTT
        mqttClient.publish(outputTopics[i], outputState[i] ? "true" : "false", true);
        
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
        // mcp3.digitalWrite(OUTPUT_PINS3[i], functionState[i]);

        // Публикуем новое состояние в MQTT
        mqttClient.publish(functionTopics[i], functionState[i] ? "true" : "false", true);

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
        //mcp1.digitalWrite(OUTPUT_PINS1[i], true);
        mqttClient.publish(outputTopics[i], "true", true);
        
        Serial.print("btnHold: Scenario_2 activated");
        btns[i].clear();
      }
    }
    
    // Обработка удержания для кнопки 11 (Scenario_1)
    if (i == 11) {
      if (btns[i].hold()) {
        outputState[i] = true;
        //mcp1.digitalWrite(OUTPUT_PINS1[i], true);
        mqttClient.publish(outputTopics[i], "true", true);
        
        Serial.print("btnHold: Scenario_1 activated");
        btns[i].clear();
      }
    }
  }
}