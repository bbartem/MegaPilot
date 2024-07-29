[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverOS.svg?color=brightgreen)](https://github.com/GyverLibs/GyverOS/releases/latest/download/GyverOS.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverOS.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverOS)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverOS?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverOS
Библиотека лёгкого диспетчера задач для Arduino
- Лёгкий вес
- Статическое выбираемое количество задач
- Возможность остановки, отключения и прямого вызова задач
- Вычисление времени до ближайшей задачи (для сна на этот период)
- Встроенный бенчмарк: время выполнения задачи и загруженность процессора
- Алгоритм работает на системном таймере millis()

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverOS** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverOS/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
```cpp
GyverOS<5> OS;	// указать макс. количество задач
```

<a id="usage"></a>
## Использование
```cpp
void setMicros(bool mode);          // включить микросекундный режим (true)
void tick();                        // тикер. Вызывать как можно чаще
void attach(int num, void (*handler)(), uint32_t prd = 0);  // подключить функцию обработчик задачи
void detach(int num);               // отключить функцию обработчик задачи
void setPeriod(int num, uint32_t prd);  // установить период для задачи
void start(int num);                // запустить задачу
void restart(int num);              // перезапустить задачу
void stop(int num);                 // остановить задачу
void exec(int num);                 // вызвать задачу
uint32_t getLeft();                 // получить время до ближайшей задачи

// ====== БЕНЧМАРК ======
void attachLoopTime(int num);       // подключить счётчик времени выполнения задачи и сбросить максимум
void detachLoopTime();              // отключить счётчик времени выполнения задачи
uint32_t getLoopTime();             // получить текущее время выполнения выбранной ранее задачи в мкс
uint32_t getMaxLoopTime();          // получить максимальное время выполнения выбранной ранее задачи в мкс
void enableLoad(uint32_t loadp);    // включить измерение загруженности процессора за указанный период в мс
void disableLoad();                 // отключить измерение загруженности процессора
int getLoad();                      // получить загруженность процессора в процентах

// === ДЕФАЙНЫ НАСТРОЕК ===
// объявлять ПЕРЕД подключением библиотеки
#define OS_BENCH    // подключить модуль бенчмарка (тест производительности)
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
// демо диспетчера задач

#include <GyverOS.h>
GyverOS<5> OS;	// указать макс. количество задач

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  // подключаем задачи (порядковый номер, имя функции, период в мс)
  OS.attach(0, f1, 400);
  OS.attach(1, f2, 1000);
  OS.attach(2, f3, 200);
  
  //OS.detach(0);         // отключить задачу 0
  //OS.setPeriod(0, 200); // сменить период задачи 0 на 200 мс
  //OS.start(0);          // запустить задачу 0
  //OS.stop(0);           // остановить задачу 0
  //OS.exec(0);           // выполнить задачу 0 сейчас
}

void loop() {
  OS.tick();	// вызывать как можно чаще, задачи выполняются здесь
  
  // OS.getLeft() возвращает время в мс до ближайшей задачи
  // на это время можно усыпить МК, например при помощи narcoleptic или GyverPower
  // для примера просто поставим delay на это время
  delay(OS.getLeft());
}

// обработчики задач
void f1() {
  // выводит свой период в порт
  static uint32_t ms;
  Serial.println(millis() - ms);
  ms = millis();
}

void f2() {
  static uint32_t ms;
  // выводит свой период в порт
  Serial.println(millis() - ms);
  ms = millis();
}

void f3() {
  // выводит свой период в порт и  мигает светодиодом на D13
  digitalWrite(13, !digitalRead(13));
  static uint32_t ms;
  Serial.println(millis() - ms);
  ms = millis();
}
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 - добавил микросекундный режим
- v1.2 - внёс микросекундный режим в класс
- v1.2.1 - повышена стабильность

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
