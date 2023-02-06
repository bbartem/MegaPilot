// Данный пример меняет адрес модуля на указанный в newAddress.  //
                                                                 //
uint8_t newAddress = 0x10;                                       // Назначаемый модулю адрес.
                                                                 //
#include <Wire.h>                                                // Подключаем библиотеку для работы с аппаратной шиной I2C.
#include <iarduino_I2C_Matrix_8x8.h>                             // Подключаем библиотеку для работы с LED матрицей 8x8.
iarduino_I2C_Matrix_8x8 disp;                                    // Объявляем объект disp для работы с функциями и методами библиотеки iarduino_I2C_Matrix_8x8.
                                                                 // Если при объявлении объекта указать адрес, например, disp(0xBB), то пример будет работать с тем модулем, адрес которого был указан.
void setup(){                                                    //
    Serial.begin(9600);                                          //
    while(!Serial){;}                                            //
    delay(500);                                                  // Ждём завершение переходных процессов связанных с подачей питания.
    if( disp.begin() ){                                          // Инициируем работу с LED матрицей 8x8.
        Serial.print("На шине I2C найден модуль с адресом 0x");  //
        Serial.print( disp.getAddress(), HEX );                  // Выводим текущий адрес модуля.
        Serial.print(" который является LED матрицей 8x8\r\n");  //
        if( disp.changeAddress(newAddress) ){                    // Меняем адрес модуля на newAddress.
            Serial.print("Адрес модуля изменён на 0x");          //
            Serial.println( disp.getAddress(), HEX );            // Выводим текущий адрес модуля.
        }else{                                                   //
            Serial.println("Адрес модуля изменить не удалось!"); //
        }                                                        //
    }else{                                                       //
        Serial.println("Модуль LED матрица 8x8 не найден!");     //
    }                                                            //
}                                                                //
                                                                 //
void loop(){                                                     //
}                                                                //
