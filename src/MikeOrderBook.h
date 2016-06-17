#ifndef _MIKEORDERBOOK_H_INCLUDED_
#define _MIKEORDERBOOK_H_INCLUDED_

#include <vector>

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
	long price =0;
	long amount=0;
	
};

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







#endif //_MIKEORDERBOOK_H_INCLUDED_
