#ifndef _DATA_H_INCLUDED_
#define _DATA_H_INCLUDED_

#include "MktSnapshot.h"	//for Price and MktSnapshot
//#include "Pointers.h"
#include "Display.h"
#include "MikeOrder.h"


class Control;
class MikeOrder;

class Data	//stores all data used by program
{

public:
	//constructors:
	Data(MikeSimulator * p);
	MikeSimulator * ptr_to_mikesimulator;	//pointer to class creating this class
	//member functions:
	void MktSnapshot();	//loads historical data into memory (from Sample2.txt)
	void Data::LiveData();	//empty now - TODO	
	

//GETTERS / SETTERS:
	inline long GetAskPrice() { return ask_price; }
	inline long GetBidPrice() { return bid_price; }
	inline long GetPrevAskPrice() { return prev_ask_price; }
	inline long GetPrevBidPrice() { return prev_bid_price; }

	inline void SetAskPrice(long value) { ask_price = value; }
	inline void SetBidPrice(long value) { bid_price = value; }
	inline void SetPrevAskPrice(long value) { prev_ask_price = value; }
	inline void SetPrevBidPrice(long value) { prev_bid_price = value; }

	inline MikeOrder * GetMikeOrder() { return Order; }
	inline void SetMikeOrder(MikeOrder * NewOrder) { Order = NewOrder; }
	//put all marketdata here
	std::vector<MktSnap>  histSavedData;	//holds historical data saved in a file called "Sample2.txt"

private:
	long ask_price;
	long bid_price;
	long prev_ask_price;
	long prev_bid_price;
	long ask_volume;
	long bid_volume;
	long top_limit;
	long bottom_limit;
	long prof_top_limit;
	long prof_bot_limit;
	long simple_time;

	MikeOrder * Order;
};

class MikePosition
{
public:
	long price;
	long open_amount;
	long open_pl;
	long closed_pl;
	long total_pl;
};





#endif //_DATA_H_INCLUDED_




//long & BidPrice()
//{
//	return bid_price;
//}

////long currPrice = BidPrice();

////BidPrice() = 95;