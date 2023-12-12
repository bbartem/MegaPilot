#include <Adafruit_MCP23X17.h>
#include <EncButton.h>
#include <GyverOS.h>

GyverOS<1> OS;

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

bool button0;
bool button1;
bool button2;
bool button3;
bool button4;
bool button5;
bool button6;
bool button7;
bool button8;
bool button9;
bool button10;
bool button11;
bool button12;
bool button13;
bool button14;
bool button15;

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

bool script1 = false; // Сценарий1 запуск
bool script2 = false; // Сценарий2 запуск

bool checkScriptLed = true;

EncButton<EB_TICK, VIRT_BTN> btn0;
EncButton<EB_TICK, VIRT_BTN> btn1;
EncButton<EB_TICK, VIRT_BTN> btn2;
EncButton<EB_TICK, VIRT_BTN> btn3;
EncButton<EB_TICK, VIRT_BTN> btn4;
EncButton<EB_TICK, VIRT_BTN> btn5;
EncButton<EB_TICK, VIRT_BTN> btn6;
EncButton<EB_TICK, VIRT_BTN> btn7;
EncButton<EB_TICK, VIRT_BTN> btn8;
EncButton<EB_TICK, VIRT_BTN> btn9;
EncButton<EB_TICK, VIRT_BTN> btn10;
EncButton<EB_TICK, VIRT_BTN> btn11;
EncButton<EB_TICK, VIRT_BTN> btn12;
EncButton<EB_TICK, VIRT_BTN> btn13;
EncButton<EB_TICK, VIRT_BTN> btn14;
EncButton<EB_TICK, VIRT_BTN> btn15;

void checkScript() {
  checkScriptLed = !checkScriptLed;
  mcp3.digitalWrite(OUTPUT_PIN23, checkScriptLed);
  Serial.println("OUTPUT_PIN23 - ");
    Serial.println(!checkScriptLed);
}

void cheking(){
  btn0.tick(!mcp2.digitalRead(INPUT_PIN0));
  btn1.tick(!mcp2.digitalRead(INPUT_PIN1));
  btn2.tick(!mcp2.digitalRead(INPUT_PIN2));
  btn3.tick(!mcp2.digitalRead(INPUT_PIN3));
  btn4.tick(!mcp2.digitalRead(INPUT_PIN4));
  btn5.tick(!mcp2.digitalRead(INPUT_PIN5));
  btn6.tick(!mcp2.digitalRead(INPUT_PIN6));
  btn7.tick(!mcp2.digitalRead(INPUT_PIN7));
  btn8.tick(!mcp2.digitalRead(INPUT_PIN8));
  btn9.tick(!mcp2.digitalRead(INPUT_PIN9));
  btn10.tick(!mcp2.digitalRead(INPUT_PIN10));
  btn11.tick(!mcp2.digitalRead(INPUT_PIN11));
  btn12.tick(!mcp2.digitalRead(INPUT_PIN12));
  btn13.tick(!mcp2.digitalRead(INPUT_PIN13));
  btn14.tick(!mcp2.digitalRead(INPUT_PIN14));
  btn15.tick(!mcp2.digitalRead(INPUT_PIN15));

  if (btn0.click()){
    output0 = !output0;
    mcp1.digitalWrite(OUTPUT_PIN0, output0);
    Serial.println("btn: Пульт - ");
    Serial.println(output0);
  }
  if (btn1.click()){
    output1 = !output1;
    mcp1.digitalWrite(OUTPUT_PIN1, output1);
    Serial.println("btn: Камера - ");
    Serial.println(output1);
  }
  if (btn2.click()){
    output2 = !output2;
    mcp1.digitalWrite(OUTPUT_PIN2, output2);
    Serial.println("btn: Сцена - ");
    Serial.println(output2);
  }
  if (btn3.click()){
    output3 = !output3;
    mcp1.digitalWrite(OUTPUT_PIN3, output3);
    Serial.println("btn: Микрофоны - ");
    Serial.println(output3);
  }
  if (btn4.click()){
    output4 = !output4;
    mcp1.digitalWrite(OUTPUT_PIN4, output4);
    Serial.println("btn: Коммутация - ");
    Serial.println(output4);
  }
  if (btn5.click()){
    output5 = !output5;
    mcp1.digitalWrite(OUTPUT_PIN5, output5);
    Serial.println("btn: Трансляция - ");
    Serial.println(output5);
  }
  if (btn6.click()){
    output6 = !output6;
    mcp1.digitalWrite(OUTPUT_PIN6, output6);
    Serial.println("btn: Мониторы - ");
    Serial.println(output6);
  }
  if (btn7.click()){
    output7 = !output7;
    mcp1.digitalWrite(OUTPUT_PIN7, output7);
    Serial.println("btn: Портал - ");
    Serial.println(output7);
  }
  if (btn8.click()){
    output8 = !output8;
    mcp1.digitalWrite(OUTPUT_PIN8, output8);
    Serial.println("btn: Свет(кафедра) - ");
    Serial.println(output8);
  }
  if (btn9.click()){
    output9 = !output9;
    mcp1.digitalWrite(OUTPUT_PIN9, output9);
    Serial.println("btn: Проектор - ");
    Serial.println(output9);
  }
  if (btn10.click()){
    output10 = !output10;
    mcp1.digitalWrite(OUTPUT_PIN10, output10);
    Serial.println("btn: Сценарий2 - ");
    Serial.println(output10);
    if (!script2){
      Serial.println("Сценарий 2(ВКЛ) запущен");
      checkScript();
      
      output0 = true;
      output2 = true;
      output3 = true;
      output4 = true;
      output6 = true;
      output7 = true;

      mcp1.digitalWrite(OUTPUT_PIN0, output0); //- Пульт
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN2, output2); //- Розетки сцена
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN3, output3); //- Микрофоны
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN4, output4); //- Коммутация
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN6, output6); //- Мониторы
      delay(2000);
      mcp1.digitalWrite(OUTPUT_PIN7, output7); //- Порталы
      Serial.println("Сценарий 2(ВКЛ) завершен");
      checkScript();
    }
    if (script2){
      checkScript();
      Serial.println("Сценарий 2(ВЫКЛ) запущен");

      output0 = false;
      output2 = false;
      output3 = false;
      output4 = false;
      output6 = false;
      output7 = false;

      mcp1.digitalWrite(OUTPUT_PIN6, output6); //- Мониторы
      delay(2000);
      mcp1.digitalWrite(OUTPUT_PIN7, output7); //- Порталы
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN0, output0); //- Пульт
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN2, output2); //- Розетки сцена
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN3, output3); //- Микрофоны
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN4, output4); //- Коммутация
      delay(200);
      Serial.println("Сценарий 2(ВЫКЛ) завершен");
      checkScript();
    }
    script2 = !script2;
  }
  if (btn11.click()){
    output11 = !output11;
    mcp1.digitalWrite(OUTPUT_PIN11, output11);
    Serial.println("btn: Сценарий1 - ON");
    Serial.println(output11);
    if (!script1){
      Serial.println("Сценарий 1(ВКЛ) запущен");
      checkScript();
      
      output0 = true;
      output1 = true;
      output2 = true;
      output3 = true;
      output4 = true;
      output5 = true;
      output6 = true;
      output7 = true;
      output8 = true;
      output9 = true;
      output13 = true;
      output14 = true;
      output15 = true;
      
      Serial.println("отладка на зависание 1");

      mcp1.digitalWrite(OUTPUT_PIN0, output0); //- Пульт
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN1, output1); //- Камера
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN2, output2); //- Розетки сцена
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN3, output3); //- Микрофоны
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN4, output4); //- Коммутация
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN9, output9); //- Проектор
      delay(2000);
      mcp1.digitalWrite(OUTPUT_PIN5, output5); //- Трансляция
      delay(2000);
      mcp1.digitalWrite(OUTPUT_PIN6, output6); //- Мониторы
      delay(2000);
      mcp1.digitalWrite(OUTPUT_PIN7, output7); //- Порталы
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN14, output14); //- Свет
      mcp1.digitalWrite(OUTPUT_PIN15, output15); //- Свет
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN8, output8); //- Свет(кафедра)
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN13, output13); //- Свет(рояль)
      delay(200);
      Serial.println("Сценарий 1(ВКЛ) завершен");
      checkScript();
    }
    if (script1){
      Serial.println("Сценарий 1(ВЫКЛ) запущен");
      checkScript();

      output0 = false;
      output1 = false;
      output2 = false;
      output3 = false;
      output4 = false;
      output5 = false;
      output6 = false;
      output7 = false;
      output8 = false;
      output9 = false;
      output12 = false;
      output13 = false;
      output14 = false;
      output15 = false;

      mcp1.digitalWrite(OUTPUT_PIN5, output5); //- Трансляция
      delay(2000);
      mcp1.digitalWrite(OUTPUT_PIN6, output6); //- Мониторы
      delay(2000);
      mcp1.digitalWrite(OUTPUT_PIN7, output7); //- Порталы
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN0, output0); //- Пульт
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN1, output1); //- Камера
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN2, output2); //- Розетки сцена
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN3, output3); //- Микрофоны
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN4, output4); //- Коммутация
      delay(200);
      mcp1.digitalWrite(OUTPUT_PIN9, output9); //- Проектор
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN14, output14); //- Свет
      mcp1.digitalWrite(OUTPUT_PIN15, output15); //- Свет
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN12, output12); //- Свет(Хор)
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN8, output8); //- Свет(кафедра)
      delay(500);
      mcp1.digitalWrite(OUTPUT_PIN13, output13); //- Свет(рояль)
      delay(200);
      Serial.println("Сценарий 1(ВЫКЛ) завершен");
      checkScript();
    }
    script1 = !script1;
  }
  if (btn12.click()){
    output12 = !output12;
    mcp1.digitalWrite(OUTPUT_PIN12, output12);
    Serial.println("btn: Свет(хор) - ON");
    Serial.println(output12);
  }
  if (btn13.click()){
    output13 = !output13;
    mcp1.digitalWrite(OUTPUT_PIN13, output13);
    Serial.println("btn: Свет(рояль) - ON");
    Serial.println(output13);
  }
  if (btn14.click()){
    output14 = !output14;
    mcp1.digitalWrite(OUTPUT_PIN14, output14);
    Serial.println("btn: Свет(сцена1) - ON");
    Serial.println(output14);
  }
  if (btn15.click()){
    output15 = !output0;
    mcp1.digitalWrite(OUTPUT_PIN15, output15);
    Serial.println("btn: Свет(сцена2) - ON");
    Serial.println(output15);
  }

  if (btn0.held()){
    function0 = !function0;
    mcp3.digitalWrite(OUTPUT_PIN16, function0);
    Serial.print("\t Функция 0: ");
    Serial.println(!function10);
    delay(100);
    function0 = !function0;
    mcp3.digitalWrite(OUTPUT_PIN16, function0);
    Serial.print("\t Функция 0: ");
    Serial.println(!function10);
  }
  if (btn1.held()){
    function1 = !function1;
    mcp3.digitalWrite(OUTPUT_PIN17, function1);
    function7 = !function7;
    mcp3.digitalWrite(OUTPUT_PIN23, function7);
    Serial.print("\t Функция 1: ");
    Serial.println(!function1);
  }
  if (btn2.held()){
    function2 = !function2;
    mcp3.digitalWrite(OUTPUT_PIN18, function2);
    Serial.print("\t Функция 2: ");
    Serial.println(!function2);
  }
  if (btn3.held()){
    function3 = !function3;
    mcp3.digitalWrite(OUTPUT_PIN19, function3);
    Serial.print("\t Функция 3: ");
    Serial.println(!function3);
    delay(100);
    function3 = !function3;
    mcp3.digitalWrite(OUTPUT_PIN19, function3);
    Serial.print("\t Функция 3: ");
    Serial.println(!function3);
  }
  if (btn4.held()){
    function4 = !function4;
    mcp3.digitalWrite(OUTPUT_PIN20, function4);
    Serial.print("\t Функция 4: ");
    Serial.println(!function4);
  }
  if (btn5.held()){
    function5 = !function5;
    mcp3.digitalWrite(OUTPUT_PIN21, function5);
    Serial.print("\t Функция 5: ");
    Serial.println(!function5);
  }
  if (btn6.held()){
    function6 = !function6;
    mcp3.digitalWrite(OUTPUT_PIN22, function6);
    Serial.print("\t Функция 6: ");
    Serial.println(!function6);
  }
  if (btn7.held()){
    function7 = !function7;
    mcp3.digitalWrite(OUTPUT_PIN23, function7);
    Serial.print("\t Функция 7: ");
    Serial.println(!function7);
  }
  if (btn8.held()){
    function8 = !function8;
    mcp3.digitalWrite(OUTPUT_PIN24, function8);
    Serial.print("\t Функция 8: ");
    Serial.println(!function8);
  }
  if (btn9.held()){
    function9 = !function9;
    mcp3.digitalWrite(OUTPUT_PIN25, function9);
    Serial.print("\t Функция 9: ");
    Serial.println(!function9);
  }
  if (btn10.held()){
    function10 = !function10;
    mcp3.digitalWrite(OUTPUT_PIN26, function10);
    Serial.print("\t Функция 10: ");
    Serial.println(!function10);
  }
  if (btn11.held()){
    function11 = !function11;
    mcp3.digitalWrite(OUTPUT_PIN27, function11);
    Serial.print("\t Функция 11: ");
    Serial.println(!function11);
  }
  if (btn12.held()){
    function12 = !function12;
    mcp3.digitalWrite(OUTPUT_PIN28, function12);
    Serial.print("\t Функция 12: ");
    Serial.println(!function12);
  }
  if (btn13.held()){
    function13 = !function13;
    mcp3.digitalWrite(OUTPUT_PIN29, function13);
    Serial.print("\t Функция 13: ");
    Serial.println(!function13);
  }
  if (btn14.held()){
    function14 = !function14;
    mcp3.digitalWrite(OUTPUT_PIN30, function14);
    Serial.print("\t Функция 14: ");
    Serial.println(!function4);
  }
  if (btn15.held()){
    function15 = !function15;
    mcp3.digitalWrite(OUTPUT_PIN31, function15);
    Serial.print("\t Функция 15: ");
    Serial.println(!function15);
  }
}


void setup() {
  Serial.begin(9600);

  OS.attach(0, cheking, 50);

  Serial.println("Start MegaPilot");

  mcp1.begin_I2C(addr1); 
  mcp2.begin_I2C(addr2); 
  mcp3.begin_I2C(addr3);

  mcp1.pinMode(OUTPUT_PIN0, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN1, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN2, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN3, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN4, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN5, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN6, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN7, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN8, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN9, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN10, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN11, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN12, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN13, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN14, OUTPUT);
  mcp1.pinMode(OUTPUT_PIN15, OUTPUT);
  
  mcp3.pinMode(OUTPUT_PIN16, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN17, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN18, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN19, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN20, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN21, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN22, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN23, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN24, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN25, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN26, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN27, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN28, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN29, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN30, OUTPUT);
  mcp3.pinMode(OUTPUT_PIN31, OUTPUT);

  mcp2.pinMode(INPUT_PIN0, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN1, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN2, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN3, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN4, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN5, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN6, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN7, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN8, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN9, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN10, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN11, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN12, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN13, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN14, INPUT_PULLUP);
  mcp2.pinMode(INPUT_PIN15, INPUT_PULLUP);

  mcp1.digitalWrite(OUTPUT_PIN0, output0);
  mcp1.digitalWrite(OUTPUT_PIN1, output1);
  mcp1.digitalWrite(OUTPUT_PIN2, output2);
  mcp1.digitalWrite(OUTPUT_PIN3, output3);
  mcp1.digitalWrite(OUTPUT_PIN4, output4);
  mcp1.digitalWrite(OUTPUT_PIN5, output5);
  mcp1.digitalWrite(OUTPUT_PIN6, output6);
  mcp1.digitalWrite(OUTPUT_PIN7, output7);
  mcp1.digitalWrite(OUTPUT_PIN8, output8);
  mcp1.digitalWrite(OUTPUT_PIN9, output9);
  mcp1.digitalWrite(OUTPUT_PIN10, output10);
  mcp1.digitalWrite(OUTPUT_PIN11, output11);
  mcp1.digitalWrite(OUTPUT_PIN12, output12);
  mcp1.digitalWrite(OUTPUT_PIN13, output13);
  mcp1.digitalWrite(OUTPUT_PIN14, output14);
  mcp1.digitalWrite(OUTPUT_PIN15, output15);

  mcp2.digitalWrite(INPUT_PIN0, button0);
  mcp2.digitalWrite(INPUT_PIN1, button1);
  mcp2.digitalWrite(INPUT_PIN2, button2);
  mcp2.digitalWrite(INPUT_PIN3, button3);
  mcp2.digitalWrite(INPUT_PIN4, button4);
  mcp2.digitalWrite(INPUT_PIN5, button5);
  mcp2.digitalWrite(INPUT_PIN6, button6);
  mcp2.digitalWrite(INPUT_PIN7, button7);
  mcp2.digitalWrite(INPUT_PIN8, button8);
  mcp2.digitalWrite(INPUT_PIN9, button9);
  mcp2.digitalWrite(INPUT_PIN10, button10);
  mcp2.digitalWrite(INPUT_PIN11, button11);
  mcp2.digitalWrite(INPUT_PIN12, button12);
  mcp2.digitalWrite(INPUT_PIN13, button13);
  mcp2.digitalWrite(INPUT_PIN14, button14);
  mcp2.digitalWrite(INPUT_PIN15, button15);

  mcp3.digitalWrite(OUTPUT_PIN16, function0); // 
  mcp3.digitalWrite(OUTPUT_PIN17, function1); //
  mcp3.digitalWrite(OUTPUT_PIN18, function2); // 
  mcp3.digitalWrite(OUTPUT_PIN19, function3); // 
  mcp3.digitalWrite(OUTPUT_PIN20, function4); //
  mcp3.digitalWrite(OUTPUT_PIN21, function5); //
  mcp3.digitalWrite(OUTPUT_PIN22, function6); //
  mcp3.digitalWrite(OUTPUT_PIN23, function7); //
  mcp3.digitalWrite(OUTPUT_PIN24, function8); //
  mcp3.digitalWrite(OUTPUT_PIN25, function9); //
  mcp3.digitalWrite(OUTPUT_PIN26, function10); //
  mcp3.digitalWrite(OUTPUT_PIN27, function11); //
  mcp3.digitalWrite(OUTPUT_PIN28, function12); //
  mcp3.digitalWrite(OUTPUT_PIN29, function13); //
  mcp3.digitalWrite(OUTPUT_PIN30, function14); //
  mcp3.digitalWrite(OUTPUT_PIN31, function15); //
}

void loop() {
  OS.tick();
}
