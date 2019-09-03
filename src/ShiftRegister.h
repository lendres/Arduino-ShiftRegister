/*
  ShiftRegister74HC595.h - Library for simplified control of 74HC595 shift registers.
  Created by Timo Denk (www.timodenk.com), Nov 2014.
  Additional information is available at http://shiftregister.simsso.de/
  Released into the public domain.
*/

/*
  Renamed to "ShiftRegister" and removed experimental code.  Added setAllHighNoUpdate
  and setAllLowNoUpdate. - LAE
*/

#ifndef ShiftRegister_h
#define ShiftRegister_h

#include "Arduino.h"

class ShiftRegister
{
public:
    ShiftRegister(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin);
    ~ShiftRegister();

    void setAll(const uint8_t* digitalValues);
    uint8_t* getAll(); 

    void set(int pin, uint8_t value);
	uint8_t get(int pin);

    void setNoUpdate(int pin, uint8_t value);
    
    void setAllLow();
	void setAllLowNoUpdate();

	void setAllHigh();
	void setAllHighNoUpdate();

	void updateRegisters();

private:
    int 		_numberOfShiftRegisters;
    int 		_clockPin;
    int 		_serialDataPin;
    int 		_latchPin;
    uint8_t* 	_digitalValues;
};

#endif