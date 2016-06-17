#include "MikeOrderBook.h"

#include <sstream>
#include <iostream>
#include <string>

MikeOrderBook::MikeOrderBook()
{
	using namespace std;
	openOrderBook.clear();
	cout << endl << "OrderBook created." << endl;
	
}

MikeOrderBook::~MikeOrderBook()
{
}


void MikeOrderBook::newOrder(MikeOrderType type, long orderPrice, long orderAmount)
{
	using namespace std;
	long newOrderId = generateID();
	string tempOrderType;
	//if (type == BUYLMT) tempOrderType = "Buy Limit";

	cout << "new order received. Type: " << /*tempOrderType<<*/ " " << type << " Price: " <<
		orderPrice << " Size: " << orderAmount << " Order ID: " << newOrderId << endl;

	MikeOrder tempOrder;

	tempOrder.orderId = newOrderId;
	tempOrder.ordertype = type;
	tempOrder.assignedToPosition = orderPrice;
	tempOrder.price = orderPrice;
	tempOrder.amount = orderAmount;

	openOrderBook.push_back(tempOrder);

}

void MikeOrderBook::checkFills(long bidPrice, long askPrice)
{
	using namespace std;
	cout << "Checking fills... Not implemented yet" << endl;
}

void MikeOrderBook::printoutAllOrders()
{
	using namespace std;
	MikeOrder temp;
	for (int i = 0; i < openOrderBook.size(); ++i)
	{
		temp = openOrderBook[i];
		cout << "Order ID: " << temp.orderId << " Order Price: " << temp.price << endl;
	}
}

long MikeOrderBook::generateID()
{
	static long s_itemID = 0;
	return s_itemID++;
}



MikeOrder::MikeOrder()
{

}

MikeOrder::~MikeOrder()
{
}