// 
// 
// 

#include "Controller.h"

void ControllerClass::clearError()
{
	error = false;
	errorCount = 0;
}

void ControllerClass::init(HardwareSerial& hs)
{
	serial = &hs;
	serial->setTimeout(0);

	con.packet = conOld.packet = 0;

	error = 1;
	errorCount = 255;
}

bool ControllerClass::receiveConData()
{
	int readData;
	bool dataReceived = false;

	conOld.packet = con.packet;
	while ((readData = serial->read()) != -1)
	{
		con.packet = readData;
		dataReceived = true;
	}

	if (dataReceived)
	{
		clearError();
	}
	else
	{
		if (errorCount + 1 > errorCountThreshold)
		{
			error = true;
			con.clear();
			conOld.clear();
		}
		else
		{
			errorCount++;
		}
	}
	return error;
}

void ControllerClass::sendConData()
{
	serial->write(con.packet);
}


ControllerClass Controller;

