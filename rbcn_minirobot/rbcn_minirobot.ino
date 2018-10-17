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

MotorDriverTA8428KClass MD0, MD1, MD2;


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

}

// Add the main program code into the continuous loop() function
void loop()
{


}
