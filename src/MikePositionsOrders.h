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

#include <time.h> //for clock_t, clock, CLOCKS_PER_SEC

#include <vector>
#include <string>
#include <set>
#include <unordered_set>

#include "OrderbookPrototype.h"
#include "MikeEnums.h"
#include "MikeTimer.h"



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

	//the price of the order
	long price = 0;

	//the size of the order
	long amount = 0;

	//for future use - for passing orders into outside API
	int orderId;

	//for checking fills - has the order been filled already?
	bool isFilled = false;
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

	void eraseall();

	//returns true if all orders are empty at this price
	bool checkifempty();

	
};


class MikePosition
{
public:
	long price =0 ;
	long open_amount =0;
	long open_pl=0;
	long closed_pl=0;
	long total_pl=0;


	//this is for indexing purposes - set to TRUE if position was ever
	//accessed or changed. Mainly to avoid iterating through tens of thousands
	//of positions
	bool isActive = false;

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
		static long prevbidprice = 0;
		static long prevaskprice = 0;
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

	//POSITION METHODS:
	//used for printing open positions in WidgetTable
	const std::vector <MikePosition> * GetMikePositions() { return   &positionBook; }
	void newPosition(long price, long position);
	MikePosition getPosition(long price);
	
	
	//calculates the total aggregate open P/L for all active positions of the whole book
	long AllOpenPL(long bidprice, long askprice);
	//calculates the total aggregate closed P/L for all active positions of the whole book
	long AllClosedPL(long bidprice, long askprice);
	//calculates the total aggregate total P/L (open+closed) for all active positions of the whole book
	long AllTotalPL(long bidprice, long askprice);
	//calculates the total aggregate position for all active positions of the whole book
	long TotalOpenPos();
	//calculate individual P/L for each position that is stored in the openPosIndex
	//this should be done before attempting to print out the positions
	void calculateIndividualPLs(long bidprice, long askprice);

	//prototype for printing activePositions:
	void printoutActivePositions(long bidprice, long askprice);

	////not implemented yet:
	//bool clearPosition(long price);
	////not used at the moment. do I still need this?
	//bool changePostion(long price, long amount);
	////not implemented yet. gives the total open position above a certain price level:
	//long totalOpenAbove(long price);
	////not implemented yet. gives the total open position below a certain price level:
	//long totalOpenBelow(long price);


	//ORDER METHODS:
	void newOrder(MikeOrderType type, long orderPrice, long orderAmount);
	//checks fills for all orders stored in the openPosIndex
	void checkFills(long bidPrice, long askPrice);
	//goes through all the open orders stored in openOrderBook and updates openOrdersByPrice:
	void updateOpenOrdersByPrice();
	//used for printing open orders in WidgetTable
	const std::vector <MikeOrdersAtPrice> * GetOpOrdersbyPrice() { return &openOrdersByPrice; }
	//prototype function to print out all orders in the console:
	void printoutAllOrders();


	//NEW ORDER HANDLING PROTOTYPE:
	//for now, these are just funcions copied from previous implementation of 'Order Methods' with a 'prot' prefix. remove as neccessary after new implementation tested
	
	Mike::OrderbookPrototype * orderbook;
	void protnewOrder(MikeOrderType type, long orderPrice, long orderAmount);
	//checks fills for all orders stored in the openPosIndex
	void protcheckFills(long bidPrice, long askPrice);
	//goes through all the open orders stored in openOrderBook and updates openOrdersByPrice:
	void protupdateOpenOrdersByPrice();
	//used for printing open orders in WidgetTable
	const std::vector <MikeOrdersAtPrice> * protGetOpOrdersbyPrice() { return &openOrdersByPrice; }
	//prototype function to print out all orders in the console:
	void protprintoutAllOrders();




private:





	//this array stores all the orders.
	//figure out how to design this
	std::vector <MikeOrder> openOrderBook;

	//this array stores all closed orders:
	std::vector<MikeOrder> closedOrderBook;

	//how do I do this???
	//this stores all the orders sorted by price:
	std::vector<MikeOrdersAtPrice> openOrdersByPrice;

	//stores all the positions
	//the vector number reflects the price in cents - eg positionBook[10073]
	//reflects a price of 100 dollars and 73 cents
	std::vector <MikePosition> positionBook;
	

	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	
	// INDEX:

	//stores the prices of active postions.
	//for knowing which postitions are active or not - if I need to access only the 'not empty' positions. 
//	std::vector <long> openPosIndex;	//original index
	std::unordered_set<long> openPosIndexSet;	//trying to implement a faster way
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////

	//this is the size of positionBook. used in constructor to determine what is the highest price position
	//that can be stored in positionBook.
	long PositionBookmaxPrice = 1000000; 


	//check if any members of this position are other than zero if they are - designate the position as active
	//and add to active position index if everything is zero - designate the position as not active and remove from active position index:
	bool checkIfStillActive(long price);
	//add position to active position index:
	void addPosToIndex(long price);
	//remove position from active position index:
	void remPosFromIndex(long price);

	//naming the class to enable having multiple instances of MikePositionOrders
	//for multiple different strategies. This is done during class construction:
	std::string nameOfBook;
	//for generating unique orderIds:
	long generateID();

	//simple timer for testing purposes:
	Mike::Timer timer;

};





#endif //_MikePositionsOrders_H_INCLUDED_
