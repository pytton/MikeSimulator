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
MikeOrderbook * orderbook;


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
#include "MikeEnums.h"
#include "MikeTimer.h"

#include <unordered_set>


class Timer;
class PositionBook;
class MikeOrderbook;
enum class BtnPressed;
enum MikeOrderType;



class MikePositionOrders
{

public:
	MikePositionOrders(std::string name, long highestPrice);
	~MikePositionOrders();
public://private:
	//This class stores all the positions:
	PositionBook * positionbook;

	//This class stores all the orders:
	MikeOrderbook * orderbook;
public:
	//POSITION METHODS:
	//used for printing open positions in WidgetTable
	//temporary fix for refactoring - erase when not needed:
//	std::vector <MikePosition> refactoringPositionvector;
	const std::vector <MikePosition> * GetMikePositions();// {return &refactoringPositionvector; /*return &positionBook;*/ }
//	void newPosition(long price, long position);

	
	//used by orderbook to update a position after an order is filled. NEEDS REVISION
	void fillposition(int posprice, long fillprice, long filledamount, long bidPrice, long askPrice);
	//calculates the total aggregate open P/L for all active positions of the whole book
	long CalcAllOpenPL(long bidprice, long askprice);
	//calculates the total aggregate closed P/L for all active positions of the whole book
	long CalcAllClosedPL(long bidprice, long askprice);
	//calculates the total aggregate total P/L (open+closed) for all active positions of the whole book
	long CalcAllTotalPL(long bidprice, long askprice);
	//calculates the total aggregate position for all active positions of the whole book
	long CalcTotalOpenPos();
	//calculate average weighed position price:
	double CalcAvgPos();
	//calculate individual P/L for each position that is stored in the openPosIndex
	//this should be done before attempting to print out the positions
	void calculateIndividualPLs(long bidprice, long askprice);
	//Clears out all Positions - sets everything to zero
	void clearAllPositions();

	//prototype for printing activePositions. NOT IMPLEMENTED:
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

	void cancelOrder(long orderId);
	void cancelAllOrdAtPrice(long price);
	void cancelAllOpenOrders();

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
