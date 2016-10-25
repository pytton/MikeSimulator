//#pragma once
//
//#include "MikeEnums.h"
//#include <vector>
//#include <unordered_set>
////#include <algorithm>
//#include "MikePositionsOrders.h"
//
//class MikeOrder;
//class MikeOrdersAtPrice;
//class MikePositionOrders;
//
//
//class NewPosOrders
//{
//public:
//	NewPosOrders();
//	~NewPosOrders();
//
//	//POSITION METHODS:
//	//used for printing open positions in WidgetTable
//	const std::vector <MikePosition> * GetMikePositions() { return   &positionBook; }
//	void newPosition(long price, long position);
//	MikePosition getPosition(long price);
//
//	//used by orderbook to update a position after an order is filled
//	void fillposition(int posprice, long fillprice, long filledamount);
//	//calculates the total aggregate open P/L for all active positions of the whole book
//	long AllOpenPL(long bidprice, long askprice);
//	//calculates the total aggregate closed P/L for all active positions of the whole book
//	long AllClosedPL(long bidprice, long askprice);
//	//calculates the total aggregate total P/L (open+closed) for all active positions of the whole book
//	long AllTotalPL(long bidprice, long askprice);
//	//calculates the total aggregate position for all active positions of the whole book
//	long TotalOpenPos();
//	//calculate individual P/L for each position that is stored in the openPosIndex
//	//this should be done before attempting to print out the positions
//	void calculateIndividualPLs(long bidprice, long askprice);
//
//	//prototype for printing activePositions:
//	void printoutActivePositions(long bidprice, long askprice);
//
//	////not implemented yet:
//	//bool clearPosition(long price);
//	////not used at the moment. do I still need this?
//	//bool changePostion(long price, long amount);
//	////not implemented yet. gives the total open position above a certain price level:
//	//long totalOpenAbove(long price);
//	////not implemented yet. gives the total open position below a certain price level:
//	//long totalOpenBelow(long price);
//
//
//	//ORDER METHODS:
//	void newOrder(MikeOrderType type, long orderPrice, long orderAmount);
//	//checks fills for all orders stored in the openPosIndex
//	void checkFills(long bidPrice, long askPrice);
//	//goes through all the open orders stored in openOrderBook and updates openOrdersByPrice:
//	void updateOpenOrdersByPrice();
//	//used for printing open orders in WidgetTable
//	const std::vector <MikeOrdersAtPrice> * GetOpOrdersbyPrice() { return &openOrdersByPrice; }
//	//prototype function to print out all orders in the console:
//	void printoutAllOrders();
//
//
//	//NEW ORDER HANDLING PROTOTYPE:
//	//for now, these are just funcions copied from previous implementation of 'Order Methods' with a 'prot' prefix. remove as neccessary after new implementation tested
//
//	OrderbookPrototype * orderbook;
//	void protnewOrder(MikeOrderType type, long orderPrice, long orderAmount);
//	//checks fills for all orders stored in the openPosIndex
//	void protcheckFills(long bidPrice, long askPrice);
//	//goes through all the open orders stored in openOrderBook and updates openOrdersByPrice:
//	void protupdateOpenOrdersByPrice();
//	//used for printing open orders in WidgetTable
//	const std::vector <MikeOrdersAtPrice> * protGetOpOrdersbyPrice() { return &openOrdersByPrice; }
//	//prototype function to print out all orders in the console:
//	void protprintoutAllOrders();
//
//
//private:
//
//	//this array stores all the orders.
//	//figure out how to design this
//	std::vector <MikeOrder> openOrderBook;
//
//	//this array stores all closed orders:
//	std::vector<MikeOrder> closedOrderBook;
//
//	//how do I do this???
//	//this stores all the orders sorted by price:
//	std::vector<MikeOrdersAtPrice> openOrdersByPrice;
//
//
//
//
//	//stores all the positions
//	//the vector number reflects the price in cents - eg positionBook[10073]
//	//reflects a price of 100 dollars and 73 cents
//	std::vector <MikePosition> positionBook;
//
//
//	///////////////////////////////////////////////////////////
//	///////////////////////////////////////////////////////////
//
//	// INDEX:
//
//	//stores the prices of active postions.
//	//for knowing which postitions are active or not - if I need to access only the 'not empty' positions. 
//	//	std::vector <long> openPosIndex;	//original index
//	std::unordered_set<long> openPosIndexSet;	//trying to implement a faster way
//												///////////////////////////////////////////////////////////
//												///////////////////////////////////////////////////////////
//
//												//this is the size of positionBook. used in constructor to determine what is the highest price position
//												//that can be stored in positionBook.
//	long PositionBookmaxPrice = 1000000;
//
//
//	//check if any members of this position are other than zero if they are - designate the position as active
//	//and add to active position index if everything is zero - designate the position as not active and remove from active position index:
//	bool checkIfStillActive(long price);
//	//add position to active position index:
//	void addPosToIndex(long price);
//	//remove position from active position index:
//	void remPosFromIndex(long price);
//
//	//naming the class to enable having multiple instances of MikePositionOrders
//	//for multiple different strategies. This is done during class construction:
//	std::string nameOfBook;
//	//for generating unique orderIds:
//	long generateID();
//
//	//simple timer for testing purposes:
//	Mike::Timer timer;
//
//
//};
//
