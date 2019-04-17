# PsxLib
A small and light lib for ESP32 and Ps2 Controller

To Use with PS1 and PS2 GamePad controllers with Arduino & c., Esp8266, Esp32 etc.
A light lib original written by: Kevin Ahrendt June 22nd, 2008 and modified following also libs of Bill Porter and Kompanets Konstantin (aka I2M)

	*  Connections: Example with Digital Pins 2, 4, 0, 15 and Ground
	*  GamePad Cable connected to micro by five pins. 
	*  Green   		ACK  -----------------|
	*  Blue    		Clock   ---- 2     Res 10K
	*  Yellow  		Attn    ---- 4        |
	*  Red     		VCC+ ------------------
	*  Black   		Ground  ---- Ground   |
	*  White   		Vibration    NC       |
	*  Orange  		Command ---- 0     Res 10K
	*  Brown   		Data    ---- 15 ------|
	*  Note: VCC Cable side connected with two R10K with Clock and Data Pins.
