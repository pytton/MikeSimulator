#include "Data.h"


namespace Mike {
	Data::Data()
	{
		//set up the user interface windows:
		dataControlWindow = new DataUI();
	//	dataControlWindow->mWindow->show();
	}

	Data::~Data()
	{
		if (NULL == dataControlWindow) delete dataControlWindow;
	}


	DataUI::DataUI()
	{
		mWindow->show();
	}

}//namespace Mike