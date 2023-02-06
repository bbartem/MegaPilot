/*
  Shift595.h -   Library for easily working with 74HC595 Shift Registers
				 with the goal of expanding the number of Digital Outputs
                 Aurdino can support. This library allows individual
                 control of the shift register pins with a single command
				 much like a native digital output port.

Copyright (c) 2014 Bradley Tompkins

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef Shift595_h
#define Shift595_h

#include "Arduino.h"

// The constant max595s defines the maximum number of 74HC595's this library supports;
// change it if you need more, or less. The default settings allow eight daisy-chained 595's,
// creating an additional 64 Digital Output pins from just three of your Aurdino's native pins.

#define max595s 8 

class Shift595
{
  public:
    Shift595(int, int, int, int);
    void clearRegisters(void);
	void setRegisterPin(int, boolean);

  private:	  
    int _dataPin;     // pin 14 on the 74HC595
	int _latchPin;    // pin 12 on the 74HC595
	int _clockPin;    // pin 11 on the 74HC595
	
	int _numOfPins;
	
	void writeRegisters(void); 
	
	boolean _registers[max595s*8];
};

#endif

