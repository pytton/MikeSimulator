#pragma once
#include "UserInterface.h"

/**************************************************************************************************************
THIS IS AN EXAMPLE OF DERIVING A NEW INTERFACE FROM USERINTERFACE

TO BE USED AS A MEANS TO CONTROL ALGOS IN THE FUTURE





**************************************************************************************************************/

class ManualInterface :   public UserInterface
{
public:
//	ManualInterface(Control * control, double starting_bid_price = 700);
	ManualInterface(
		Control * control,
		double starting_bid_price = 700,
		int numberOfColumns = 25,
		int numberOfButtoncolumns = 5);
	
	~ManualInterface();
	
	//uncomment and implement this if it is needed to change column and button names
	virtual void SetColButNames(std::vector <std::string> &col_names, std::vector <std::string> &button_names);

	//experimenting:

	//virtual void printPositions(const std::vector <MikePosition> *openPositions,
	//	const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice);
	//virtual void PrintAll(
	//	long totalOpenPos,
	//	long totalOpenPL,
	//	long totalClosedPL,
	//	long totalPL,
	//	long askPrice,
	//	long bidPrice,
	//	const std::vector <MikePosition> *openPositions,
	//	const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice);


};


