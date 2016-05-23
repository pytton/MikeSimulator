//#ifndef _MKTSNAPSHOT_H_INCLUDED_
//#define _MKTSNAPSHOT_H_INCLUDED_
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//
//class Price
//{
//public:
////time:
//	std::string m_str_dtLong;	//date/time in long format - eg Tue 24 Nov 15 15:52:37 -0700
//	std::string m_str_dtnumber;	//date/time as an int eg 1448380352
//	std::string m_str_timems;	//time in h m and milisecond eg 7h45m9962
////prices as string:
//	std::string m_str_name;		//name of instrument eg SPY
//	std::string m_str_bidPr;	//bid price as string
//	std::string m_str_askPr;	//ask price as string
//	std::string m_str_bidVol;	//bid volume as string
//	std::string m_str_askVol;	//ask volume as string
////prices as long:
//	long  m_long_bidPr;	//bid price as long
//	long m_long_askPr;	//ask price as long
//	long m_long_bidVol;	//bid volume as long
//	long m_long_askVol;	//ask volume as long
//
//	bool m_flag_is_realdata;	
//	//flag - if false this class has been initialized but not filled with real market data
//	//for use when Price class will be used as part of MktSnap or other class - as part of a bigger array
//	//set this to true after filling in with real data as opposed to dummy data represented by -1 in constructor
//	
//	//constructor:
//	Price()
//	{
//		m_str_name = "";	//name of instrument eg SPY
//		m_str_bidPr = "";	//bid price as string
//		m_str_askPr = "";	//ask price as string
//		m_str_bidVol = "";	//bid volume as string
//		m_str_askVol = "";	//ask volume as string
//
//		m_long_bidPr = -1;	//bid price as long
//		m_long_askPr = -1;	//ask price as long
//		m_long_bidVol = -1;	//bid volume as long
//		m_long_askVol = -1;	//ask volume as long
//
//		m_flag_is_realdata = 0;
//	}
//
//	//member functions:
//	void changeStringToLongs()
//	{
//		//TO DO - write a function that attempts to convert string data to long data using atol function (similar to atoi)
//	}
//};
//
//class MktSnap	//Snapshot of Mkt at given timepoint. Put these in a vector to have a stream of market data.
//{
//public:
//	std::string m_str_dtLong;	//date/time in long format - eg Tue 24 Nov 15 15:52:37 -0700
//	std::string m_str_dtnumber;	//date/time as an int eg 1448380352
//	std::string m_str_timems;	//time in h m and milisecond eg 7h45m9962
//
//	//Price m_prices[6];	-- this was the original way of doing it. replaced with vector below:
//	std::vector <Price> m_prices;	//array to hold Prices - modify to make bigger if ever needed
//									//use: EUR - 0, GBP - 1, SPY - 2, DIA - 3, IWM - 4, QQQ - 5
//	MktSnap() {
//		m_prices.resize(6);			//increase this if adding anything else - but will need to change
//									//void Data::MktSnapshot to put values inside it too
//	}
//	
//};
//
//class StreamOfMktSnap
//{
//public:
//	std::vector<MktSnap> *MktStream;
//
//	//constructor:
//	StreamOfMktSnap()
//	{
//		MktStream = new std::vector<MktSnap>;
//	}
//};
//
//
//#endif //_MKTSNAPSHOT_H_INCLUDED_