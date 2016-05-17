#include "Display.h"

Display::Display(MikeSimulator * p)
{
	ptr_to_mikesimulator = p;
//	window = new UserInterface(ptr_to_mikesimulator, this);
	//window->ptr_t_display = this;
	window->show();
}

UserInterface * Display::GetUInterface()
{
	return window;
}