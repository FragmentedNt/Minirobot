// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       rbcn_minirobot.ino
    Created:	2018/10/17 19:39:43
    Author:     DESKTOP-IQIF1R0\USR-xx
*/

// Define User Types below here or use a .h file
//
#include "TM0.h"
#include "MotorDriverTA8428K.h"


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

MotorDriverTA8428KClass MD0, MD1, MD2, MD3;


// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(115200);
	pinMode(13, OUTPUT);
	TCCR0B = (TCCR0B & 0b11111000) | 0x02;
	TCCR1B = (TCCR1B & 0b11111000) | 0x02;
	TCCR2B = (TCCR2B & 0b11111000) | 0x02;
	TM0.init();
	MD0.init(5, 6, true);
	MD1.init(9, 10, true, true);
	MD2.init(3, 11, true);
	MD3.init(20, 21, true, false, false);

}

// Add the main program code into the continuous loop() function
void loop()
{
	blinkLED();

	TM0.Delay(9);
	//printTimeSpan();
	demo();
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

void demo()
{
	static int ms = 0;
	int mi = TM0.Millis();
	if (mi - ms < 2000)
	{
		MD0.set(0);
		MD1.set(0);
		MD2.set(0);
		MD3.set(0);
	}
	else if (mi - ms < 4000)
	{
		MD0.set(100);
		MD1.set(100);
		MD2.set(100);
		MD3.set(100);
	}
	else if (mi - ms < 6000)
	{
		MD0.set(0);
		MD1.set(0);
		MD2.set(0);
		MD3.set(0);
	}
	else if (mi - ms < 8000)
	{
		MD0.set(-100);
		MD1.set(-100);
		MD2.set(-100);
		MD3.set(-100);
	}
	else
	{
		ms = mi;
	}
}