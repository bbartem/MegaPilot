// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA

#include <HX711.h>                                  // Подключаем библиотеку HX711 для работы с АЦП hx711

HX711 scale(A1, A0);                                // Указываем в какие пины подключен АЦП hx711 (DT(DOUT)  - pin A1, SCK - pin A0)

float myScale;                                      // Инициализируем переменную в которой будем хранить текущий вес

void setup() {
  Serial.begin(9600);                               // Инициализируем монитор порта, как устройство вывода
  Serial.println("Calibration...");                 // Выводим надпись

  
  scale.set_scale(469.58);                          // Устанавливаем калибровочный коэффициент 
  scale.tare();                                     // Сбрасываем весы на 0
  myScale = round(scale.get_units(10));             // Запоминаем среднее значение без груза, но с учетом тары 
  
  Serial.println(0.00);                             // Обнуляем значение веса на мониторе порта
}

void loop() {
  scale.power_up();                                 // Отключаем энергосберегающий режим hx711
  if (round(scale.get_units(10)) != myScale) {      // Условие выполняется, если округленный до граммов вес отличается от последнего
    myScale = scale.get_units(20);                  // Запоминаем текущий вес
   
    if (myScale > 0.5)                              // Если вес не ничтожно мал
      Serial.println(myScale);                      // то выводим его
    else                                            // иначе
      Serial.println(0.00);                         // выводим нули
   
    myScale = round(myScale);                       // Запоминаем округленный текущий вес (для сравнения)
  }
  scale.power_down();                               // Включаем энергосберегающий режим hx711
  delay(500);                                       // Пауза на половину сек.
}
