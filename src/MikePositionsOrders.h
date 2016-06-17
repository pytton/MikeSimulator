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



#include <vector>
#include <string>

#include "MikeEnums.h"


class MikeOrder
{
public:
	MikeOrder();
	~MikeOrder();


	//for future use - for passing orders into outside API
	long orderId;
	//BUYLMT, SELLLMT, BUYSTP, SELLSTP
	MikeOrderType ordertype;
	long assignedToPosition = 0;
	long price = 0;
	long amount = 0;

};




class MikePosition
{
public:
	long price;
	long open_amount;
	long open_pl;
	long closed_pl;
	long total_pl;


	//this is for indexing purposes - set to TRUE if position was ever
	//accessed or changed. Mainly to avoid iterating through tens of thousands
	//of positions
	bool isActive = false;

	MikePosition();
};//class MikePosition



class MikePositionOrders
{
public:
	MikePositionOrders();
	~MikePositionOrders();

protected:


public:
	//MikeOrderBook();
	//~MikeOrderBook();

	void newOrder(MikeOrderType type, long orderPrice, long orderAmount);
	void checkFills(long bidPrice, long askPrice);

	//prototype function to print out all orders in the console:
	void printoutAllOrders();

	//MikeOrder getOrder(long price);
	//void modifyOrder();

private:
	//this array stores all the orders.
	//figure out how to design this
	std::vector <MikeOrder> openOrderBook;

	//for generating unique orderIds:
	long generateID();





public:

//	PositionBook(std::string name, long highestPrice);

	void newPosition(long price, long position);
	MikePosition getPosition(long price);
	bool clearPosition(long price);
	bool changePostion(long price, long amount);

	//calculates the total open P/L for all active positions
	long calculatedTotalOpenPL();

	//calculates the total closed P/L for all active positions
	long calculatedTotalClosedPL();

	//calculates the total total_pl P/L for all active positions
	long calculateTotalTotalPL();

	//gives the total open position above a certain price level:
	long totalOpenAbove(long price);

	//gives the total open position below a certain price level:
	long totalOpenBelow(long price);



private:
	//stores all the positions
	//the vector number reflects the price in cents - eg positionBook[10073]
	//reflects a price of 100 dollars and 73 cents
	std::vector <MikePosition> positionBook;
	std::string nameOfBook;

	long minPrice; //stores the price of the smallest active position - for quicker iterating through all of book
	long maxPrice; //highest active price - for index

				   //for knowing which postitions are active or not - if I need to access only
				   //the 'not empty' positions
	std::vector <long> index;






};

MikePositionOrders::MikePositionOrders()
{
}

MikePositionOrders::~MikePositionOrders()
{
}



class MikeOrderBook
{
public:
	MikeOrderBook();
	~MikeOrderBook();

	void newOrder(MikeOrderType type, long orderPrice, long orderAmount);
	void checkFills(long bidPrice, long askPrice);

	//prototype function to print out all orders in the console:
	void printoutAllOrders();

	//MikeOrder getOrder(long price);
	//void modifyOrder();

private:
	//this array stores all the orders.
	//figure out how to design this
	std::vector <MikeOrder> openOrderBook;

	//for generating unique orderIds:
	long generateID();

};




class PositionBook
{

public:

	PositionBook(std::string name, long highestPrice);

	void newPosition(long price, long position);
	MikePosition getPosition(long price);
	bool clearPosition(long price);
	bool changePostion(long price, long amount);

	//calculates the total open P/L for all active positions
	long calculatedTotalOpenPL();

	//calculates the total closed P/L for all active positions
	long calculatedTotalClosedPL();

	//calculates the total total_pl P/L for all active positions
	long calculateTotalTotalPL();

	//gives the total open position above a certain price level:
	long totalOpenAbove(long price);

	//gives the total open position below a certain price level:
	long totalOpenBelow(long price);



private:
	//stores all the positions
	//the vector number reflects the price in cents - eg positionBook[10073]
	//reflects a price of 100 dollars and 73 cents
	std::vector <MikePosition> positionBook;
	std::string nameOfBook;

	long minPrice; //stores the price of the smallest active position - for quicker iterating through all of book
	long maxPrice; //highest active price - for index

				   //for knowing which postitions are active or not - if I need to access only
				   //the 'not empty' positions
	std::vector <long> index;


};











#endif //_MikePositionsOrders_H_INCLUDED_
