// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA

#include "HX711.h"
// Скетч выводит в монитoр порта Arduino IDE калибровочный коэффициент весов для функции set_scale()
// Впишите известный вам вес предмета в граммах в строку с указывающим комментарием в нижней части этого скетча (рекомендуется от 500 до 1000 граммов)
// Загрузите скетч в Arduino
// Убедитесь, что на весах нет груза
// Запустите монитор порта
// В течение 5-и секунд после появления надписи Ready поместите на весы предмет, вес которого вам известен
// Запомните значение set_scale - это ваш калибровочный коэффициент

// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0
HX711 scale(A1, A0);
float myScale;
float myRatio;

void setup() {
  Serial.begin(9600);
  scale.set_scale();
  scale.tare();
  Serial.println("Ready");
  delay(5000);
  myScale = scale.get_units(10);
  myRatio = myScale/970;          // В этой строке необходимо заменить число на известный вам вес в граммах
  Serial.print("set_scale: ");
  Serial.println(myRatio);
}

void loop() {

}
