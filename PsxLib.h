/*  PSXLIB Controller Decoder Library (PsxLib.h)
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
	*  Note: VCC Cable side connected with two R10K with Clock and Data Pins.
	
	Controller protocol implemented using Andrew J McCubbin's analysis.
	http://www.gamesx.com/controldata/psxcont/psxcont.htm
	
	Shift command is based on tutorial examples for ShiftIn and ShiftOut
	functions both written by Carlyn Maw and Tom Igoe
	http://www.arduino.cc/en/Tutorial/ShiftIn
	http://www.arduino.cc/en/Tutorial/ShiftOut

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


#ifndef PSXLIB_H
	#define PSXLIB_H

#if ARDUINO > 22
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


//These are our button constants
#define PSB_IDLE      	0x0000
#define PSB_SELECT      0x0001
#define PSB_START       0x0008
#define PSB_L2          0x0100
#define PSB_R2          0x0200
#define PSB_L1          0x0400
#define PSB_R1          0x0800
#define PSB_GREEN       0x1000
#define PSB_RED         0x2000
#define PSB_BLUE        0x4000
#define PSB_PINK        0x8000

// Left Keys Pad and Stiks
#define PSB_PAD_UP      0x0010
#define PSB_PAD_RIGHT   0x0020
#define PSB_PAD_DOWN    0x0040
#define PSB_PAD_LEFT    0x0080

#define PSB_LSTIK_LEFT 	0x0010
#define PSB_LSTIK_DOWN  0x0020
#define PSB_LSTIK_RIGHT 0x0040
#define PSB_LSTIK_UP    0x0080

// Right Keys Pad and Stiks
#define PSB_TRIANGLE    0x1000
#define PSB_CIRCLE      0x2000
#define PSB_CROSS       0x4000
#define PSB_SQUARE      0x8000

#define PSB_RSTIK_LEFT 	0x1000
#define PSB_RSTIK_DOWN  0x2000
#define PSB_RSTIK_RIGHT 0x4000
#define PSB_RSTIK_UP    0x8000

class Psx {
	public:
		Psx();
		void setupPins(byte dataPin, byte cmndPin, byte attPin, byte clockPin, byte delay);
					// Data Pin #, CMND Pin #, ATT Pin #, CLK Pin #, Delay
					// Delay is how long the clock goes without changing state in Microseconds. 
					// It can be lowered to increase response, but if it is too low it may cause 
					// glitches and have some keys spill over with false-positives. 
					// A regular PSX controller works fine at 50 uSeconds.

		unsigned int read();		// Returns the status of the button presses in an unsignd int.
									// The value returned corresponds to each key as defined above.
		bool newButtonState();		// Giuseppe: will be true if any button was pressed
		bool buttonNewState(unsigned int);	// Giuseppe: will be true if button changed state
		bool button(unsigned int);	// Giuseppe: will be TRUE if button is being pressed

	private:
		byte shift(byte _dataOut);

		byte _dataPin;
		byte _cmndPin;
		byte _attPin;
		byte _clockPin;

		byte _delay;
		boolean _temp;
		byte _dataIn;

		byte _data1;
		byte _data2;
		unsigned int _dataOut;
		unsigned int _last_buttons;		// Giuseppe: Last Button Pressed
};

#endif