#include "Data.h"
#include "MikeTWSData.h"

#include <iostream>
#include <string>
#include <vector>

//forward function declarations:
long StringToLong(std::string Input);

Data::Data(Control * p, int starting_bid)	//THIS IS THE NEW REFACTORED CONSTRUCTOR - FINISH THIS
{
	//MikeSimulator * ptr_to_mikesimulator = p;
//	Order = new MikeOrder(p);
	ask_price = starting_bid + 1;
	bid_price = starting_bid;
	prev_ask_price = ask_price;
	prev_bid_price = bid_price;
	ask_volume = 10;
	bid_volume = 10;
	top_limit = 0;
	bottom_limit = 0;
	prof_top_limit = 0;
	prof_bot_limit = 0;
	simple_time = 1;

	liveTWSData = NULL;
	liveTWSData = new MikeTWSData();
	using namespace std;
	//liveDataAvailable = liveTWSData->ConnectTWS(1);
	liveDataAvailable = 0;
	if (liveDataAvailable) {
		cout << "\nLive Data Available" << endl;
		cout << setprecision(15);
		cout << "Current EUR.USD bid size: " << liveTWSData->GetBidSize(1) << endl;
		cout << "Current EUR.USD bid price: " << liveTWSData->GetBid(1) << endl;
	}
	else {
		cout << "\nLive Data not available! " << endl;
		delete liveTWSData;
		liveTWSData = NULL;
	}
}


void Data::ConnectLiveData()
{
	if (liveDataAvailable) { std::cout << "\nAlready connected!" << std::endl; return; }
	liveTWSData = NULL;
	liveTWSData = new MikeTWSData();
	using namespace std;
	liveDataAvailable = liveTWSData->ConnectTWS(3);
	if (liveDataAvailable) {
		cout << "\nLive Data Available" << endl;
		cout << setprecision(15);
		cout << "Current EUR.USD bid size: " << liveTWSData->GetBidSize(1) << endl;
		cout << "Current EUR.USD bid price: " << liveTWSData->GetBid(1) << endl;
	}
	else {
		cout << "\nLive Data not available! " << endl;
		delete liveTWSData;
		liveTWSData = NULL;
	}
}

void Data::updateLiveData(int TickerId)
{
	using namespace std;
	if (!liveDataAvailable) { cout << "\nLive Data not available." << endl; return; }
	//liveTWSData provides prices as a double in US dollars. we need to convert that to int so that they are displayed as US Cents:
	int convertfactor = 0;
	if (TickerId == 1 || TickerId == 2) convertfactor = 100000; //for forex: EUR and GBP
	if (TickerId == 3 || TickerId == 4 || TickerId == 5 || TickerId == 6) convertfactor = 100;//for stocks
	bid_price = (liveTWSData->GetBid(TickerId)) * convertfactor;
	ask_price = (liveTWSData->GetAsk(TickerId))*convertfactor;
	bid_volume = liveTWSData->GetBidSize(TickerId);
	ask_volume = liveTWSData->GetAskSize(TickerId);
}

void Data::PrintoutDataInConsole()
{
	using namespace std;
	if (!liveDataAvailable) { cout << "\nLive Data not available." << endl; return; }


	cout << setprecision(15);
	cout << "\nServer time: " << liveTWSData->GetServerTime() << "Printing Live Data for EUR.USD:\n Bid Price: " << liveTWSData->GetBid(1) <<
		" bid size: " << liveTWSData->GetBidSize(1) <<
		" ask price: " << liveTWSData->GetAsk(1) <<
		" ask size: " << liveTWSData->GetAskSize(1) << endl;
}




//helper functions below:

//returns a long from a string:
long StringToLong(std::string Input)	//accepts a string of any of these formats: 1.000522346874 ; 12566478 ; 00023668 ; 000263574.5489 ; 456.67;
{
	const char * c = Input.c_str();

	long returnValue;

	// THE SECRET IS HERE:
	// atof - all to float?
	// atoi - also works - all to int?

	returnValue = atol(c);
	
	return returnValue;

	//int myVal = atoi("66");
	//float myValDbl =	atof("66.55");		//windows compiler directly supports this????
}
