// 
// 
// 

#include "MotorDriverTA8428K.h"


void MotorDriverTA8428KClass::init(byte pinA, byte pinB, bool brake = false, bool inverse = false, bool hardwarePWM = true)
{
	this->pinA = pinA;
	this->pinB = pinB;
	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	this->brake = brake;
	this->inverse = inverse;
	this->hardwarePWM = hardwarePWM;

	cycle = 20;
	now = 0;

	prev_power = 0;
	if (hardwarePWM)
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
		if (hardwarePWM)
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
		if (hardwarePWM)
		{
			analogWrite(pinA, power);
			analogWrite(pinB, 0);
		}
		else
		{
			//if (now / cycle < power / 255)�F�����^�Ȃ̂ł���͂܂����C�Ƃ������Ƃŉ��Ɏ��ό`
			if (now * 255 < cycle * power)
			{
				digitalWrite(pinA, HIGH);
				digitalWrite(pinB, LOW);
			}
			else
			{
				digitalWrite(pinA, LOW);
				digitalWrite(pinB, LOW);
			}
		}
	}
	else if (power < 0)
	{
		if (power < -255)	power = -255;
		if (hardwarePWM)
		{
			analogWrite(pinA, 0);
			analogWrite(pinB, -power);
		}
		else
		{
			if (now * 255 < cycle * -power)
			{
				digitalWrite(pinA, LOW);
				digitalWrite(pinB, HIGH);
			}
			else
			{
				digitalWrite(pinA, LOW);
				digitalWrite(pinB, LOW);
			}
		}
	}
	else
	{
		if (brake)
		{
			if (hardwarePWM)
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
			if (hardwarePWM)
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

	now++;
	if (now > cycle)
		now = 0;
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

