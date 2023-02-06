// Данный пример постоянно поворачивает дисплей на 90°.          //
                                                                 // Создаём изображение "капля".
const byte image[8] = {0b00111100,                               //                       ####  
                       0b01111110, /* Посмотрите, изображение */ //                      ###### 
                       0b11001111, /* можно увидеть прямо в   */ //                     ##  ####
                       0b10000110, /* коде!!!                 */ //                     #    ## 
                       0b10000000,                               //                     #       
                       0b10000000,                               //                     #       
                       0b01000000,                               //                      #      
                       0b00100000};                              //                       #     
#include <Wire.h>                                                // Подключаем библиотеку для работы с аппаратной шиной I2C.
#include <iarduino_I2C_Matrix_8x8.h>                             // Подключаем библиотеку для работы с LED матрицей 8x8.
iarduino_I2C_Matrix_8x8 disp(0x09);                              // Объявляем объект disp для работы с LED матрицей 8x8, указывая её адрес на шине I2C.
                                                                 //
void setup(){                                                    //
    delay(500);                                                  // Ждём завершение переходных процессов связанных с подачей питания.
    disp.begin();                                                // Инициируем работу с LED матрицей 8x8.
    disp.drawImage(image);                                       // Выводим на дисплей изображение массива image.
}                                                                //
                                                                 // Далее поворачиваем дисплей, значит будут повёрнуты не только имеющиеся, но и вновь выводимые данные.
void loop(){                                                     //
    disp.angle(0);   delay(100);                                 // Поворачиваем дисплей на 0°   и ждём 0.1 секунду.
    disp.angle(90);  delay(100);                                 // Поворачиваем дисплей на 90°  и ждём 0.1 секунду.
    disp.angle(180); delay(100);                                 // Поворачиваем дисплей на 180° и ждём 0.1 секунду.
    disp.angle(270); delay(100);                                 // Поворачиваем дисплей на 270° и ждём 0.1 секунду.
}                                                                //