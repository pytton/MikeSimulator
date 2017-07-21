#include "PosOrders.h"
#include <iostream>
#include "WidgetTable.h"

using namespace std;

Mike::PosOrders::PosOrders()
{
	COMMENTSON = true;
//	myWidTable = new WidgetTable(10, 10, 20, 20, "myTable");
}

Mike::PosOrders::~PosOrders()
{
}

void Mike::PosOrders::updateAll(long bidPrice, long askPrice)
{
}

long Mike::PosOrders::newOrder(long price, long orderAmount, MikeOrderType orderType)
{
	if (COMMENTSON) cout << "Mike::PosOrders::newOrder called" << endl;
	//take care of OrderId:
	long currentOrderId = mOrderId;
	mOrderId++;
	
	//enter this new order into mOpenOrders:
	SetMikeOrder tempOrder;
	tempOrder.orderId = currentOrderId;
	tempOrder.ordertype = orderType;
	tempOrder.assignedToPosition = price;  //unused function now - could be modified later (maybe?)
	tempOrder.price = price;
	tempOrder.amount = orderAmount;
	tempOrder.isFilled = false;

	//TODO: uncomment and fix:
	mOpenOrders.insert(tempOrder);

	//caller of function gets mOrderId:
	return currentOrderId;
}

bool Mike::PosOrders::modifyOrder(int orderNumber, long price, MikeOrderType orderType)
{
	return false;
}

void Mike::PosOrders::checkFills(long bidPrice, long askPrice)
{	//Go through all open orders and check for fills.

	

	//check all the open orders in the indexOpenOrd index and fill as required:

	Orders mFilledOrders;//this has to be done because removing an element from indexOpenOrd while iterating through it causes the program to crash. so add OrderIds to be removed here and remove them later in a seperate loop.

	SetMikeOrder * ptr_ordertoprocess;

	bool updatebyprice = false;//if any order gets filled, the openOrdersByPrice vector will change and will need to be updated

	for (auto iter = mOpenOrders.begin(); iter != mOpenOrders.end(); iter++) {

		cout << "Checking fills. Order Id: " << iter->orderId << " Amount: " << iter->amount << endl;

		mFilledOrders.insert(*iter);

	}


	//for (auto OrderId : mOpenOrders)
	//{
	//	ptr_ordertoprocess = &OrderId;

	//	//check if BUYLMT order price is at or below the askPrice:
	//	if (ptr_ordertoprocess->ordertype == BUYLMT && ptr_ordertoprocess->price >= askPrice)
	//	{
	//		//fill the position that the ptr_ordertoprocess has been assigned to:
	//		int postofill = ptr_ordertoprocess->assignedToPosition;
	//		int filledprice = askPrice;//BUYLMT orders filled at ask price for now
	//		int filledamount = ptr_ordertoprocess->amount;//filling the whole order amount for now

	//		fill(postofill, filledprice, filledamount, bidPrice, askPrice);//BUY ORDERS FILL POSITIVE AMOUNTS. SELL ORDERS FILL NEGATIVE AMOUNTS. positive open_amount in MikePosition class means the position is 'long'. negative open_amount means the position is 'short'.

	//																	   //mark order as filled in orderbook vector:
	//		ptr_ordertoprocess->isFilled = true;
	//		//insert the order to indexClosedOrd which stores all closed orders:
	//		indexClosedOrd.insert(ptr_ordertoprocess->orderId);

	//		//mark this OrderId for removal from indexOpenOrd (which stores all open orders) after finishing iterating through it:
	//		removeFindexOpenOrd.insert(OrderId);
	//		//openOrdersByPrice will be outdated now - update it
	//		updatebyprice = true;
	//	}

	//	if (ptr_ordertoprocess->ordertype == SELLLMT && ptr_ordertoprocess->price <= bidPrice)
	//	{
	//		//fill the position that the ptr_ordertoprocess has been assigned to:
	//		int postofill = ptr_ordertoprocess->assignedToPosition;
	//		int filledprice = bidPrice;//SELLLMT orders filled at bid price for now
	//		int filledamount = ptr_ordertoprocess->amount;//filling the whole order amount for now

	//		fill(postofill, filledprice, (filledamount * -1), bidPrice, askPrice);//SELL ORDERS FILL NEGATIVE AMOUNTS. positive open_amount in MikePosition class means the position is 'long'. negative open_amount means the position is 'short'.

	//																			  //mark order as filled in orderbook vector:
	//		ptr_ordertoprocess->isFilled = true;
	//		//insert the order to indexClosedOrd which stores all closed orders:
	//		indexClosedOrd.insert(ptr_ordertoprocess->orderId);

	//		//mark this OrderId for removal from indexOpenOrd (which stores all open orders) after finishing iterating through it:
	//		removeFindexOpenOrd.insert(OrderId);
	//		//openOrdersByPrice will be outdated now - update it
	//		updatebyprice = true;
	//	}

	//	if (ptr_ordertoprocess->ordertype == BUYSTP && ptr_ordertoprocess->price <= askPrice)
	//	{
	//		//fill the position that the ptr_ordertoprocess has been assigned to:
	//		int postofill = ptr_ordertoprocess->assignedToPosition;
	//		int filledprice = askPrice;//BUYSTP orders filled at ask price for now
	//		int filledamount = ptr_ordertoprocess->amount;//filling the whole order amount for now

	//		fill(postofill, filledprice, filledamount, bidPrice, askPrice);

	//		//mark order as filled in orderbook vector:
	//		ptr_ordertoprocess->isFilled = true;
	//		//insert the order to indexClosedOrd which stores all closed orders:
	//		indexClosedOrd.insert(ptr_ordertoprocess->orderId);

	//		//mark this OrderId for removal from indexOpenOrd (which stores all open orders) after finishing iterating through it:
	//		removeFindexOpenOrd.insert(OrderId);
	//		//openOrdersByPrice will be outdated now - update it
	//		updatebyprice = true;
	//	}

	//	if (ptr_ordertoprocess->ordertype == SELLSTP && ptr_ordertoprocess->price >= bidPrice)
	//	{
	//		//fill the position that the ptr_ordertoprocess has been assigned to:
	//		int postofill = ptr_ordertoprocess->assignedToPosition;
	//		int filledprice = bidPrice;//SELLSTP orders filled at bid price for now
	//		int filledamount = ptr_ordertoprocess->amount;//filling the whole order amount for now

	//		fill(postofill, filledprice, (filledamount * -1), bidPrice, askPrice);//SELL ORDERS FILL NEGATIVE AMOUNTS. positive open_amount in MikePosition class means the position is 'long'. negative open_amount means the position is 'short'.

	//																			  //mark order as filled in orderbook vector:
	//		ptr_ordertoprocess->isFilled = true;
	//		//insert the order to indexClosedOrd which stores all closed orders:
	//		indexClosedOrd.insert(ptr_ordertoprocess->orderId);

	//		//mark this OrderId for removal from indexOpenOrd (which stores all open orders) after finishing iterating through it:
	//		removeFindexOpenOrd.insert(OrderId);
	//		//openOrdersByPrice will be outdated now - update it
	//		updatebyprice = true;
	//	}
	//}

	//remove the filled orders from the indexOpenOrd:
	//for (int OrdIdToRemove : removeFindexOpenOrd) indexOpenOrd.erase(OrdIdToRemove);

	//update the openOrdersByPrice if any order got filled:
	//if (updatebyprice) updateOpenOrdersByPrice();

	//	 cout << "\nChecking fills. Open orders: " << indexOpenOrd.size() << " Closed orders: " << indexClosedOrd.size() << " Checking fills took : " << timer.elapsed() << endl;



}

void Mike::PosOrders::cancelOrdersAtPrice(long price)
{
}

bool Mike::PosOrders::cancelOrder(int orderNumber)
{
	return false;
}
