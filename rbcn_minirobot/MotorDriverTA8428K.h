// MotorDriverTA8428K.h

#ifndef _MOTORDRIVERTA8428K_h
#define _MOTORDRIVERTA8428K_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TM0.h"

class MotorDriverTA8428KClass
{
 private:
	 byte pinA, pinB;
	 bool brake;
	 bool inverse;
	 bool hardwarePWM;
	 short prev_power;

	 // software pwm
	 short cycle;
	 short now;
 protected:


 public:
	void init(byte pinA, byte pinB, bool brake = false, bool inverse = false, bool hardwarePWM = true);
	void set(short power);
	void set(short power, byte brake);
};

#endif

