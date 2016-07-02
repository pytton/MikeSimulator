#pragma once
#include "UserInterface.h"

/**************************************************************************************************************
THIS IS AN EXAMPLE OF DERIVING A NEW INTERFACE FROM USERINTERFACE

TO BE USED AS A MEANS TO CONTROL ALGOS IN THE FUTURE





**************************************************************************************************************/

class ManualInterface :   public UserInterface
{
public:
	ManualInterface(Control * control, double starting_bid_price = 700);
	
	~ManualInterface();
	
	//uncomment and implement this if it is needed to change column and button names
//	virtual void SetColButNames(std::vector <std::string> &col_names, std::vector <std::string> &button_names);
};


