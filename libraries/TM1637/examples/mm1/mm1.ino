
#include "TM1637.h"
#define CLK 9 
#define DIO 8
TM1637 tm1637(CLK,DIO);
void setup()
{
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);

//   Timer1.initialize(10000);//timing for 10ms
//  Timer1.attachInterrupt(TimingISR);
}
void loop()
{

//0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
  //  tm1637.display(3,15);
 tm1637.display(1234);
//tm1637.display(0.0);
tm1637.point(POINT_ON);
delay(1000);
tm1637.display(1234);
tm1637.point(POINT_OFF);
delay(1000);
  }

