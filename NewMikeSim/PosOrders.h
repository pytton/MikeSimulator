#ifndef _POSORDERS_H_INCLUDED_
#define _POSORDERS_H_INCLUDED_

/****************************************************************************************
This class handles all the positions and orders for a single strategy/algo.
It can be a 'manual' algo - meaning that all orders are entered by a human.
Or it can handle positions and fills/orders for any algo I come up with.
Algos might have their own different objects to handle decisions.
This class handles the basics - order entry, modification, cancellation, fills,
requests for open positions, P/L.

This class constits of these main elements:
mPositions;			//stores all open positions
mOpenOrders;		//stores all open orders
mClosedOrders;		//stores all closed orders
mOpenOrdersAtPrice;	//stores all open orders at a given price point

mPositions is a map - each price point has own MikePosition class with its open amount
(positive for 'long' and negative for 'short'), open/closed/total profit-loss.

The sum of these individual positions for each price point make up these values:
long mAllOpenPL;  //total open Profit/Loss for all elements in all individual mPositions
long mAllClosedPL;  //total closed P/L for all elements in mPositions
long mNetPosition;  //sum of all positions: positive for long, negative for short
double mAveragePriceOfPosition;  //weighed avg. price of net position


For example - human presses 'buy lmt' button with a price corresponding to 547:
void newOrder(price, orderType) enteres the order into mOpenOrders.
when void checkFills(bidPrice, askPrice) is called - all the elements of mOpenOrders
are checked for fills. If an order is filled it is moved to mClosedOrders
and  mPositions is updated as required.

This class is used and controlled by the Control class.
The Control class might have as many of MikePosition classes as it needs - one for
each algo.

Methods:

void calculatePL(bidPrice, askPrice)) is used to update the Profit/Loss of each
position in MikePositionBook

****************************************************************************************/


//#include "MikePositionsOrders.h"

#include <vector>
#include <string>
#include <map>
#include <set>

class Timer;
class PositionBook;
class MikeOrderbook;
class MikePosition;
class MikeOrdersAtPrice;

enum BtnPressed;
enum MikeOrderType;


#ifndef _MIKEORDERCLASS_DEFINED_
#define _MIKEORDERCLASS_DEFINED_

class MikeOrder
{
public:
	//	MikeOrder();
	//	~MikeOrder();

	//BUYLMT, SELLLMT, BUYSTP, SELLSTP
	MikeOrderType ordertype;

	//this stores which position the order is assigned to
	//there can be multiple orders for one price
	//once order is filled - this tells which position is updated
	long assignedToPosition = 0;

	//the price of the order. prices are in cents.
	long price = 0;

	//the size of the order
	long amount = 0;

	//for future use - for passing orders into outside API
	int orderId;

	//for checking fills - has the order been filled already?
	bool isFilled = false;

	//for future implementation.
	bool partialFill = false;
};

class MikeOrdersAtPrice
{
public:
	long price = 0;
	long buyLimitAmount = 0;
	long buyStopAmount = 0;
	long sellLimitAmount = 0;
	long sellStopAmount = 0;

	void eraseall();//

					//returns true if all orders are empty at this price
	bool checkifempty();

};

class MikePosition
{
	friend class WidgetTable;
public:
	long price = 0;
	long open_amount = 0;//positive open_amount means the position is 'long'. negative open_amount means the position is 'short'.
	long open_pl = 0;
	long closed_pl = 0;
	long total_pl = 0;

private:
	bool isActive = false;
	long prevbidprice = 0;
	long prevaskprice = 0;

public:
	//this is for indexing purposes - set to TRUE if position was ever
	//accessed or changed. Mainly to avoid iterating through tens of thousands
	//of positions
	inline bool checkifActive() { if (isActive == true) return true; else  return false; }
	inline void setActive() { isActive = true; }
	inline void setInactive() { isActive = false; }

public:
	//positive amount for buy orders, negative amount for sell orders!
	void fill(long fillprice, long filledamount)
	{
		//this will modify the closed_pl by:
		//difference in fill price and price of this position
		//multiplied by amount
		long tempclosed_pl = closed_pl;
		long profitloss;
		////////////////////////////////////////////////
		profitloss = (price - fillprice) * filledamount;
		closed_pl = tempclosed_pl + profitloss;
		////////////////////////////////////////////////
		//this updates the current open_amount by the amount that was filled
		long tempopenamount = open_amount;
		open_amount = tempopenamount + filledamount;
	}
	void calculatePL(long bidprice, long askprice)
	{
		//	static long prevbidprice = 0;
		//	static long prevaskprice = 0;
		if (bidprice != prevbidprice || askprice != prevaskprice)
		{
			open_pl = 0;
			//if position is 'long':
			if (open_amount >= 0) open_pl = (bidprice - price) * open_amount;
			//if position is 'short':
			if (open_amount < 0) open_pl = (askprice - price) * open_amount;

			//update total_pl with new open_pl
			total_pl = closed_pl + open_pl;
		}
	}
};//class MikePosition

#endif // !_MIKEORDERCLASS_DEFINED_

namespace Mike {


	//stores Positions and Orders
	class PosOrderss {

	public:
		typedef ::std::map<long, MikePosition> PositionMap;
		typedef ::std::set<MikeOrder> Orders;
		typedef ::std::map<long, MikeOrdersAtPrice> OrdsAtPrice;
	public:
		//main elements of this class:

		PositionMap mPositions;  //stores all open positions
		Orders mOpenOrders;  //stores all open orders
		Orders mClosedOrders;  //stores all closed orders
		OrdsAtPrice mOpenOrdersAtPrice;  //stores all open orders at a given price point
		long mAllOpenPL;  //total open Profit/Loss for all elements in all individual mPositions
		long mAllClosedPL;  //total closed P/L for all elements in mPositions
		long mAllTotalPL;  //mAllOpenPL + mAllClosedPL. Positive = profit, negative = loss
		long mNetPosition;  //sum of all positions: positive for long, negative for short
		double mAveragePriceOfPosition;  //weighed avg. price of net position
		double mZeroProfitPrice;  //price at which mAllTotalPL would equal zero

	protected:
		//PosOrd();
		//~PosOrd();

		//controlling orders and positions:

		//checkfills and update all values including P/Ls etc...
		void updateAll(long bidPrice, long askPrice);
		//enters a new order into the mOpenOrders container
		void newOrder(long price, MikeOrderType orderType);
		bool modifyOrder(int orderNumber, long price, MikeOrderType orderType);  //if orderNumber is in mOpenOrders, changes it to new price and orderType. Returns false if orderNumber not found in mOpenOrders
		void checkFills(long bidPrice, long askPrice);  //checks open orders for fills at given prices
		void cancelOrdersAtPrice(long price);  //cancels all orders at given price
		bool cancelOrder(int orderNumber);  //returns true if ordernumber found in mOpenOrders and cancels it. false if orderNumber not in mOpenOrders

//              _   _                
//    __ _  ___| |_| |_ ___ _ __ ___ 
//   / _` |/ _ \ __| __/ _ \ '__/ __|
//  | (_| |  __/ |_| ||  __/ |  \__ \
//   \__, |\___|\__|\__\___|_|  |___/
//   |___/                           
		//for printing/looking up orders and postions. call updateAll before using these if you want values for current bid/ask price:

		PositionMap const * getPositionsPtr() { return &mPositions; };  //for looking at open positions
		void updateOpenOrdersAtPrice();  //iterates through all mOpenOrders and updates mOpenOrdersAtPrice
		OrdsAtPrice const * getOrdsAtPricePtr() { return &mOpenOrdersAtPrice; }  //for looking at all orders at a price
		inline long getAllOpenPL() { return mAllOpenPL; }  //total open Profit/Loss for all elements in all individual mPositions
		inline long getAllClosedPL() { return mAllClosedPL; }  //total closed P/L for all elements in mPositions
		long getAllTotalPL() { return mAllTotalPL; }  //mAllOpenPL + mAllClosedPL. Positive = profit, negative = loss
		long getNetPosition() { return mNetPosition; }  //sum of all positions: positive for long, negative for short
		double getAveragePriceOfPosition() { return mAveragePriceOfPosition; }  //weighed avg. price of net position
		double getZeroProfitPrice() { return mZeroProfitPrice; }  //price at which mAllTotalPL would equal zero


	private:
		//class functions:

	private:
		//variables used inside functions - for speed:

///////////////////////////////////////////////////////////////
//OLD FROM PREVIOUS CLASS MIKEPOSITIONORDERS:
	//public:
	//	//MikePositionOrders(std::string name, long highestPrice);
	//	//~MikePositionOrders();
	//public://private:
	//	   //This class stores all the positions:
	//	PositionBook * positionbook;
	//	//This class stores all the orders:
	//	MikeOrderbook * orderbook;
	//public:
	//	//POSITION METHODS:
	//	//used for printing open positions in WidgetTable
	//	//temporary fix for refactoring - erase when not needed:
	//	::std::vector <MikePosition> refactoringPositionvector;
	//	const ::std::vector <MikePosition> * GetMikePositions();// {return &refactoringPositionvector; /*return &positionBook;*/ }
	//														  //	void newPosition(long price, long position);
	//														  //used by orderbook to update a position after an order is filled. NEEDS REVISION
	//	void fillposition(int posprice, long fillprice, long filledamount, long bidPrice, long askPrice);
	//	//calculates the total aggregate open P/L for all active positions of the whole book
	//	long CalcAllOpenPL(long bidprice, long askprice);
	//	//calculates the total aggregate closed P/L for all active positions of the whole book
	//	long CalcAllClosedPL(long bidprice, long askprice);
	//	//calculates the total aggregate total P/L (open+closed) for all active positions of the whole book
	//	long CalcAllTotalPL(long bidprice, long askprice);
	//	//calculates the total aggregate position for all active positions of the whole book
	//	long CalcTotalOpenPos();
	//	//calculate individual P/L for each position that is stored in the openPosIndex
	//	//this should be done before attempting to print out the positions
	//	void calculateIndividualPLs(long bidprice, long askprice);
	//	//prototype for printing activePositions. NOT IMPLEMENTED:
	//	void printoutActivePositions(long bidprice, long askprice);
	//	//not implemented yet:
	//	bool clearPosition(long price);
	//	//not used at the moment. do I still need this?
	//	bool changePostion(long price, long amount);
	//	//not implemented yet. gives the total open position above a certain price level:
	//	long totalOpenAbove(long price);
	//	//not implemented yet. gives the total open position below a certain price level:
	//	long totalOpenBelow(long price);
	//	//ORDER METHODS:
	//	void newOrder(MikeOrderType type, long orderPrice, long orderAmount);
	//	//checks fills for all orders stored in the openPosIndex
	//	void checkFills(long bidPrice, long askPrice);
	//	//goes through all the open orders stored in openOrderBook and updates openOrdersByPrice:
	//	void updateOpenOrdersByPrice();
	//	//prototype function to print out all orders in the console:
	//	void printoutAllOrders();//not implemented
	//	void cancelOrder(long orderId);//implement this
	//	void cancelAllOrdAtPrice(long price);//implement this
	//										 //REFACTORING:
	//										 //used for printing open orders in WidgetTable
	//	::std::vector <MikeOrdersAtPrice> refactorOrdersBP;
	//	const ::std::vector <MikeOrdersAtPrice> * GetOpOrdersbyPrice();// { return &orderbook->openOrdersByPrice;   /*return &refactorOrdersBP;*/ /*return &openOrdersByPrice;*/ }
	//private:
	//	//this is the size of positionBook. used in constructor to determine what is the highest price position that can be stored in positionBook.
	//	long PositionBookmaxPrice = 1000000;
	//	//naming the class to enable having multiple instances of MikePositionOrders for multiple different strategies. This is done during class construction:
	//	::std::string nameOfBook = "Unnamed";
	//	//simple timer for testing purposes:
	//	Timer timer;

	};


}  // namespace Mike


#endif//_POSORDERS_H_INCLUDED_