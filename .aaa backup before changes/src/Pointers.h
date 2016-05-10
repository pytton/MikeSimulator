//includes Data, Control and Display
//
//#ifndef _POINTERS_H_INCLUDED_
//#define _POINTERS_H_INCLUDED_
////this class stores pointers to all elements of the application - for easy access
//
//#include "UserInterface.h"
//#include "MktSnapshot.h"	//for Price and MktSnapshot
//
//
//class Data;
//class Control;
//class Display;
////class Pointers;
//
//class Pointers	//this is used for communication between three main elements of the program
//{
//public:
//	Control * ptr_t_control;
//	Data * ptr_t_data;
//	Display * ptr_t_display;
//	
//	//consturctors:
//	Pointers();
//	Pointers(Control * c, Data * d, Display * dis);
//
//	void initPointers(Control * control, Data * data, Display * display);	//sets pointers
//
//	Control * returnControlPtr();
//};
//
//
//
//
//
//
//#endif // !_POINTERS_H_INCLUDED_



////below, just for reference - a way to handle pointers the safe? or stupid? way:
//
//class Display	//stores all user input/output activities
//{
//public:
//	UserInterface * window;
//	Display * ptr_t_display;	//pointer to self - used for access
//
//								//constructor
//	Display()
//	{
//		window = new UserInterface;
//		window->show();
//	}
//	void set_display_ptr()	//THIS MUST BE CALLED RIGHT AFTER CONSTRUCTING CLASS!!!!
//	{
//		ptr_t_display = this;
//	}
//	Display * get_display_ptr()
//	{
//		return this;
//	}
//};
//
//class Data	//stores all data used by program
//{	//put all marketdata here
//public:
//	Data * ptr_t_data;
//
//	Data()	//constructor
//	{
//
//	}
//	void set_data_ptr()	//THIS MUST BE CALLED RIGHT AFTER CONSTRUCTING CLASS!!!!
//	{
//		ptr_t_data = this;
//	}
//	Data * get_data_ptr()
//	{
//		return this;
//	}
//
//};
//
//class Control
//{
//public:
//
//
//};
//
//class Pointers
//{
//public:
//	Display * ptr_t_display;
//	Data * ptr_t_data;
//	Control * ptr_t_control;
//
//
//	//below is old code:
//	//void * ptr_t_UserInterface;	//main window of userinterface
//	//void set_ptr_t_UserInterface(void * pointer)
//	//{
//	//	ptr_t_UserInterface = pointer;
//	//}
//	//void * get_ptr_t_UserInterface()
//	//{
//	//	return ptr_t_UserInterface;
//	//}
//};