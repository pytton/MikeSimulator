#ifndef _MikePositionsOrders_H_INCLUDED_
#define _MikePositionsOrders_H_INCLUDED_

/****************************************************************************************
This class handles all the positions and orders for a single strategy/algo.
It can be a 'manual' algo - meaning that all orders are entered by a human.
Or it can handle positions and fills/orders for any algo I come up with.
Algos might have their own different objects to handle decisions.
This class handles the basics - order entry, modification, cancellation, fills,
requests for open positions, P/L.

This class constits of these main elements:
m_openOrders
m_closedOrders
m_positionBook

//This class stores all the positions:
PositionBook * positionbook;

//This class stores all the orders:
OrderbookPrototype * orderbook;


For example - human presses 'buy lmt' button with a price corresponding to 547.
void newOrder(price, orderType) enteres the order into MikeOrder m_openOrders.
when void checkFills(bidPrice, askPrice) is called - all the elements of m_openOrders
are checked for fills. If an order is filled it is moved to MikeOrder m_closedOrders
and MikePositonBook m_openPositions is updated as required.

This class is used and controlled by the Control class.
The Control class might have as many of MikePosition classes as it needs - one for
each algo.

void calculatePL(bidPrice, askPrice)) is used to update the Profit/Loss of each
position in MikePositionBook

****************************************************************************************/
#include <unordered_set>
#include "MikeTimer.h"


class Timer;
class PositionBook;
class OrderbookPrototype;


enum BtnPressed;
enum MikeOrderType;

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

//this class aggregates all the open orders by price. there can be multiple orders of
//multiple kind and amount for a single price. this class keeps track of the total
//b lmt, b stp, s lmt, s stp orders for a single price point.
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
	long price =0 ;
	long open_amount =0;//positive open_amount means the position is 'long'. negative open_amount means the position is 'short'.
	long open_pl=0;
	long closed_pl=0;
	long total_pl=0;

private:
	bool isActive = false;
	long prevbidprice = 0;
	long prevaskprice = 0;

public:
	//this is for indexing purposes - set to TRUE if position was ever
	//accessed or changed. Mainly to avoid iterating through tens of thousands
	//of positions
	bool checkifActive() { if (isActive == true) return true; else  return false; }
	void setActive() { isActive = true; }
	void setInactive() { isActive = false; }

public:
	//positive amount for buy orders, negative amount for sell orders!
	void fill(long fillprice, long filledamount)
	{
		//this will modify the closed_pl by:
		//difference in fill price and price of this position
		//multiplied by amount
		long tempclosed_pl = closed_pl;
		long profitloss;
		profitloss = (price - fillprice) * filledamount;
		closed_pl = tempclosed_pl + profitloss;

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

class MikePositionOrders
{

public:
	MikePositionOrders(std::string name, long highestPrice);
	~MikePositionOrders();
private:
	//This class stores all the positions:
	PositionBook * positionbook;

	//This class stores all the orders:
	OrderbookPrototype * orderbook;
public:
	//POSITION METHODS:
	//used for printing open positions in WidgetTable
	//temporary fix for refactoring - erase when not needed:
	std::vector <MikePosition> refactoringPositionvector;
	const std::vector <MikePosition> * GetMikePositions();// {return &refactoringPositionvector; /*return &positionBook;*/ }
//	void newPosition(long price, long position);

	
	//used by orderbook to update a position after an order is filled. NOT IMPLEMENTED YET
	void fillposition(int posprice, long fillprice, long filledamount, long bidPrice, long askPrice);
	//calculates the total aggregate open P/L for all active positions of the whole book
	long CalcAllOpenPL(long bidprice, long askprice);
	//calculates the total aggregate closed P/L for all active positions of the whole book
	long CalcAllClosedPL(long bidprice, long askprice);
	//calculates the total aggregate total P/L (open+closed) for all active positions of the whole book
	long CalcAllTotalPL(long bidprice, long askprice);
	//calculates the total aggregate position for all active positions of the whole book
	long CalcTotalOpenPos();
	//calculate individual P/L for each position that is stored in the openPosIndex
	//this should be done before attempting to print out the positions
	void calculateIndividualPLs(long bidprice, long askprice);

	//prototype for printing activePositions:
	void printoutActivePositions(long bidprice, long askprice);

	//not implemented yet:
	bool clearPosition(long price);
	//not used at the moment. do I still need this?
	bool changePostion(long price, long amount);
	//not implemented yet. gives the total open position above a certain price level:
	long totalOpenAbove(long price);
	//not implemented yet. gives the total open position below a certain price level:
	long totalOpenBelow(long price);


	//ORDER METHODS:
	void newOrder(MikeOrderType type, long orderPrice, long orderAmount);
	//checks fills for all orders stored in the openPosIndex
	void checkFills(long bidPrice, long askPrice);
	//goes through all the open orders stored in openOrderBook and updates openOrdersByPrice:
	void updateOpenOrdersByPrice();
	//prototype function to print out all orders in the console:
	void printoutAllOrders();//not implemented

	void cancelOrder(long orderId);//implement this
	void cancelAllOrdAtPrice(long price);//implement this

	//REFACTORING:
	//used for printing open orders in WidgetTable
	std::vector <MikeOrdersAtPrice> refactorOrdersBP;
	const std::vector <MikeOrdersAtPrice> * GetOpOrdersbyPrice();// { return &orderbook->openOrdersByPrice;   /*return &refactorOrdersBP;*/ /*return &openOrdersByPrice;*/ }

private:

	//this is the size of positionBook. used in constructor to determine what is the highest price position that can be stored in positionBook.
	long PositionBookmaxPrice = 1000000; 

	//naming the class to enable having multiple instances of MikePositionOrders for multiple different strategies. This is done during class construction:
	std::string nameOfBook = "Unnamed";

	//simple timer for testing purposes:
	Timer timer;

};





#endif //_MikePositionsOrders_H_INCLUDED_
