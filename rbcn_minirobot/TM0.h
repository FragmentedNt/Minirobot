// TM0.h

#ifndef _TM0_h
#define _TM0_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TM0Class
{
 protected:
	 unsigned int prescaler;
	 char mode;
	 unsigned int factor0;
	 unsigned int factor1;

 public:
	void init();
	void Delay(unsigned long ms);
	void DelayMicroseconds(unsigned int us);
	unsigned long Millis();
	unsigned long Micros();
};

extern TM0Class TM0;

#endif

