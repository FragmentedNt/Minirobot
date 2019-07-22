// Define User Types below here or use a .h file
//
#include "Controller.h"
#include "TM0.h"
#include "MotorDriverTA8428K.h"

#define SW_UP A0
#define SW_DOWN A1
#define SW_OPEN A2
#define SW_CLOSE A3

// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

MotorDriverTA8428KClass LeftMD, RightMD, UpMD, HandMD;


// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(115200);

	Controller.init(Serial);

	pinMode(SW_UP, INPUT_PULLUP);
	pinMode(SW_DOWN, INPUT_PULLUP);
	pinMode(SW_OPEN, INPUT_PULLUP);
	pinMode(SW_CLOSE, INPUT_PULLUP);

	pinMode(13, OUTPUT);

	TCCR0B = (TCCR0B & 0b11111000) | 0x04;
	TCCR1B = (TCCR1B & 0b11111000) | 0x04;
	TCCR2B = (TCCR2B & 0b11111000) | 0x04;
	TM0.init();
	LeftMD.init(9, 10, true);
	RightMD.init(5, 6, true, true);
	//UpMD.init(3, 11, true, true);
	//HandMD.init(19, 18, true, true, false);
	HandMD.init(3, 11, true, true);
	UpMD.init(19, 18, true, false, false);
}

// Add the main program code into the continuous loop() function
void loop()
{
	static bool hand_is_open = true;
	static int hand_changed_time = 0;
	static int hand_changed_count = 0;

	blinkLED();
	Controller.receiveConData();

	if (Controller.leftForward())
		LeftMD.set(100);
	else if (Controller.leftBack())
		LeftMD.set(-100);
	else
		LeftMD.set(0);

	if (Controller.rightForward())
		RightMD.set(100);
	else if (Controller.rightBack())
		RightMD.set(-100);
	else
		RightMD.set(0);

	if (Controller.up())
	{
		if (!digitalRead(SW_UP))
			UpMD.set(0);
		else
			UpMD.set(255);
	}
	else if (Controller.down())
	{
		if (!digitalRead(SW_DOWN))
			UpMD.set(0);
		else
			UpMD.set(-255);
	}
	else
	{
		UpMD.set(0);
	}


	if (Controller.rise_open())
	{
		hand_is_open = true;
		hand_changed_time = TM0.Millis();
		hand_changed_count = 0;
	}
	if (Controller.rise_close())
	{
		hand_is_open = false;
		hand_changed_time = TM0.Millis();
		hand_changed_count = 0;
	}

	//if (hand_is_open)
	//{
	//	if (!digitalRead(SW_OPEN))
	//		HandMD.set(0);
	//	else if (TM0.Millis() - hand_changed_time > 1500)
	//		HandMD.set(50);
	//	else
	//		HandMD.set(255);
	//}
	//else
	//{
	//	if (!digitalRead(SW_CLOSE))
	//		HandMD.set(0);
	//	else if (TM0.Millis() - hand_changed_time > 1500)
	//		HandMD.set(-50);
	//	else
	//		HandMD.set(-255);
	//}

	if (hand_is_open)
	{
		if (!digitalRead(SW_OPEN))
			HandMD.set(0);
		else if (hand_changed_count > 100)
			HandMD.set(50);
		else
		{
			HandMD.set(255);
			hand_changed_count++;
		}
	}
	else
	{
		if (!digitalRead(SW_CLOSE))
			HandMD.set(0);
		else if (hand_changed_count > 100)
			HandMD.set(-50);
		else
		{
			HandMD.set(-255);
			hand_changed_count++;
		}
	}


	TM0.Delay(9);
	//printTimeSpan();
	//demo();

	if (Controller.Error())
		Serial.println("Error");
	else
		Controller.debug();
	debugSW();
	if (hand_is_open)
		Serial.print("HOpen");
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

void debugSW()
{
	if (!digitalRead(SW_UP))
		Serial.print(" SW_UP");
	if (!digitalRead(SW_DOWN))
		Serial.print(" SW_DOWN");
	if (!digitalRead(SW_OPEN))
		Serial.print(" SW_OPEN");
	if (!digitalRead(SW_CLOSE))
		Serial.print(" SW_CLOSE");
}

void demo()
{
	static int ms = 0;
	int mi = TM0.Millis();
	if (mi - ms < 2000)
	{
		LeftMD.set(0);
		RightMD.set(0);
		UpMD.set(0);
		HandMD.set(0);
	}
	else if (mi - ms < 4000)
	{
		LeftMD.set(100);
		RightMD.set(100);
		UpMD.set(100);
		HandMD.set(100);
	}
	else if (mi - ms < 6000)
	{
		LeftMD.set(0);
		RightMD.set(0);
		UpMD.set(0);
		HandMD.set(0);
	}
	else if (mi - ms < 8000)
	{
		LeftMD.set(-100);
		RightMD.set(-100);
		UpMD.set(-100);
		HandMD.set(-100);
	}
	else
	{
		ms = mi;
	}
}
