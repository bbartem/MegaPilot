#include <Wire.h>
#include "ASOLED.h"
long i;
long j;
void setup() {
 LD.init();  //initialze OLED display
LD.clearDisplay(); 


}

void loop() {


   //     LD.printString_6x8("0123456789!\"#$%&'()*+", 0, 0);
     //   LD.printString_6x8(",-./:;<=>?@[\\]^_`{|}~", 0, 1);
       // LD.printString_6x8("ABCDEFGHIJKLMNOPQRSTU", 0, 2);
  //      LD.printString_6x8("VWXYZabcdefghijklmnop",0, 3);
    //    LD.printString_6x8("qrstuvwxyzАБВГДЕЁЖЗИЙ", 0, 4);
    //    LD.printString_6x8("КЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ", 0, 5);
    //    LD.printString_6x8("Яабвгдеёжзийклмнопрст", 0, 6);
    //    LD.printString_6x8("уфхцчшщъыьэюяЇїЎў§°±µ", 0, 7);
 //LD.printString_6x8("Small ", 0, 0);
i = 2;
j = 3;
 //LD.printNumber((i), 0, 0); 

// LD.clearDisplay();
}
