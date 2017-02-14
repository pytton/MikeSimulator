#ifndef _DATA_H_INCLUDED_
#define _DATA_H_INCLUDED_





class Control;
class MikeOrder;
class Data;
class MikeSimulator;
class MikeTWSData;



class Data	//stores Market data used by program
{

public:
	//constructors:
	//Data(MikeSimulator * p);
	Data(Control * p, int starting_bid);

	MikeSimulator * ptr_to_mikesimulator;	//pointer to class creating this class
	//member functions:
//	void MktSnapshot();	//loads historical data into memory (from Sample2.txt)
	void Data::LiveData();	//empty now - TODO	
	void ConnectLiveData();
	void updateLiveData(int TickerId);//this asks liveTWSData for current data for TickerId and updates current bid_price ask_price bid_volume ask_volume values.
	void PrintoutDataInConsole();
	

//GETTERS / SETTERS:
	inline long GetAskPrice() { return ask_price; }
	inline long GetBidPrice() { return bid_price; }
	inline long GetPrevAskPrice() { return prev_ask_price; }
	inline long GetPrevBidPrice() { return prev_bid_price; }

	inline void SetAskPrice(long value) { ask_price = value; }
	inline void SetBidPrice(long value) { bid_price = value; }
	inline void SetPrevAskPrice(long value) { prev_ask_price = value; }
	inline void SetPrevBidPrice(long value) { prev_bid_price = value; }

//	inline MikeOrder * GetMikeOrder() { return Order; }
//	inline void SetMikeOrder(MikeOrder * NewOrder) { Order = NewOrder; }
	//put all marketdata here
//	std::vector<MktSnap>  histSavedData;	//holds historical data saved in a file called "Sample2.txt"

private:
	MikeTWSData * liveTWSData;
	bool liveDataAvailable;
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

	//MikeOrder * Order;
};







#endif //_DATA_H_INCLUDED_




//long & BidPrice()
//{
//	return bid_price;
//}

////long currPrice = BidPrice();

////BidPrice() = 95;