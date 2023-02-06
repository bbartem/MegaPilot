#include <Shift595.h>

#define   dataPin          2      // pin 14 on the 74HC595
#define   latchPin          13      // pin 12 on the 74HC595
#define   clockPin          4      // pin 11 on the 74HC595

#define   numOfRegisters    1      // number of shift registers present

Shift595 Shifter(dataPin, latchPin, clockPin, numOfRegisters);

void setup(){}

void loop()
{
  Shifter.setRegisterPin(0, HIGH);  delay(300);
  Shifter.setRegisterPin(1, HIGH);delay(300);
  Shifter.setRegisterPin(2, HIGH);delay(300);
  Shifter.setRegisterPin(3, HIGH); delay(300);
  Shifter.setRegisterPin(4, HIGH);delay(300);
  Shifter.setRegisterPin(5, HIGH);delay(300);
  Shifter.setRegisterPin(6, HIGH);delay(300);
  Shifter.setRegisterPin(7, HIGH);delay(300);

 
 // delay(1000); 
  Shifter.setRegisterPin(0, LOW);delay(300);
  Shifter.setRegisterPin(1, LOW);delay(300);
  Shifter.setRegisterPin(2, LOW);delay(300);
  Shifter.setRegisterPin(3, LOW); delay(300);
  Shifter.setRegisterPin(4, LOW);delay(300);
  Shifter.setRegisterPin(5, LOW);delay(300);
  Shifter.setRegisterPin(6, LOW);delay(300);
  Shifter.setRegisterPin(7, LOW);delay(300);

  //delay(1000);

   
}
