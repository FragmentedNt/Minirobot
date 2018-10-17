// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       rbcn_minirobo_controller.ino
    Created:	2018/10/17 23:01:48
    Author:     DESKTOP-IQIF1R0\USR-xx
*/

// Define User Types below here or use a .h file
//
#include "Controller.h"
#include "TM0.h"

// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(115200);
	Controller.init(Serial);

	TM0.init();

	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(5, INPUT_PULLUP);
	pinMode(6, INPUT_PULLUP);
	pinMode(7, INPUT_PULLUP);
	pinMode(8, INPUT_PULLUP);
	pinMode(9, INPUT_PULLUP);
}

// Add the main program code into the continuous loop() function
void loop()
{
	blinkLED();

	Controller.d2(!digitalRead(2));
	Controller.d3(!digitalRead(3));
	Controller.d4(!digitalRead(4));
	Controller.d5(!digitalRead(5));
	Controller.d6(!digitalRead(6));
	Controller.d7(!digitalRead(7));
	Controller.d8(!digitalRead(8));
	Controller.d9(!digitalRead(9));

	Controller.sendConData();
	TM0.Delay(9);
}

void printTimeSpan()
{
	static unsigned long prev_time = 0, current_time = 0;
	current_time = TM0.Micros();
	Serial.println(current_time - prev_time);
	prev_time = TM0.Micros();
}

void blinkLED()
{
	static int ms = 0;
	int mi = TM0.Millis();
	if (mi - ms > 500)
	{
		ms = mi;
		PINB |= _BV(5);	// Arduino nanoのPB5(D13番)に接続されているLEDを操作
						// AVRの仕様でPINxに書き込むと出力が反転する(通常の出力レジスタはPORTx)
	}
}