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

void ControllerClass::debug()
{
	if (con.btn.leftForward)	serial->print("LeftForward ");
	if (con.btn.leftBack)	serial->print("LeftBack ");
	if (con.btn.rightForward)	serial->print("RightForward ");
	if (con.btn.rightBack)	serial->print("RightBack ");
	if (con.btn.up)	serial->print("Up ");
	if (con.btn.down)	serial->print("Down ");
	if (con.btn.open)	serial->print("Open ");
	if (con.btn.close)	serial->print("Close ");
	serial->println("");
}


ControllerClass Controller;

