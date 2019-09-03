/*
  ShiftRegister74HC595.cpp - Library for simplified control of 74HC595 shift registers.
  Created by Timo Denk (www.timodenk.com), Nov 2014.
  Additional information is available at http://shiftregister.simsso.de/
  Released into the public domain.
*/

#include "Arduino.h"
#include "ShiftRegister.h"


// ShiftRegister constructor.
ShiftRegister::ShiftRegister(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin)
{
    // Set attributes.
    _numberOfShiftRegisters = numberOfShiftRegisters;

    _clockPin = clockPin;
    _serialDataPin = serialDataPin;
    _latchPin = latchPin;

    // Define pins as outputs.
    pinMode(clockPin, OUTPUT);
    pinMode(serialDataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);

    // Set pins low.
    digitalWrite(clockPin, LOW);
    digitalWrite(serialDataPin, LOW);
    digitalWrite(latchPin, LOW);

    // Allocates the specified number of bytes and initializes them to zero.
    _digitalValues = (uint8_t *)malloc(numberOfShiftRegisters * sizeof(uint8_t));
    memset(_digitalValues, 0, numberOfShiftRegisters * sizeof(uint8_t));

    // Reset shift register.
    updateRegisters();
}


// ShiftRegister destructor.
// The memory allocated in the constructor is also released.
ShiftRegister::~ShiftRegister()
{
    free(_digitalValues);
}


// Set all pins of the shift registers at once.
// digitalValues is a uint8_t array where the length is equal to the number of shift registers.
void ShiftRegister::setAll(const uint8_t* digitalValues)
{
    memcpy( _digitalValues, digitalValues, _numberOfShiftRegisters);   // dest, src, size
    updateRegisters();
}


// Retrieve all states of the shift registers' output pins.
// The returned array's length is equal to the numbe of shift registers.
uint8_t* ShiftRegister::getAll()
{
    return _digitalValues; 
}


// Set a specific pin to either HIGH (1) or LOW (0).
// The pin parameter is a positive, zero-based integer, indicating which pin to set.
void ShiftRegister::set(int pin, uint8_t value)
{
    setNoUpdate(pin, value);
    updateRegisters();
}

// Returns the state of the given pin.
// Either HIGH (1) or LOW (0)
uint8_t ShiftRegister::get(int pin)
{
	return (_digitalValues[pin / 8] >> (pin % 8)) & 1;
}


// Equivalent to set(int pin, uint8_t value), except the physical shift register is not updated.
// Should be used in combination with updateRegisters().
void ShiftRegister::setNoUpdate(int pin, uint8_t value)
{
    if (value == 1)
    {
        _digitalValues[pin / 8] |= 1 << (pin % 8);
    }
    else
    {
        _digitalValues[pin / 8] &= ~(1 << (pin % 8));
    }
}


// Sets all pins of all shift registers to LOW (0).
void ShiftRegister::setAllLow()
{
	setAllLowNoUpdate();
	updateRegisters();
}


// Sets all pins of all shift registers to LOW (0) without updating.  Good
// for reseting to a known state before making certain pins HIGH (1).
void ShiftRegister::setAllLowNoUpdate()
{
	for (int i = 0; i < _numberOfShiftRegisters; i++)
	{
		_digitalValues[i] = 0;
	}
}


// Sets all pins of all shift registers to HIGH (1).
void ShiftRegister::setAllHigh()
{
	setAllHighNoUpdate();
	updateRegisters();
}


// Sets all pins of all shift registers to HIGH (1) without updating.  Good
// for reseting to a known state before making certain pins LOW (0).
void ShiftRegister::setAllHighNoUpdate()
{
    for (int i = 0; i < _numberOfShiftRegisters; i++)
    {
        _digitalValues[i] = 255;
    }
    updateRegisters();
}


// Updates the shift register pins to the stored output values.
// This is the function that actually writes data into the shift registers of the 74HC595
void ShiftRegister::updateRegisters()
{
	for (int i = _numberOfShiftRegisters - 1; i >= 0; i--)
	{
		shiftOut(_serialDataPin, _clockPin, MSBFIRST, _digitalValues[i]);
	}

	digitalWrite(_latchPin, HIGH);
	digitalWrite(_latchPin, LOW);
}