/*
  Shift595.cpp - Library for easily working with 74HC595 Shift Registers
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

#include "Arduino.h"
#include "Shift595.h"

// constructor

Shift595::Shift595(int dataPin, int latchPin, int clockPin, int numOfRegisters)
{
    // initialize instance variables
    _dataPin = dataPin;
    _latchPin = latchPin;
    _clockPin = clockPin;
	_numOfPins = numOfRegisters*8;
  
    // initialize the rest of library
    pinMode(_dataPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
	clearRegisters();
}

// public functions

void Shift595::clearRegisters(void)
{
	for(int i = _numOfPins-1; i>=0; i--)
	{
		_registers[i] = LOW;
	}
	Serial.println();
}

void Shift595::setRegisterPin(int index, boolean data)
{	
	_registers[index] = data;
	writeRegisters();

}

// private functions

void Shift595::writeRegisters(void)
{
	digitalWrite(_latchPin, LOW);       	// unlatch from the 595 to update registers	
	for(int i = _numOfPins-1; i>=0; i--)
	{
		digitalWrite(_clockPin, LOW);   	//  bring the clock pin LOW, allowing us to shift new
											//  data onto the register
		
		boolean data = _registers[i];		//  shift the new data onto the register
		digitalWrite(_dataPin, data);	
		
		digitalWrite(_clockPin, HIGH);		// bring the clock pin HIGH to complete shift
	}	
	digitalWrite(_latchPin, HIGH);      	// re-latch to the 595 to output changes
	
	Serial.println();
}
