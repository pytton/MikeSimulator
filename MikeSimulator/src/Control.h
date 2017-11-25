#pragma once

#include "..\FLUID\FluidPriceControl.h"

namespace Mike
{
	class Control
	{
	public:
		Control();
		~Control();

		FluidPriceControlUI * priceControl;
	};
}

