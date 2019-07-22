// 
// 
// 

#include "TM0.h"

void TM0Class::init()
{
	switch (TCCR0B & 0b00000111)
	{
	case 0b001:
		prescaler = 1;
		mode = 0;
		break;

	case 0b010:
		prescaler = 8;
		mode = 0;
		break;

	case 0b011:
		prescaler = 64;
		mode = 0;
		break;

	case 0b100:
		prescaler = 256;
		mode = 1;
		break;

	case 0b101:
		prescaler = 1024;
		mode = 1;
		break;

	default:
		prescaler = 64;
		mode = 0;
		break;
	}
	factor0 = 64 / prescaler;
	factor1 = prescaler / 64;
}

void TM0Class::Delay(unsigned long ms)
{
	switch (mode)
	{
	case 0:
		delay(ms * factor0);
		break;
	
	case 1:
		delay(ms / factor1);
		break;
	}
}

void TM0Class::DelayMicroseconds(unsigned int us)
{
	if (us < 16383)
		delayMicroseconds(us);
	else
		Delay(us / 1000);
}

unsigned long TM0Class::Millis()
{
	switch (mode)
	{
	case 0:
		return millis() / factor0;
		break;

	case 1:
		return millis() * factor1;
		break;
	}
}

unsigned long TM0Class::Micros()
{
	switch (mode)
	{
	case 0:
		return micros() / factor0;
		break;

	case 1:
		return micros() * factor1;
		break;
	}
}

TM0Class TM0;

