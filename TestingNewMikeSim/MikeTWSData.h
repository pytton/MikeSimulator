#ifndef _MIKETWSDATA_H_INCLUDED_
#define _MIKETWSDATA_H_INCLUDED_


#include <string>
#include <conio.h>
#include <iostream>
#include <iomanip> //for setprecision
#include <fstream>	//for ofstream out("order.out");
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include <Windows.h>

#include "TwsApiL0.h"
#include "TwsApiDefs.h"



class ResponseFromTWS;

class MikeTWSData//1-EUR, 2-GBP, 3-SPY, 4-DIA, 5-IWM, 6-QQQ
{
public:
	MikeTWSData();//1-EUR, 2-GBP, 3-SPY, 4-DIA, 5-IWM, 6-QQQ
	~MikeTWSData();

	bool ConnectTWS(int numberAttempts);
	void consolePrintProt();
	

	double GetBid(int TickerID);
	double GetAsk(int TickerID);
	double GetBidSize(int TickerID);
	double GetAskSize(int TickerID);
	long GetServerTime();

private:
	ResponseFromTWS * twsReply;
	EClientL0*	pClientTWS;
	bool ConnectedToTWS;

	void setupContracts();//1-EUR, 2-GBP, 3-SPY, 4-DIA, 5-IWM, 6-QQQ
	void GetContractDetails(Contract & myContract, int contract); //1-EUR, 2-GBP, 3-SPY, 4-DIA, 5-IWM, 6-QQQ

	//////////////////////////////
	//PROTOTYPE:

	std::string UTCTime()
	{
		char outstr[200];
		time_t t;
		struct tm *tmp;
		const char* fmt = "%a %d %b %y %T %z";
		std::string UTCTime;
		t = time(NULL);
		tmp = gmtime(&t);
		if (tmp == NULL) {
			UTCTime = "gmtime error";
		}

		if (strftime(outstr, sizeof(outstr), fmt, tmp) == 0) {
			UTCTime = "strftime returned 0";
		}
		else strftime(outstr, sizeof(outstr), fmt, tmp);

		UTCTime = static_cast<std::string>(outstr);

		return UTCTime;
	}

	int generateID()
	{
		static int s_itemID = 0;
		return s_itemID++;
	}

	void waitforuserend()
	{
		using namespace std;
		cin.clear();
		cin.ignore(255, '\n');
		cin.get();
	}

	//END PROTOTYPE
	///////////////////////////////////



};

class ResponseFromTWS : public EWrapperL0		//this implementation will only support up to 100 tickerId's - limited by array size
{
public:

	double m_priceAsk[100];
	double m_priceBid[100];
	double m_BidSize[100];
	double m_AskSize[100];

	long m_time;


	virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute)
	{
		switch (field)
		{
		case TickType::ASK:
			m_priceAsk[tickerId] = price;
			break;
		case TickType::BID:
			m_priceBid[tickerId] = price;
			break;
		}
	}

	virtual void tickSize(TickerId tickerId, TickType field, int size)
	{
		switch (field)
		{
		case TickType::BID_SIZE:
			m_BidSize[tickerId] = double(size);
			break;
		case TickType::ASK_SIZE:
			m_AskSize[tickerId] = double(size);
			break;
		}
	}

	virtual void currentTime(long time) { m_time = time; }
};



#endif // _MIKETWSDATA_H_INCLUDED_