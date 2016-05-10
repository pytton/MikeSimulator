#ifndef _CONTROL_H_INCLUDED_
#define _CONTROL_H_INCLUDED_

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
#include "UserInterface.h"
//#include "MktSnapshot.h"	//for Price and MktSnapshot



class Data;
class Control;
class MikeSimulator;

class Control
{
public:
	//constructor:
	Control(MikeSimulator*p);

	//member functions:
	void MainLoop();
	void ManualOrder(int type, long price);
	void CallbkWidTable();
//	void tryout1();
	void printCurrentAll();
private:
		//members:
	MikeSimulator * ptr_to_mikesimulator;
	UserInterface * userInterface;
	Data * data;

};

#endif //_CONTROL_H_INCLUDED_
