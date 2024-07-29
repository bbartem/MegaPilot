//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "MegaESP8266"
#define BLYNK_AUTH_TOKEN            "IDSgGWPXm_YpSQgXHlsL62IwIR-6_8b7"

#define BLYNK_PRINT Serial

#include <EncButton.h>
#include <Adafruit_MCP23X17.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char ssid[] = "wi-fi";
char pass[] = "YourPassword";
char domain[] = "195.20.119.138";

IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);

#define EspSerial Serial1

#define ESP8266_BAUD 38400

ESP8266 wifi(&EspSerial);

Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
Adafruit_MCP23X17 mcp3;

#define addr1 0x24
#define addr2 0x22
#define addr3 0x23

#define OUTPUT_PIN0 0
#define OUTPUT_PIN1 1
#define OUTPUT_PIN2 2
#define OUTPUT_PIN3 3
#define OUTPUT_PIN4 4
#define OUTPUT_PIN5 5
#define OUTPUT_PIN6 6
#define OUTPUT_PIN7 7
#define OUTPUT_PIN8 8
#define OUTPUT_PIN9 9
#define OUTPUT_PIN10 10
#define OUTPUT_PIN11 11
#define OUTPUT_PIN12 12
#define OUTPUT_PIN13 13
#define OUTPUT_PIN14 14
#define OUTPUT_PIN15 15

#define OUTPUT_PIN16 0
#define OUTPUT_PIN17 1
#define OUTPUT_PIN18 2
#define OUTPUT_PIN19 3
#define OUTPUT_PIN20 4
#define OUTPUT_PIN21 5
#define OUTPUT_PIN22 6
#define OUTPUT_PIN23 7
#define OUTPUT_PIN24 8
#define OUTPUT_PIN25 9
#define OUTPUT_PIN26 10
#define OUTPUT_PIN27 11
#define OUTPUT_PIN28 12
#define OUTPUT_PIN29 13
#define OUTPUT_PIN30 14
#define OUTPUT_PIN31 15

#define INPUT_PIN0 0
#define INPUT_PIN1 1
#define INPUT_PIN2 2
#define INPUT_PIN3 3
#define INPUT_PIN4 4
#define INPUT_PIN5 5
#define INPUT_PIN6 6   
#define INPUT_PIN7 7
#define INPUT_PIN8 8
#define INPUT_PIN9 9
#define INPUT_PIN10 10
#define INPUT_PIN11 11
#define INPUT_PIN12 12
#define INPUT_PIN13 13
#define INPUT_PIN14 14
#define INPUT_PIN15 15

int button0 = LOW;
int button1 = LOW;
int button2 = LOW;
int button3 = LOW;
int button4 = LOW;
int button5 = LOW;
int button6 = LOW;
int button7 = LOW;
int button8 = LOW;
int button9 = LOW;
int button10 = LOW;
int button11 = LOW;
int button12 = LOW;
int button13 = LOW;
int button14 = LOW;
int button15 = LOW;

bool output0 = false;
bool output1 = false;
bool output2 = false;
bool output3 = false;
bool output4 = false;
bool output5 = false;
bool output6 = false;
bool output7 = false;
bool output8 = false;
bool output9 = false;
bool output10 = false;
bool output11 = false;
bool output12 = false;
bool output13 = false;
bool output14 = false;
bool output15 = false;

bool function0 = true; // - 1 реле Подсобка (дверь)
bool function1 = true; // - 3 реле Розетка
bool function2 = true; // - 4 Реле 
bool function3 = true; // -  2 реле Балкон (дверь)
bool function4 = true; // - 15 реле
bool function5 = true; // - 13 реле
bool function6 = true; // - 14 реле
bool function7 = true; // - 16 реле Лампочка
bool function8 = true; // - 8 реле
bool function9 = true; // - 6 реле
bool function10 = true; // - 10 реле
bool function11 = true; // - 12 реле
bool function12 = true; // - 7 реле
bool function13 = true; // - 5 реле
bool function14 = true; // - 9 реле
bool function15 = true; // - 11 реле

void setup()
{
  Serial.begin(115200);

  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  
  
  WiFi.config(arduino_ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
   Serial.println();
   Blynk.begin(BLYNK_AUTH_TOKEN, domain, 9444);
   //Blynk.begin(auth, "blynk-cloud.com", 8442, arduino_ip, dns_ip, gateway_ip, subnet_mask, arduino_mac);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}