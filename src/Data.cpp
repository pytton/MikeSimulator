#include "Data.h"
//#include "MktSnapshot.h"	//for Price and MktSnapshot
//#include "MikeOrder.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "MktSnapshot.h"	//for Price and MktSnapshot
#include "MikeSimulator.h"
#include "UserInterface.h"
#include "MikeTWSData.h"

//forward function declarations:
long StringToLong(std::string Input);

//Data::Data(MikeSimulator * p)
//{
//	MikeSimulator * ptr_to_mikesimulator = p;
////	Order = new MikeOrder(p);
//	ask_price = 701;
//	bid_price = 700;
//	prev_ask_price = 701;
//	prev_bid_price = 700;
//	ask_volume = 10;
//	bid_volume = 10;
//	top_limit = 0;
//	bottom_limit = 0;
//	prof_top_limit = 0;
//	prof_bot_limit = 0;
//	simple_time = 1;
//}


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

//
////below function loads prices stored in a file to memory
//void Data::MktSnapshot(/*std::vector<MktSnap> & data*/) //this function loads prices stored in a file to memory
//{
//	/*
//	getline(where to store the extracted characters, how many characters should be taken unlles, seperator(delimiter)) - extracts seperators and delete it
//	get(where to store the extracted characters, how many characters should be taken unlles, seperator(delimiter)) - doesn't extract seperator
//	ignore(how_many_characters_to_extracte AND TO IGNORE THEM, seperator) - extracts characters
//
//	get();
//	*/
//
//	using namespace std;
//
//	Price tempPrice;	//for feeding into tempSnap
//	MktSnap tempSnap;	//temporary object for feeding the ptr_to_vector vector
//	long progressCtr = 0;	//used for displaying how much of file has been processed
//
//
//	//this is where we store the data - histSavedData is part of Data class
//	vector<MktSnap> * ptr_to_vector = &histSavedData;
//
//	//file name from which to input data:
//	fstream file;
//	file.open("sample2.txt", ios::in | ios::binary);
//
//	if (file.is_open())	//load contents of file into vector<MktSnap> * ptr_to_vector = &histSavedData
//	{
//		//std::string scrnoutput;
//		char buf;
//		char temp;
//		string output = "";
//		int counter = 0;	//for the case/switch part
//
//		do {
//			temp = file.get();
//			if ((temp != ',') && (temp != '\n'))
//			{
//				buf = temp;
//				output += buf;	//adds the character buf to string output
//			}
//			if ((temp == ','))
//			{
//				//here - take the output. figure out where to put it
//				//first three outputs - they go into time. rest as market data
//				//output - this now has the string I want to put somewhere
//				//increase the counter, put output according to counter, then clear output
//				//tempSnap is a tempo
//				switch (counter)
//				{
//
//				case 0:		//first long string time
//					tempSnap.m_str_dtLong = output;
//					break;
//				case 1:		//second integer time
//					tempSnap.m_str_dtnumber = output;
//					break;
//				case 2:		//milisecond time as string
//					tempSnap.m_str_timems = output;
//					break;
//				case 3:		//EUR into m_str_name
//					break;	//this holds only the name of instrument!!
//				case 4:
//					tempSnap.m_prices[0].m_str_bidPr = output;
//					break;
//				case 5:
//					tempSnap.m_prices[0].m_str_askPr = output;
//					break;
//				case 6:
//					tempSnap.m_prices[0].m_str_bidVol = output;
//					break;
//				case 7:
//					tempSnap.m_prices[0].m_str_askVol = output;
//					tempSnap.m_prices[0].m_flag_is_realdata = 1;
//					break;
//				case 8:		//GBP into m_str_name
//					break;
//				case 9:
//					tempSnap.m_prices[1].m_str_bidPr = output;
//					break;
//				case 10:
//					tempSnap.m_prices[1].m_str_askPr = output;
//					break;
//				case 11:
//					tempSnap.m_prices[1].m_str_bidVol = output;
//					break;
//				case 12:
//					tempSnap.m_prices[1].m_str_askVol = output;
//					tempSnap.m_prices[1].m_flag_is_realdata = 1;
//					break;
//				case 13:	//SPY into m_str_name
//					break;
//				case 14:
//					tempSnap.m_prices[2].m_str_bidPr = output;
//					break;
//				case 15:
//					tempSnap.m_prices[2].m_str_askPr = output;
//					break;
//				case 16:
//					tempSnap.m_prices[2].m_str_bidVol = output;
//					break;
//				case 17:
//					tempSnap.m_prices[2].m_str_askVol = output;
//					tempSnap.m_prices[2].m_flag_is_realdata = 1;
//					break;
//				case 18:		//DIA into m_str_name
//					break;
//				case 19:
//					tempSnap.m_prices[3].m_str_bidPr = output;
//					break;
//				case 20:
//					tempSnap.m_prices[3].m_str_askPr = output;
//					break;
//				case 21:
//					tempSnap.m_prices[3].m_str_bidVol = output;
//					break;
//				case 22:
//					tempSnap.m_prices[3].m_str_askVol = output;
//					tempSnap.m_prices[3].m_flag_is_realdata = 1;
//					break;
//				case 23:		//IWM into m_str_name
//					break;
//				case 24:
//					tempSnap.m_prices[4].m_str_bidPr = output;
//					break;
//				case 25:
//					tempSnap.m_prices[4].m_str_askPr = output;
//					break;
//				case 26:
//					tempSnap.m_prices[4].m_str_bidVol = output;
//					break;
//				case 27:
//					tempSnap.m_prices[4].m_str_askVol = output;
//					tempSnap.m_prices[4].m_flag_is_realdata = 1;
//					break;
//				case 28:		//QQQ into m_str_name
//					break;
//				case 29:
//					tempSnap.m_prices[5].m_str_bidPr = output;
//					break;
//				case 30:
//					tempSnap.m_prices[5].m_str_askPr = output;
//					break;
//				case 31:
//					tempSnap.m_prices[5].m_str_bidVol = output;
//					break;
//				case 32:
//					tempSnap.m_prices[5].m_str_askVol = output;
//					tempSnap.m_prices[5].m_flag_is_realdata = 1;
//					break;
//				default:
//					cerr << "error reading file (at comma switch)";
//					break;
//				}
//
//				counter++;
//				output = "";
//				//temp = 0;
//			}
//			if (temp == '\n') {
//				//here - this is the end of line. put everything into the vector
//				//vecMktSnap.push_back(tempSnap);
//				ptr_to_vector->push_back(tempSnap);
//				counter = 0;
//			}
//
//			progressCtr++;	//for displaying progress of loading into memory
//			if (progressCtr % 250000 == 0) { std::cout << endl << progressCtr << endl; }
//		} while (!file.eof());	//stay in loop until end of file is reached
//		cout << endl << endl << endl << endl << "output string follows: " << endl;
//	}
//	else
//	{
//		cout << "The file couldn't be opened properly" << endl;
//	}
//
//	cout << endl << endl << "Contents: " << tempSnap.m_prices[0].m_str_bidVol << endl << tempSnap.m_str_dtLong << endl << tempSnap.m_str_timems;
//
//	//print first ten timestamps for check:
//	//for (int i = 0; i < ((vecMktSnap.size() < 3) ? vecMktSnap.size() : 3); i++)
//	//{
//	//	tempSnap = vecMktSnap[i];
//	//	if (i == 0) { cout << endl << "First: " << tempSnap.m_str_timems << endl; }
//	//	std::cout << endl << tempSnap.m_str_timems << endl;
//	//}
//	////print last timestamp for check:
//	//tempSnap = vecMktSnap[vecMktSnap.size() - 1];
//	//std::cout << endl << "Last: " << tempSnap.m_str_timems;
//	//cout << endl << tempSnap.m_prices[2].m_str_askPr << endl;
//	//cout << endl << tempSnap.m_prices[0].m_str_askPr << endl;
//
//
//	//printout part of data for a check:
//	for (int i = 0; i < (((ptr_to_vector->size()) < 3) ? (ptr_to_vector->size()) : 3); i++)
//	{
//		tempSnap = (*ptr_to_vector)[i];
//		if (i == 0) { cout << endl << "First: " << tempSnap.m_str_timems << endl; }
//		std::cout << endl << tempSnap.m_str_timems << endl;
//	}
//	tempSnap = (*ptr_to_vector)[(*ptr_to_vector).size() - 1];
//	cout << endl << " vector output: " << endl;
//	std::cout << endl << "Last: " << tempSnap.m_str_timems;
//	cout << endl << tempSnap.m_prices[2].m_str_askPr << endl;
//	cout << endl << tempSnap.m_prices[0].m_str_askPr << endl;
//
//
//	//function that builds price data in long format from string format
//	for (int i = 0; i < histSavedData.size(); ++i)
//	{
//		for (int j = 0; j < 6; ++j) {
//			//copy and convert prices from string to long format:
//			histSavedData[i].m_prices[j].m_long_askPr = 
//				StringToLong(histSavedData[i].m_prices[j].m_str_askPr);
//			histSavedData[i].m_prices[j].m_long_askVol =
//				StringToLong(histSavedData[i].m_prices[j].m_str_askVol);
//			histSavedData[i].m_prices[j].m_long_bidPr =
//				StringToLong(histSavedData[i].m_prices[j].m_str_bidPr);
//			histSavedData[i].m_prices[j].m_long_bidVol =
//				StringToLong(histSavedData[i].m_prices[j].m_str_bidVol);
//			
//			//set the flag to indicate data is present:			
//			histSavedData[i].m_prices[j].m_flag_is_realdata = true;
//		}
//	}
//}
//
//




void Data::LiveData() 
{
	//TODO - MAKE A FUNCTION THAT GETS LIVE DATA FROM THE MARKET HERE
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
	//HACK://liveTWSData provides prices as a double in US dollars. we need to convert that to int so that they are displayed as US Cents:
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
	////////////////////
	////////////////////
	////////////////////
	//						THE SECRET IS HERE:
	// atof - all to float?
	// atoi - also works - all to int?

	returnValue = atol(c);
	
	return returnValue;

	//int myVal = atoi("66");
	//float myValDbl =	atof("66.55");		//windows compiler directly supports this????
}
