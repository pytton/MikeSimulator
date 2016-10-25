#include <iostream>
#include "OrderbookPrototype.h"
#include "MikePositionsOrders.h"

#include "MikeEnums.h"
#include <vector>
#include <unordered_set>

#include "PositionBook.h"
#include "MikeTimer.h"


	OrderbookPrototype::OrderbookPrototype(MikePositionOrders * p_mikepositionorders)
	{
		mypositionbook = p_mikepositionorders;
		allOrders.clear();
		indexOpenOrd.clear();
		indexClosedOrd.clear();
	}

	//OrderbookPrototype::OrderbookPrototype(PositionBook * positionbook)
	//{
	//	//mypositionbook = positionbook;
	//	//allOrders.clear();
	//	//indexOpenOrd.clear();
	//	//indexClosedOrd.clear();
	//}


	OrderbookPrototype::~OrderbookPrototype()
	{
	}

	int OrderbookPrototype::neworder(MikeOrderType type, long orderPrice, long orderAmount)
	{

		//below copied from MikePositionOrders:
		using namespace std;
		long currNewOrderId = newOrderId;

		//enter the order in the correct format:
		MikeOrder tempOrder;

		tempOrder.orderId = currNewOrderId;
		tempOrder.ordertype = type;
		tempOrder.assignedToPosition = orderPrice;
		tempOrder.price = orderPrice;
		tempOrder.amount = orderAmount;
		tempOrder.isFilled = false;

		allOrders.push_back(tempOrder);//add this new order into the vector that stores all the orders ever entered/processed.

		//update the Open Orders index!
		indexOpenOrd.insert(currNewOrderId);

		//below just for printing out confirmation in console - erase for speed if neccessa	
		//string tempOrderType;
		//switch (type)
		//{
		//case CXLORDER:
		//	tempOrderType = "CANCEL";
		//	break;
		//case BUYLMT:
		//	tempOrderType = "BUY LIMIT";
		//	break;
		//case BUYSTP:
		//	tempOrderType = "BUY STOP";
		//	break;
		//case SELLLMT:
		//	tempOrderType = "SELL LIMIT";
		//	break;
		//case SELLSTP:
		//	tempOrderType = "SELL STOP";
		//	break;
		//default:
		//	break;
		//}
		//cout << "new order received. Type: " << tempOrderType << " Price: " <<
		//	orderPrice << " Size: " << orderAmount << " Order ID: " << currNewOrderId << endl;

		cout << "Prototype newOrder called! Order price: " << orderPrice << endl <<
			"Size of allOrders in Prototype: " << allOrders.size() << endl <<
			"newOrderId value before incrementing: " << newOrderId << endl <<
			"size of indexOpenOrd: " << indexOpenOrd.size() << endl;

		//increment the orderId inside the Orderbook class - THIS IS CRUCIAL to ensure that the index of the allOrders vector matches the OrderId of the Order stored under that index. Eg. allOrders.at(234) should store an order with OrderId = 234
		newOrderId++;

		return currNewOrderId; //returns the OrderId of the just created order to the caller of the function
	}



	void OrderbookPrototype::checkfills(long bidPrice, long askPrice)
	{
		//copied from MikePositionOrders:
		using namespace std;
		//WORK IN PROGRESS BELOW:
		//Go through all open orders and check for fills.

		Timer timer;
		timer.reset();

		//check all the open orders in the indexOpenOrd index and fill as required:

		MikeOrder * ordertoprocess;

		for (int OrderId : indexOpenOrd)
		{
			ordertoprocess = &allOrders[OrderId];

			//check if BUYLMT order price is at or below the askPrice:
			if (ordertoprocess->ordertype == BUYLMT && ordertoprocess->price >= askPrice)
			{
				//fill the position that the ordertoprocess has been assigned to:


				//calculate the P/L for the position

				//see if it is still active:

				//mark order as filled in orderbook:

				//copy the order to closedorderbook
			}

		}


		//for (unsigned int i = 0; i < openOrderBook.size(); i++)
		//{
		//	MikeOrder order;
		//	//MikeOrder * ptr_order = &openOrderBook.at(i);
		//	order = openOrderBook.at(i);


		//	if (openOrderBook.at(i).isFilled == false)
		//	{
		//		//check buy limit orders only for now. do rest later:
		//		if (order.ordertype == BUYLMT)
		//		{	//if ask price is below BUY LIMIT ORDER price, fill it at ask price 
		//			//and move the order from openOrderBook to closedOrderBook
		//			if (order.price >= askPrice)
		//			{
		//				//fill the position:
		//				positionBook.at(order.assignedToPosition).fill(askPrice, order.amount);
		//				//calculate the P/L for the position:
		//				positionBook.at(order.assignedToPosition).calculatePL(bidPrice, askPrice);
		//				//see if it is still active:
		//				checkIfStillActive(order.assignedToPosition);
		//				//mark order as filled in openOrderBook:
		//				openOrderBook.at(i).isFilled = true;
		//				//copy the order to closedOrderBook:
		//				closedOrderBook.push_back(order);

		//				//TODO: update the openOrdersByPrice vector!!!!

		//				cout << " Order ID: " << order.orderId << " Filled at price: " << askPrice << endl;
		//			}

		//		}
		//		//if (order.ordertype == SELLLMT)
		//		//{	//if bid price is above SELL LIMIT ORDER price, fill it at bid price 
		//		//	//and move the order from openOrderBook to closedOrderBook
		//		//	if (order.price <= bidPrice)
		//		//	{
		//		//		//fill the position:
		//		//		positionBook.at(order.assignedToPosition).fill(bidPrice, (order.amount) * -1);
		//		//		//calculate the P/L for the position:
		//		//		positionBook.at(order.assignedToPosition).calculatePL(bidPrice, askPrice);
		//		//		//see if it is still active:
		//		//		checkIfStillActive(order.assignedToPosition);
		//		//		//mark order as filled in openOrderBook:
		//		//		openOrderBook.at(i).isFilled = true;
		//		//		//copy the order to closedOrderBook:
		//		//		closedOrderBook.push_back(order);

		//		//		cout << " Order ID: " << order.orderId << " Filled at price: " << bidPrice << endl;
		//		//	}

		//		//}
		//		//if (order.ordertype == BUYSTP)
		//		//{	//if ask price is above BUY STOP ORDER price, fill it at ask price
		//		//	//and move the order from openOrderBook to closedOrderBook
		//		//	if (order.price <= askPrice)
		//		//	{
		//		//		//fill the position:
		//		//		positionBook.at(order.assignedToPosition).fill(askPrice, order.amount);
		//		//		//calculate the P/L for the position:
		//		//		positionBook.at(order.assignedToPosition).calculatePL(bidPrice, askPrice);
		//		//		//see if it is still active:
		//		//		checkIfStillActive(order.assignedToPosition);
		//		//		//mark order as filled in openOrderBook:
		//		//		openOrderBook.at(i).isFilled = true;
		//		//		//copy the order to closedOrderBook:
		//		//		closedOrderBook.push_back(order);

		//		//		cout << " Order ID: " << order.orderId << " Filled at price: " << askPrice << endl;
		//		//	}

		//		//}
		//		//if (order.ordertype == SELLSTP)
		//		//{	//if bid price is below SELL STOP ORDER price, fill it at bid price 
		//		//	//and move the order from openOrderBook to closedOrderBook
		//		//	if (order.price >= askPrice)
		//		//	{
		//		//		//fill the position:
		//		//		positionBook.at(order.assignedToPosition).fill(bidPrice, (order.amount) * -1);
		//		//		//calculate the P/L for the position:
		//		//		positionBook.at(order.assignedToPosition).calculatePL(bidPrice, askPrice);
		//		//		//see if it is still active:
		//		//		checkIfStillActive(order.assignedToPosition);
		//		//		//mark order as filled in openOrderBook:
		//		//		openOrderBook.at(i).isFilled = true;
		//		//		//copy the order to closedOrderBook:
		//		//		closedOrderBook.push_back(order);

		//		//		cout << " Order ID: " << order.orderId << " Filled at price: " << bidPrice << endl;
		//		//	}

		//		//}

		//	}

		//}

		////erase all filled orders from openOrderBook:

		//for (unsigned int i = 0; i < openOrderBook.size();)
		//{
		//	if (openOrderBook.at(i).isFilled == true)
		//	{
		//		openOrderBook.erase(openOrderBook.begin() + i);
		//		i = 0;
		//		continue;
		//	}
		//	i++;
		//}
		//cout << "\nChecking fills. Open orders: " << openOrderBook.size() <<
		//	" Closed orders: " << closedOrderBook.size() <<
		//	" Checking fills took : " << timer.elapsed() << endl;




	}

	void OrderbookPrototype::cancelordersatprice(int price)
	{
	}

	//Mike::OrderbookPrototype::checkstatusoforder(long orderID)
	//{
	//	OrderStatus orderstatus = CANCELLED;
	//	return orderstatus;
	//}

	MikeOrdersAtPrice OrderbookPrototype::totOrdAmtatPrice()
	{
		MikeOrdersAtPrice myOrders;
		return MikeOrdersAtPrice();
	}

	void OrderbookPrototype::modifyorder(long orderID)
	{
	}

	void OrderbookPrototype::cancelorder(long orderID)
	{
	}

	

