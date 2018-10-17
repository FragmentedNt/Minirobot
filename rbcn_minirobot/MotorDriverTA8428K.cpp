// 
// 
// 

#include "MotorDriverTA8428K.h"


void MotorDriverTA8428KClass::init(byte pinA, byte pinB, bool brake = false, bool inverse = false, bool pwm_enable = true)
{
	this->pinA = pinA;
	this->pinB = pinB;
	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	this->brake = brake;
	this->inverse = inverse;
	this->pwm = pwm_enable;
	prev_power = 0;
	if (pwm)
	{
		analogWrite(pinA, 0);
		analogWrite(pinB, 0);
	}
	else
	{
		digitalWrite(pinA, LOW);
		digitalWrite(pinB, LOW);
	}
	TM0.DelayMicroseconds(100);
	set(0);
}

void MotorDriverTA8428KClass::set(short power)
{
	if (inverse)
		power *= -1;
	
	if (prev_power != power)
	{
		prev_power = power;
		if (pwm)
		{
			analogWrite(pinA, 0);
			analogWrite(pinB, 0);
		}
		else
		{
			digitalWrite(pinA, LOW);
			digitalWrite(pinB, LOW);
		}
		TM0.DelayMicroseconds(100);
	}

	if (power > 0)
	{
		if (power > 255)	power = 255;
		if (pwm)
		{
			analogWrite(pinA, power);
			analogWrite(pinB, 0);
		}
		else
		{
			digitalWrite(pinA, HIGH);
			digitalWrite(pinB, LOW);
		}
	}
	else if (power < 0)
	{
		if (power < -255)	power = -255;
		if (pwm)
		{
			analogWrite(pinA, 0);
			analogWrite(pinB, -power);
		}
		else
		{
			digitalWrite(pinA, LOW);
			digitalWrite(pinB, HIGH);
		}
	}
	else
	{
		if (brake)
		{
			if (pwm)
			{
				analogWrite(pinA, 255);
				analogWrite(pinB, 255);
			}
			else
			{
				digitalWrite(pinA, HIGH);
				digitalWrite(pinB, HIGH);
			}
		}
		else 
		{
			if (pwm)
			{
				analogWrite(pinA, 0);
				analogWrite(pinB, 0);
			}
			else
			{
				digitalWrite(pinA, LOW);
				digitalWrite(pinB, LOW);
			}
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="power"></param>
/// <param name="brake"></param>
void MotorDriverTA8428KClass::set(short power, byte brake)
{
	this->brake = brake;
	set(power);
}

MotorDriverTA8428KClass MD0, MD1, MD2;

