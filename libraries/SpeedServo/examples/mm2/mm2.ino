#include <VarSpeedServo.h> 

VarSpeedServo myServo;            

void setup() 
{ 
  myServo.attach(9);
//  myServo.write(0);
}


void loop() 
{
  myServo.slowmove(0, 50);  // положение, скорость
  delay(10000);
  myServo.slowmove(180, 5);  // положение, скорость
  delay(5000);
}
