// Controller.h

#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ControllerClass
{
 protected:
	HardwareSerial * serial;

	const byte errorCountThreshold = 10;
	byte errorCount;
	bool error;

	typedef union {
		byte packet;
		struct {
			byte leftForward : 1;
			byte leftBack : 1;
			byte rightForward : 1;
			byte rightBack : 1;
			byte up : 1;
			byte down : 1;
			byte open : 1;
			byte close : 1;
		}btn;
		struct {
			byte d2 : 1;
			byte d3 : 1;
			byte d4 : 1;
			byte d5 : 1;
			byte d6 : 1;
			byte d7 : 1;
			byte d8 : 1;
			byte d9 : 1;
		}sw;
		void clear()
		{
			packet = 0;
		}
	}ControllerUnion;

	ControllerUnion con, conOld;

	void clearError();

 public:
	 void init(HardwareSerial& hs);
	 bool receiveConData();
	 void sendConData();

	 bool leftForward()		{ return con.btn.leftForward; }
	 bool leftBack()		{ return con.btn.leftBack; }
	 bool rightForward()	{ return con.btn.rightForward; }
	 bool rightBack()		{ return con.btn.rightBack; }
	 bool up()		{ return con.btn.up; }
	 bool down()	{ return con.btn.down; }
	 bool open()	{ return con.btn.open; }
	 bool close()	{ return con.btn.close; }
	 
	 void d2(int d) { con.sw.d2 = d; }
	 void d3(int d) { con.sw.d3 = d; }
	 void d4(int d) { con.sw.d4 = d; }
	 void d5(int d) { con.sw.d5 = d; }
	 void d6(int d) { con.sw.d6 = d; }
	 void d7(int d) { con.sw.d7 = d; }
	 void d8(int d) { con.sw.d8 = d; }
	 void d9(int d) { con.sw.d9 = d; }

};

extern ControllerClass Controller;

#endif

