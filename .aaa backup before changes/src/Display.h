#ifndef _DISPLAY_H_INCLUDED_
#define _DISPLAY_H_INCLUDED_

//#include "Pointers.h"
#include "UserInterface.h"


class Data;
class Control;
//class Pointers;
class MikeSimulator;
//Pointers Display::StaticPointers = 0;



class Display	//stores all user input/output activities
{

public:
//constructor
	Display(MikeSimulator*p);

	UserInterface * GetUInterface();
	//{
	//	return window;
	//}
public:
//private: 
	
	MikeSimulator * ptr_to_mikesimulator;
	UserInterface * window;

//member functions



};







#endif //_DISPLAY_H_INCLUDED_
