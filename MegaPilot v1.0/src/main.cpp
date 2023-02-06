#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

//#include <Adafruit_MCP23X17.h>

//#include <Adafruit_MCP23XXX.h>
#include <Adafruit_MCP23X17.h>
#include <Wire.h>

#define LED_PIN0 0
#define LED_PIN1 1
#define LED_PIN2 2
#define LED_PIN3 3
#define LED_PIN4 4
#define LED_PIN5 5
#define LED_PIN6 6
#define LED_PIN7 7
#define LED_PIN8 8
#define LED_PIN9 9
#define LED_PIN10 10
#define LED_PIN11 11
#define LED_PIN12 12
#define LED_PIN13 13
#define LED_PIN14 14
#define LED_PIN15 15

#define LED_PIN16 0
#define LED_PIN17 1
#define LED_PIN18 2
#define LED_PIN19 3
#define LED_PIN20 4
#define LED_PIN21 5
#define LED_PIN22 6
#define LED_PIN23 7
#define LED_PIN24 8
#define LED_PIN25 9
#define LED_PIN26 10
#define LED_PIN27 11
#define LED_PIN28 12
#define LED_PIN29 13
#define LED_PIN30 14
#define LED_PIN31 15

#define BUTTON_PIN0 0
#define BUTTON_PIN1 1
#define BUTTON_PIN2 2
#define BUTTON_PIN3 3
#define BUTTON_PIN4 4
#define BUTTON_PIN5 5
#define BUTTON_PIN6 6   
#define BUTTON_PIN7 7
#define BUTTON_PIN8 8
#define BUTTON_PIN9 9
#define BUTTON_PIN10 10 //сценарий1
#define BUTTON_PIN11 11 //сценарий2
#define BUTTON_PIN12 12
#define BUTTON_PIN13 13
#define BUTTON_PIN14 14
#define BUTTON_PIN15 15



Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
Adafruit_MCP23X17 mcp3;
#define addr1 0x24
#define addr2 0x22
#define addr3 0x23

char auth[] = "tdMaGVFxXJIi1IZVxWGpr7NqFbzySp0E";
char domain[] = "195.20.119.138";

#define W5100_CS  10
#define SDCARD_CS 4

WidgetTerminal terminal(V21);

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V5);
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V8);
  Blynk.syncVirtual(V9);
  Blynk.syncVirtual(V10);
  Blynk.syncVirtual(V11);
  Blynk.syncVirtual(V12);
  Blynk.syncVirtual(V13);
  Blynk.syncVirtual(V14);
  Blynk.syncVirtual(V15);
}

BlynkTimer timer;

void scenario();

int button0 = HIGH;
int button1 = HIGH;
int button2 = HIGH;
int button3 = HIGH;
int button4 = HIGH;
int button5 = HIGH;
int button6 = HIGH;
int button7 = HIGH;
int button8 = HIGH;
int button9 = HIGH;
int button10 = HIGH;
int button11 = HIGH;
int button12 = HIGH;
int button13 = HIGH;
int button14 = HIGH;
int button15 = HIGH;

int led0 = LOW;
int led1 = LOW;
int led2 = LOW;
int led3 = LOW;
int led4 = LOW;
int led5 = LOW;
int led6 = LOW;
int led7 = LOW;
int led8 = LOW;
int led9 = LOW;
int led10 = LOW;
int led11 = LOW;
int led12 = LOW;
int led13 = LOW;
int led14 = LOW;
int led15 = LOW;


int function1 = HIGH; // - Балкон (дверь)
int function2 = HIGH; // - Подсобка (дверь)
int function3 = HIGH; // - Розетка
int function4 = HIGH; // - 
int function5 = HIGH; // - 
int function6 = HIGH; // - 
int function7 = HIGH; // - 
int function8 = HIGH; // - 
int function9 = HIGH; // - 
int function10 = HIGH; // - 
int function11 = HIGH; // - 
int function12 = HIGH; // - 
int function13 = HIGH; // - 
int function14 = HIGH; // - 
int function15 = HIGH; // - 
int function16 = HIGH; // - 

int script = LOW; // Сценарий запуск

BLYNK_WRITE(V0)
{
  led0 = param.asInt();
  mcp1.digitalWrite(LED_PIN0, led0);
  terminal.println("app: Балкон");
}
BLYNK_WRITE(V1)
{
  led1 = param.asInt();
  mcp1.digitalWrite(LED_PIN1, led1);
  terminal.println("app: Камера");
}
BLYNK_WRITE(V2)
{
  led2 = param.asInt();
  mcp1.digitalWrite(LED_PIN2, led2);
  terminal.println("app: Сцена");
}
BLYNK_WRITE(V3)
{
  led3 = param.asInt();
  mcp1.digitalWrite(LED_PIN3, led3);
  terminal.println("app: Микрофоны");
}
BLYNK_WRITE(V4)
{
  led4 = param.asInt();
  mcp1.digitalWrite(LED_PIN4, led4);
  terminal.println("app: Коммутация");
}
BLYNK_WRITE(V5)
{
  led5 = param.asInt();
  mcp1.digitalWrite(LED_PIN5, led5);
  terminal.println("app: Трансляция");
}
BLYNK_WRITE(V6)
{
  led6 = param.asInt();
  mcp1.digitalWrite(LED_PIN6, led6);
  terminal.println("app: Мониторы");
}
BLYNK_WRITE(V7)
{
  led7 = param.asInt();
  mcp1.digitalWrite(LED_PIN7, led7);
  terminal.println("app: Порталы");
}
BLYNK_WRITE(V8)
{
  led8 = param.asInt();
  mcp1.digitalWrite(LED_PIN8, led8);
  terminal.println("app: Свет(кафедра)");
}
BLYNK_WRITE(V9)
{
  led9 = param.asInt();
  mcp1.digitalWrite(LED_PIN9, led9);
  terminal.println("app: Проектор");
}
BLYNK_WRITE(V10)
{
  led10 = param.asInt();
  terminal.println("app: Сценарий 2");
  mcp3.digitalWrite(LED_PIN31, led10);
  delay(2000);
  led10 = LOW;
  mcp3.digitalWrite(LED_PIN31, led10);
}
BLYNK_WRITE(V11)
{
  led11 = param.asInt();
  script = param.asInt();
  terminal.println("app: Сценарий 1");
  mcp1.digitalWrite(LED_PIN11, led11);
  btnScenario();
}
BLYNK_WRITE(V12)
{
  led12 = param.asInt();
  mcp1.digitalWrite(LED_PIN12, led12);
  terminal.println("app: Свет(хор)");
}
BLYNK_WRITE(V13)
{
  led13 = param.asInt();
  mcp1.digitalWrite(LED_PIN13, led13);
  terminal.println("app: Свет(рояль)");
}
BLYNK_WRITE(V14)
{
  led14 = param.asInt();
  mcp1.digitalWrite(LED_PIN14, led14);
  terminal.println("app: Свет1");
}
BLYNK_WRITE(V15)
{
  led15 = param.asInt();
  mcp1.digitalWrite(LED_PIN15, led15);
  terminal.println("app: Свет2");
}
BLYNK_WRITE(V16) // - Подсобка (дверь)
{
  function1 = param.asInt();
  terminal.println("app: Дверь(подсобка)");
  door1();
}
BLYNK_WRITE(V17) // - Балкон (дверь)
{
  function2 = param.asInt();
  terminal.println("app: Дверь(балкон)");
  door2();
}
BLYNK_WRITE(V20) // - Розетка
{
  function3 = param.asInt();
  terminal.println("app: Розетка");
  socket();
}
//BLYNK_WRITE(V18) // - Сценарий1
//{
//  script = param.asInt();
//  btnScenario();
//}
BLYNK_WRITE(V22)
{
  function4 = param.asInt();
  mcp3.digitalWrite(LED_PIN18, function4);
  terminal.println("app: function4");
}
BLYNK_WRITE(V24)
{
  function6 = param.asInt();
  mcp3.digitalWrite(LED_PIN20, function6);
  terminal.println("app: function6");
}
BLYNK_WRITE(V25)
{
  function7 = param.asInt();
  mcp3.digitalWrite(LED_PIN21, function7);
  terminal.println("app: function7");
}
BLYNK_WRITE(V26)
{
  function8 = param.asInt();
  mcp3.digitalWrite(LED_PIN22, function8);
  terminal.println("app: function8");
}
BLYNK_WRITE(V27)
{
  function9 = param.asInt();
  mcp3.digitalWrite(LED_PIN23, function9);
  terminal.println("app: function9");
}
BLYNK_WRITE(V28)
{
  function10 = param.asInt();
  mcp3.digitalWrite(LED_PIN24, function10);
  terminal.println("app: function10");
}
BLYNK_WRITE(V29)
{
  function11 = param.asInt();
  mcp3.digitalWrite(LED_PIN25, function11);
  terminal.println("app: function11");
}
BLYNK_WRITE(V30)
{
  function12 = param.asInt();
  mcp3.digitalWrite(LED_PIN26, function12);
  terminal.println("app: function12");
}
BLYNK_WRITE(V31)
{
  function13 = param.asInt();
  mcp3.digitalWrite(LED_PIN27, function13);
  terminal.println("app: function13");
}
BLYNK_WRITE(V32)
{
  function14 = param.asInt();
  mcp3.digitalWrite(LED_PIN28, function14);
  terminal.println("app: function14");
}
BLYNK_WRITE(V33)
{
  function15 = param.asInt();
  mcp3.digitalWrite(LED_PIN29, function15);
  terminal.println("app: function15");
}
BLYNK_WRITE(V34)
{
  function16 = param.asInt();
  mcp3.digitalWrite(LED_PIN30, function16);
  terminal.println("app: function16");
}
void door1(){
    Serial.println("Дверь1 ON");
    mcp3.digitalWrite(LED_PIN16, function1);
    Blynk.virtualWrite(V16, function1);
    delay(1500);
    function1 = HIGH;
    Serial.println("Дверь1 OFF");
    mcp3.digitalWrite(LED_PIN16, function1);
    Blynk.virtualWrite(V16, function1);
}
void door2(){
    Serial.println("Дверь2 ON");
    mcp3.digitalWrite(LED_PIN19, function2);
    Blynk.virtualWrite(V17, function2);
    delay(1500);
    function2 = HIGH;
    Serial.println("Дверь2 OFF");
    mcp3.digitalWrite(LED_PIN19, function2);
    Blynk.virtualWrite(V17, function2);
}
void socket(){
  if (function3 == LOW){
    Serial.println("Розетка ON");
    mcp3.digitalWrite(LED_PIN17, function3);
    Blynk.virtualWrite(V20, function3);
  } else {
    Serial.println("Розетка OFF");
    mcp3.digitalWrite(LED_PIN17, function3);
    Blynk.virtualWrite(V20, function3);
  }
}

void btnScenario(){
  if (script == HIGH){
    led0 = HIGH;
    led1 = HIGH;
    led2 = HIGH;
    led3 = HIGH;
    led4 = HIGH;
    led5 = HIGH;
    led6 = HIGH;
    led7 = HIGH;
    led8 = HIGH;
    led9 = HIGH;
    led13 = HIGH;
    led14 = HIGH;
    led15 = HIGH;
    Serial.println("Сценарий 1(ВКЛ) запущен");
    terminal.println("Сценарий 1(ВКЛ) запущен");
    delay(200);
        mcp1.digitalWrite(LED_PIN0, led0); //- Пульт
        Blynk.virtualWrite(V0, led0);
        terminal.println("\t ON - Пульт");
        delay(200);
        mcp1.digitalWrite(LED_PIN1, led1); //- Камера
        Blynk.virtualWrite(V1, led1);
        terminal.println("\t ON - Камера");
        delay(200);
        mcp1.digitalWrite(LED_PIN2, led2); //- Розетки сцена
        Blynk.virtualWrite(V2, led2);
        terminal.println("\t ON - Сцена");
        delay(200);
        mcp1.digitalWrite(LED_PIN3, led3); //- Микрофоны
        Blynk.virtualWrite(V3, led3);
        terminal.println("\t ON - Микрофоны");
        delay(200);
        mcp1.digitalWrite(LED_PIN4, led4); //- Коммутация
        Blynk.virtualWrite(V4, led4);
        terminal.println("\t ON - Коммутация");
        delay(200);
        mcp1.digitalWrite(LED_PIN9, led9); //- Проектор
        Blynk.virtualWrite(V9, led9);
        terminal.println("\t ON - Проектор");
        delay(2000);
        mcp1.digitalWrite(LED_PIN5, led5); //- Трансляция
        Blynk.virtualWrite(V5, led5);
        terminal.println("\t ON - Трансляция");
        delay(2000);
        mcp1.digitalWrite(LED_PIN6, led6); //- Мониторы
        Blynk.virtualWrite(V6, led6);
        terminal.println("\t ON - Мониторы");
        delay(2000);
        mcp1.digitalWrite(LED_PIN7, led7); //- Порталы
        Blynk.virtualWrite(V7, led7);
        terminal.println("\t ON - Порталы");
        delay(1000);
        mcp1.digitalWrite(LED_PIN14, led14); //- Свет
        mcp1.digitalWrite(LED_PIN15, led15); //- Свет
        Blynk.virtualWrite(V14, led14);
        Blynk.virtualWrite(V15, led15);
        terminal.println("\t ON - Свет1");
        terminal.println("\t ON - Свет2");
        delay(1000);
        mcp1.digitalWrite(LED_PIN8, led8); //- Свет(кафедра)
        Blynk.virtualWrite(V8, led8);
        terminal.println("\t ON - Свет(кафедра)");
        delay(1000);
        mcp1.digitalWrite(LED_PIN13, led13); //- Свет(рояль)
        Blynk.virtualWrite(V13, led13);
        terminal.println("\t ON - Свет(рояль)");
        delay(200);
    Serial.println("Сценарий 1(ВКЛ) завершен");
    terminal.println("Сценарий 1(ВКЛ) завершен");
  } else {
    led0 = LOW;
    led1 = LOW;
    led2 = LOW;
    led3 = LOW;
    led4 = LOW;
    led5 = LOW;
    led6 = LOW;
    led7 = LOW;
    led8 = LOW;
    led9 = LOW;
    led12 = LOW;
    led13 = LOW;
    led14 = LOW;
    led15 = LOW;
    Serial.println("Сценарий 1(ВЫКЛ) запущен");
    terminal.println("Сценарий 1(ВЫКЛ) запущен");
    delay(200);
        mcp1.digitalWrite(LED_PIN5, led5); //- Трансляция
        Blynk.virtualWrite(V5, led5);
        terminal.println("\t OFF - Трансляция");
        delay(2000);
        mcp1.digitalWrite(LED_PIN6, led6); //- Мониторы
        Blynk.virtualWrite(V6, led6);
        terminal.println("\t OFF - Мониторы");
        delay(2000);
        mcp1.digitalWrite(LED_PIN7, led7); //- Порталы
        Blynk.virtualWrite(V7, led7);
        terminal.println("\t OFF - Порталы");
        delay(1000);
        mcp1.digitalWrite(LED_PIN0, led0); //- Пульт
        Blynk.virtualWrite(V0, led0);
        terminal.println("\t OFF - Пульт");
        delay(200);
        mcp1.digitalWrite(LED_PIN1, led1); //- Камера
        Blynk.virtualWrite(V1, led1);
        terminal.println("\t OFF - Камера");
        delay(200);
        mcp1.digitalWrite(LED_PIN2, led2); //- Розетки сцена
        Blynk.virtualWrite(V2, led2);
        terminal.println("\t OFF - Сцена");
        delay(200);
        mcp1.digitalWrite(LED_PIN3, led3); //- Микрофоны
        Blynk.virtualWrite(V3, led3);
        terminal.println("\t OFF - Микрофоны");
        delay(200);
        mcp1.digitalWrite(LED_PIN4, led4); //- Коммутация
        Blynk.virtualWrite(V4, led4);
        terminal.println("\t OFF - Коммутация");
        delay(200);
        mcp1.digitalWrite(LED_PIN9, led9); //- Проектор
        Blynk.virtualWrite(V9, led9);
        terminal.println("\t OFF - Проектор");
        delay(1000);
        mcp1.digitalWrite(LED_PIN14, led14); //- Свет
        mcp1.digitalWrite(LED_PIN15, led15); //- Свет
        Blynk.virtualWrite(V14, led14);
        Blynk.virtualWrite(V15, led15);
        terminal.println("\t OFF - Свет1");
        terminal.println("\t OFF - Свет2");
        delay(1000);
        mcp1.digitalWrite(LED_PIN12, led12); //- Свет(Хор)
        Blynk.virtualWrite(V12, led12);
        terminal.println("\t OFF - Свет(хор)");
        delay(1000);
        mcp1.digitalWrite(LED_PIN8, led8); //- Свет(кафедра)
        Blynk.virtualWrite(V8, led8);
        terminal.println("\t OFF - Свет(кафедра)");
        delay(1000);
        mcp1.digitalWrite(LED_PIN13, led13); //- Свет(рояль)
        Blynk.virtualWrite(V13, led13);
        terminal.println("\t OFF - Свет(рояль)");
        delay(200);
    Serial.println("Сценарий 1(ВЫКЛ) завершен");
    terminal.println("Сценарий 1(ВЫКЛ) завершен");
  }
}

void redLight(){
  if (led10 == LOW){
    mcp3.digitalWrite(LED_PIN31, HIGH);
    delay(2000);
    mcp3.digitalWrite(LED_PIN31, LOW);
  } else {
    mcp3.digitalWrite(LED_PIN31, HIGH);
    delay(2000);
    mcp3.digitalWrite(LED_PIN31, LOW);
  }
}

void scenario(){
  if (mcp2.digitalRead(BUTTON_PIN0) == LOW){
    terminal.println("btn: Пульт");//   1 - пульт
    if (button0 != LOW){
      led0 = !led0;
      mcp1.digitalWrite(LED_PIN0, led0);
      Blynk.virtualWrite(V0, led0);
    }
    button0 = LOW;
  } else {
    button0 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN1) == LOW){
    terminal.println("btn: Камера");//   2 - камера
    if (button1 != LOW){
      led1 = !led1;
      mcp1.digitalWrite(LED_PIN1, led1);
      Blynk.virtualWrite(V1, led1);
    }
    button1 = LOW;
  } else {
    button1 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN2) == LOW){
    terminal.println("btn: Сцена");//   3 - сцена
    if (button2 != LOW){
      led2 = !led2;
      mcp1.digitalWrite(LED_PIN2, led2);
      Blynk.virtualWrite(V2, led2);
    }
    button2 = LOW;
  } else {
    button2 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN3) == LOW){
    terminal.println("btn: Микрофоны");//   4 - микрофоны
    if (button3 != LOW){
      led3 = !led3;
      mcp1.digitalWrite(LED_PIN3, led3);
      Blynk.virtualWrite(V3, led3);
    }
    button3 = LOW;
  } else {
    button3 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN4) == LOW){
    terminal.println("btn: Коммутация");//   5 - коммутация
    if (button4 != LOW){
      led4 = !led4;
      mcp1.digitalWrite(LED_PIN4, led4);
      Blynk.virtualWrite(V4, led4);
    }
    button4 = LOW;
  } else {
    button4 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN5) == LOW){
    terminal.println("btn: Трансляция");//   6 - трансляция
    if (button5 != LOW){
      led5 = !led5;
      mcp1.digitalWrite(LED_PIN5, led5);
      Blynk.virtualWrite(V5, led5);
    }
    button5 = LOW;
  } else {
    button5 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN6) == LOW){
    terminal.println("btn: Мониторы");//   7 - мониторы
    if (button6 != LOW){
      led6 = !led6;
      mcp1.digitalWrite(LED_PIN6, led6);
      Blynk.virtualWrite(V6, led6);
    }
    button6 = LOW;
  } else {
    button6 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN7) == LOW){
    terminal.println("btn: Порталы");//   8 - порталы
    if (button7 != LOW){
      led7 = !led7;
      mcp1.digitalWrite(LED_PIN7, led7);
      Blynk.virtualWrite(V7, led7);
    }
    button7 = LOW;
  } else {
    button7 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN8) == LOW){
    terminal.println("btn: Свет(кафедра)");//   9 - свет (кафедра)
    if (button8 != LOW){
      led8 = !led8;
      mcp1.digitalWrite(LED_PIN8, led8);
      Blynk.virtualWrite(V8, led8);
    }
    button8 = LOW;
  } else {
    button8 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN9) == LOW){
    terminal.println("btn: Проектор");//  10 - проектор
    if (button9 != LOW){
      led9 = !led9;
      mcp1.digitalWrite(LED_PIN9, led9);
      Blynk.virtualWrite(V9, led9);
    }
    button9 = LOW;
  } else {
    button9 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN10) == LOW){
    terminal.println("btn: Сценарий 2");// 11 - кнопка (сценарий 2)
    if (button10 != LOW){
      led10 = !led10;
      mcp1.digitalWrite(LED_PIN10, led10);
      Blynk.virtualWrite(V10, led10);
    }
    button10 = LOW;
    redLight();
  } else {
    button10 = HIGH;
    redLight();
  }
  if (mcp2.digitalRead(BUTTON_PIN11) == LOW){
    terminal.println("btn: Сценарий 1");// 12 - кнопка (сценарий 1)
    if (button11 != LOW){
      led11 = !led11;
      mcp1.digitalWrite(LED_PIN11, led11);
      Blynk.virtualWrite(V11, led11);
      script = led11;
      btnScenario();
    }
    button11 = LOW;
  } else {
    button11 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN12) == LOW){
    terminal.println("btn: Свет(хор)");// 13 - свет (хор)
    if (button12 != LOW){
      led12 = !led12;
      mcp1.digitalWrite(LED_PIN12, led12);
      Blynk.virtualWrite(V12, led12);
    }
    button12 = LOW;
  } else {
    button12 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN13) == LOW){
    terminal.println("btn: Свет(рояль)");// 14 - свет (рояль)
    if (button13 != LOW){
      led13 = !led13;
      mcp1.digitalWrite(LED_PIN13, led13);
      Blynk.virtualWrite(V13, led13);
    }
    button13 = LOW;
  } else {
    button13 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN14) == LOW){
    terminal.println("btn: Свет1");// 15 - свет
    if (button14 != LOW){
      led14 = !led14;
      mcp1.digitalWrite(LED_PIN14, led14);
      Blynk.virtualWrite(V14, led14);
    }
    button14 = LOW;
  } else {
    button14 = HIGH;
  }
  if (mcp2.digitalRead(BUTTON_PIN15) == LOW){
    terminal.println("btn: Свет2");// 16 - свет
    if (button15 != LOW){
      led15 = !led15;
      mcp1.digitalWrite(LED_PIN15, led15);
      Blynk.virtualWrite(V15, led15);
    }
    button15 = LOW;
  } else {
    button15 = HIGH;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  mcp1.begin_I2C(addr1); 
  mcp2.begin_I2C(addr2); 
  mcp3.begin_I2C(addr3);
  
  mcp1.pinMode(LED_PIN0, OUTPUT);
  mcp1.pinMode(LED_PIN1, OUTPUT);
  mcp1.pinMode(LED_PIN2, OUTPUT);
  mcp1.pinMode(LED_PIN3, OUTPUT);
  mcp1.pinMode(LED_PIN4, OUTPUT);
  mcp1.pinMode(LED_PIN5, OUTPUT);
  mcp1.pinMode(LED_PIN6, OUTPUT);
  mcp1.pinMode(LED_PIN7, OUTPUT);
  mcp1.pinMode(LED_PIN8, OUTPUT);
  mcp1.pinMode(LED_PIN9, OUTPUT);
  mcp1.pinMode(LED_PIN10, OUTPUT);
  mcp1.pinMode(LED_PIN11, OUTPUT);
  mcp1.pinMode(LED_PIN12, OUTPUT);
  mcp1.pinMode(LED_PIN13, OUTPUT);
  mcp1.pinMode(LED_PIN14, OUTPUT);
  mcp1.pinMode(LED_PIN15, OUTPUT);
  
  mcp3.pinMode(LED_PIN16, OUTPUT);
  mcp3.pinMode(LED_PIN17, OUTPUT);
  mcp3.pinMode(LED_PIN18, OUTPUT);
  mcp3.pinMode(LED_PIN19, OUTPUT);
  mcp3.pinMode(LED_PIN20, OUTPUT);
  mcp3.pinMode(LED_PIN21, OUTPUT);
  mcp3.pinMode(LED_PIN22, OUTPUT);
  mcp3.pinMode(LED_PIN23, OUTPUT);
  mcp3.pinMode(LED_PIN24, OUTPUT);
  mcp3.pinMode(LED_PIN25, OUTPUT);
  mcp3.pinMode(LED_PIN26, OUTPUT);
  mcp3.pinMode(LED_PIN27, OUTPUT);
  mcp3.pinMode(LED_PIN28, OUTPUT);
  mcp3.pinMode(LED_PIN29, OUTPUT);
  mcp3.pinMode(LED_PIN30, OUTPUT);
  mcp3.pinMode(LED_PIN31, OUTPUT);


  mcp2.pinMode(BUTTON_PIN0, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN1, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN2, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN3, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN4, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN5, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN6, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN7, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN8, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN9, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN10, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN11, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN12, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN13, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN14, INPUT_PULLUP);
  mcp2.pinMode(BUTTON_PIN15, INPUT_PULLUP);

  mcp1.digitalWrite(LED_PIN0, led0);
  mcp1.digitalWrite(LED_PIN1, led1);
  mcp1.digitalWrite(LED_PIN2, led2);
  mcp1.digitalWrite(LED_PIN3, led3);
  mcp1.digitalWrite(LED_PIN4, led4);
  mcp1.digitalWrite(LED_PIN5, led5);
  mcp1.digitalWrite(LED_PIN6, led6);
  mcp1.digitalWrite(LED_PIN7, led7);
  mcp1.digitalWrite(LED_PIN8, led8);
  mcp1.digitalWrite(LED_PIN9, led9);
  mcp1.digitalWrite(LED_PIN10, led10);
  mcp1.digitalWrite(LED_PIN11, led11);
  mcp1.digitalWrite(LED_PIN12, led12);
  mcp1.digitalWrite(LED_PIN13, led13);
  mcp1.digitalWrite(LED_PIN14, led14);
  mcp1.digitalWrite(LED_PIN15, led15);

  mcp3.digitalWrite(LED_PIN16, function1);
  mcp3.digitalWrite(LED_PIN17, function2);
  mcp3.digitalWrite(LED_PIN18, function3);
  mcp3.digitalWrite(LED_PIN19, function4);
  mcp3.digitalWrite(LED_PIN20, function5);
  mcp3.digitalWrite(LED_PIN21, function6);
  mcp3.digitalWrite(LED_PIN22, function7);
  mcp3.digitalWrite(LED_PIN23, function8);
  mcp3.digitalWrite(LED_PIN24, function9);
  mcp3.digitalWrite(LED_PIN25, function10);
  mcp3.digitalWrite(LED_PIN26, function11);
  mcp3.digitalWrite(LED_PIN27, function12);
  mcp3.digitalWrite(LED_PIN28, function13);
  mcp3.digitalWrite(LED_PIN29, function14);
  mcp3.digitalWrite(LED_PIN30, function15);
  mcp3.digitalWrite(LED_PIN31, function16);
  

  Blynk.begin(auth,domain);
  timer.setInterval(100L, scenario);
}

void loop(){
  Blynk.run();
  timer.run();
}