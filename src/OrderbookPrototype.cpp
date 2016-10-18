#include "OrderbookPrototype.h"
#include "MikePositionsOrders.h"

//class MikeOrdersAtPrice;

using namespace Mike;

//Mike::OrderbookPrototype::OrderbookPrototype()
//{
//}

Mike::OrderbookPrototype::OrderbookPrototype(MikePositionOrders * positionbook)
{
	mypositionbook = positionbook;
	allOrders.clear();
	indexOpenOrd.clear();
	indexClosedOrd.clear();
}


Mike::OrderbookPrototype::~OrderbookPrototype()
{
}

int Mike::OrderbookPrototype::neworder(MikeOrderType type, long orderPrice, long orderAmount)
{

	//below copied from MikePositionOrders:
	using namespace std;
	long currNewOrderId = newOrderId;
	string tempOrderType;
	


	MikeOrder tempOrder;

	tempOrder.orderId = currNewOrderId;
	tempOrder.ordertype = type;
	tempOrder.assignedToPosition = orderPrice;
	tempOrder.price = orderPrice;
	tempOrder.amount = orderAmount;
	tempOrder.isFilled = false;



	allOrders.push_back(tempOrder);//add this new order into the vector that stores all the orders ever entered/processed.

	indexOpenOrd.insert(currNewOrderId);






//	openOrderBook.push_back(tempOrder);

	//TODO: update the openOrdersByPrice vector!!!!
	
	//below just for printing out confirmation in console - erase for speed if neccessa	
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

void Mike::OrderbookPrototype::modifyorder(long orderID)
{
}

void Mike::OrderbookPrototype::cancelorder(long orderID)
{
}

void Mike::OrderbookPrototype::checkfills(long bidPrice, long askPrice)
{
}

void Mike::OrderbookPrototype::cancelordersatprice(int price)
{
}

OrderStatus Mike::OrderbookPrototype::checkstatusoforder(long orderID)
{
	OrderStatus orderstatus = CANCELLED;
	return orderstatus;
}

MikeOrdersAtPrice Mike::OrderbookPrototype::totOrdAmtatPrice()
{
	MikeOrdersAtPrice myOrders;
	return MikeOrdersAtPrice();
}
