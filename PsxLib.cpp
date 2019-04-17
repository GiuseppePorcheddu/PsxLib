/*  PSXLIB Controller Decoder Simple & Compact Library (PsxLib.cpp)
	To Use with PS1 and PS2 GamePad controllers with Arduino & c., Esp8266, Esp32 etc.
	
	Original written by: Kevin Ahrendt June 22nd, 2008
	Modified by Giuseppe Porcheddu November 5ft, 2018 to be used with Espressif ESP micro series
	Following also libs of Bill Porter and Kompanets Konstantin (aka I2M)

	*  Connections: Example with Digital Pins 2, 4, 0, 15 and Ground
	*  GamePad Cable connected to micro by five pins. 
	*  Green   		ACK  -----------------|
	*  Blue    		Clock   ---- 2 ---- Res 10K
	*  Yellow  		Attn    ---- 4        |
	*  Red     		VCC+ ------------------
	*  Black   		Ground  ---- Ground   |
	*  White   		Vibration    NC       |
	*  Orange  		Command ---- 0 ---- Res 10K
	*  Brown   		Data    ---- 15 ------|
	*  Note: VCC Psx side connected with two R10K with Clock and Data Pins.
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "PsxLib.h"

Psx::Psx() { };	// Class Psx

byte Psx::shift(byte _dataOut)	{	// Does the actual shifting, both in and out simultaneously
	_dataIn = 0;

	for (byte i = 0; i < 8; i++)	{
		
		if ( _dataOut & (1 << i) ) 
			digitalWrite(_cmndPin, HIGH);	// Writes out the _dataOut bits
		else 
			digitalWrite(_cmndPin, LOW);

		digitalWrite(_clockPin, LOW);
		delayMicroseconds(_delay);

		if ( digitalRead(_dataPin) ) {	// Reads the data pin
			_dataIn |= _BV(i);			// Giuseppe Shift the read into _dataIn (align to the others libs)
		}
		
		digitalWrite(_clockPin, HIGH);
		delayMicroseconds(_delay);
	}
	return _dataIn;
}


void Psx::setupPins(byte dataPin, byte cmndPin, byte attPin, byte clockPin, byte delay) {
	pinMode(dataPin, INPUT);
	digitalWrite(dataPin, HIGH);	// Turn on internal pull-up
	pinMode(attPin, OUTPUT);
	digitalWrite(_attPin, HIGH);
	pinMode(cmndPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	digitalWrite(_clockPin, HIGH);

	_dataPin = dataPin;
	_cmndPin = cmndPin;
	_attPin = attPin;
	_clockPin = clockPin;
	_delay = delay;
}


unsigned int Psx::read() {
	digitalWrite(_attPin, LOW);

	shift(0x01);
	shift(0x42);
	shift(0xFF);

	_data1 = ~shift(0xFF);
	_data2 = ~shift(0xFF);

	digitalWrite(_attPin, HIGH);
	
	_last_buttons = _dataOut;	// Giuseppe: Save Old Value

	_dataOut = (_data2 << 8) | _data1;

	return _dataOut;
}

bool Psx::button(unsigned int button) {
  return ((_dataOut & button) > 0);
}

bool Psx::newButtonState() {
  return ((_last_buttons ^ _dataOut) > 0);
}

bool Psx::buttonNewState(unsigned int button) {
  return (((_last_buttons ^ _dataOut) & button) > 0);
}

