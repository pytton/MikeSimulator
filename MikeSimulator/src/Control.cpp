#include "Control.h"



namespace Mike
{
	Control::Control()
	{
		priceControl = new FluidPriceControlUI();

		priceControl->m_window1->show();
	}


	Control::~Control()
	{
	}

}