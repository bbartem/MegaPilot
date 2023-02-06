 
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Basic.h>
  LCD5110 LCD(8,9,10,11,12);
 extern uint8_t SmallFont[];
 extern uint8_t MediumNumbers[];
 extern uint8_t BigNumbers[];

void setup()
{
  LCD.InitLCD();


}


void loop()
{
    LCD.setFont(SmallFont);
    LCD.print("ArduBlock", 12, 13);
     
    LCD.setFont(SmallFont);
    LCD.printNumI("123", 12, 13, 2, '0');
     
    LCD.setFont(MediumNumbers);
    LCD.printNumI("123", 12, 13, 2, '0');
     
    LCD.setFont(BigNumbers);
    LCD.printNumI("123", 12, 13, 2, '0');
}


//12  x

//13  y
