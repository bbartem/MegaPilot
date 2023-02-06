// Данный пример выводит символы с анимацией до и после слова.   //
                                                                 //
#include <Wire.h>                                                // Подключаем библиотеку для работы с аппаратной шиной I2C.
#include <iarduino_I2C_Matrix_8x8.h>                             // Подключаем библиотеку для работы с LED матрицей 8x8.
iarduino_I2C_Matrix_8x8 disp(0x09);                              // Объявляем объект disp для работы с LED матрицей 8x8, указывая её адрес на шине I2C.
                                                                 //
void setup(){                                                    //
    delay(500);                                                  // Ждём завершение переходных процессов связанных с подачей питания.
    disp.begin();                                                // Инициируем работу с LED матрицей 8x8.
}                                                                //
                                                                 //
void loop(){                                                     //
    disp.print('i', X8_FILLED_TOP);                              // Выводим символ 'i', с анимацией появления снизу-вверх из закрашенного фона.
    delay(300);                                                  //
    disp.print('A');                                             // Выводим символ 'A'.
    delay(300);                                                  //
    disp.print('r');                                             // Выводим символ 'r'.
    delay(300);                                                  //
    disp.print('d');                                             // Выводим символ 'd'.
    delay(300);                                                  //
    disp.print('u');                                             // Выводим символ 'u'.
    delay(300);                                                  //
    disp.print( char(105) );                                     // Выводим символ 'i', по коду этого символа.
    delay(300);                                                  //
    disp.print('n');                                             // Выводим символ 'n'.
    delay(300);                                                  //
    disp.print('o');                                             // Выводим символ 'o'.
    delay(300);                                                  //
    disp.fillScr(X8_TOP);                                        // Заливаем дисплей снизу-вверх.
}                                                                //