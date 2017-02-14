//#define COMMENTSOFF //
#include <iostream>
#include "OrderbookPrototype.h"
#include "MikePositionsOrders.h"

#include "MikeEnums.h"
#include <vector>
#include <unordered_set>

#include "PositionBook.h"
#include "MikeTimer.h"

OrderbookPrototype::OrderbookPrototype(MikePositionOrders * p_mikepositionorders, long highestprice)
	{
		mypositionorders = p_mikepositionorders;
		allOrders.clear();
		indexOpenOrd.clear();
		indexClosedOrd.clear();
		openOrdersByPrice.resize(highestprice +1);
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

		//openOrdersByPrice will be outdated now - update it
		updateOpenOrdersByPrice();

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

		MikeOrder * ptr_ordertoprocess;

		unordered_set <int> removeFindexOpenOrd;//this has to be done because removing an element from indexOpenOrd while iterating through it causes the program to crash. so add OrderIds to be removed here and remove them later in a seperate loop.

		bool updatebyprice = false;//if any order gets filled, the openOrdersByPrice vector will change and will need to be updated

			for (int OrderId : indexOpenOrd)
			{
				ptr_ordertoprocess = &allOrders[OrderId];

				//check if BUYLMT order price is at or below the askPrice:
				if (ptr_ordertoprocess->ordertype == BUYLMT && ptr_ordertoprocess->price >= askPrice)
				{
					//fill the position that the ptr_ordertoprocess has been assigned to:
					int postofill= ptr_ordertoprocess->assignedToPosition;
					int filledprice = askPrice;//BUYLMT orders filled at ask price for now
					int filledamount = ptr_ordertoprocess->amount;//filling the whole order amount for now

					fill(postofill, filledprice, filledamount, bidPrice, askPrice);//BUY ORDERS FILL POSITIVE AMOUNTS. SELL ORDERS FILL NEGATIVE AMOUNTS. positive open_amount in MikePosition class means the position is 'long'. negative open_amount means the position is 'short'.

					//mark order as filled in orderbook vector:
					ptr_ordertoprocess->isFilled = true;
					//insert the order to indexClosedOrd which stores all closed orders:
					indexClosedOrd.insert(ptr_ordertoprocess->orderId);
					
					//mark this OrderId for removal from indexOpenOrd (which stores all open orders) after finishing iterating through it:
					removeFindexOpenOrd.insert(OrderId);
					//openOrdersByPrice will be outdated now - update it
					updatebyprice = true;
				}

				if (ptr_ordertoprocess->ordertype == SELLLMT && ptr_ordertoprocess->price <= bidPrice)
				{
					//fill the position that the ptr_ordertoprocess has been assigned to:
					int postofill = ptr_ordertoprocess->assignedToPosition;
					int filledprice = bidPrice;//SELLLMT orders filled at bid price for now
					int filledamount = ptr_ordertoprocess->amount;//filling the whole order amount for now

					fill(postofill, filledprice, (filledamount * -1), bidPrice, askPrice);//SELL ORDERS FILL NEGATIVE AMOUNTS. positive open_amount in MikePosition class means the position is 'long'. negative open_amount means the position is 'short'.

					//mark order as filled in orderbook vector:
					ptr_ordertoprocess->isFilled = true;
					//insert the order to indexClosedOrd which stores all closed orders:
					indexClosedOrd.insert(ptr_ordertoprocess->orderId);

					//mark this OrderId for removal from indexOpenOrd (which stores all open orders) after finishing iterating through it:
					removeFindexOpenOrd.insert(OrderId);
					//openOrdersByPrice will be outdated now - update it
					updatebyprice = true;
				}

				if (ptr_ordertoprocess->ordertype == BUYSTP && ptr_ordertoprocess->price <= askPrice)
				{
					//fill the position that the ptr_ordertoprocess has been assigned to:
					int postofill = ptr_ordertoprocess->assignedToPosition;
					int filledprice = askPrice;//BUYSTP orders filled at ask price for now
					int filledamount = ptr_ordertoprocess->amount;//filling the whole order amount for now

					fill(postofill, filledprice, filledamount, bidPrice, askPrice);

					//mark order as filled in orderbook vector:
					ptr_ordertoprocess->isFilled = true;
					//insert the order to indexClosedOrd which stores all closed orders:
					indexClosedOrd.insert(ptr_ordertoprocess->orderId);

					//mark this OrderId for removal from indexOpenOrd (which stores all open orders) after finishing iterating through it:
					removeFindexOpenOrd.insert(OrderId);
					//openOrdersByPrice will be outdated now - update it
					updatebyprice = true;
				}

				if (ptr_ordertoprocess->ordertype == SELLSTP && ptr_ordertoprocess->price >= bidPrice)
				{
					//fill the position that the ptr_ordertoprocess has been assigned to:
					int postofill = ptr_ordertoprocess->assignedToPosition;
					int filledprice = bidPrice;//SELLSTP orders filled at bid price for now
					int filledamount = ptr_ordertoprocess->amount;//filling the whole order amount for now

					fill(postofill, filledprice, (filledamount * -1), bidPrice, askPrice);//SELL ORDERS FILL NEGATIVE AMOUNTS. positive open_amount in MikePosition class means the position is 'long'. negative open_amount means the position is 'short'.

					//mark order as filled in orderbook vector:
					ptr_ordertoprocess->isFilled = true;
					//insert the order to indexClosedOrd which stores all closed orders:
					indexClosedOrd.insert(ptr_ordertoprocess->orderId);

					//mark this OrderId for removal from indexOpenOrd (which stores all open orders) after finishing iterating through it:
					removeFindexOpenOrd.insert(OrderId);
					//openOrdersByPrice will be outdated now - update it
					updatebyprice = true;
				}
			}
		
		//remove the filled orders from the indexOpenOrd:
		for (int OrdIdToRemove : removeFindexOpenOrd) indexOpenOrd.erase(OrdIdToRemove);

		//update the openOrdersByPrice if any order got filled:
		if (updatebyprice) updateOpenOrdersByPrice();

//	 cout << "\nChecking fills. Open orders: " << indexOpenOrd.size() << " Closed orders: " << indexClosedOrd.size() << " Checking fills took : " << timer.elapsed() << endl;




	}

	void OrderbookPrototype::updateOpenOrdersByPrice()
	{
		//this is how this works. the updateOpenOrdersByPriceIndex stores prices at which there have ever
		//been any open orders. at first pass, it erases every entry in the openOrdersByPrice vector
		//with a price stored in the index. Then, it goes through all of the open orders stored in
		//the openOrderBook vector and updates entries in the openOrdersByPrice vector.
		//finally, after this is done, it goes through all of the index and checks if any of the
		//openOrdersByPrice entries corresponding to the prices stored in the index have been zeroed
		//out. if they have been zeroed out it means there are no longer any open orders corresponding
		//to that price. it then removes that price which no longer holds any open orders from the index

		//index for storing prices to iterate through:
		updateOpenOrdersByPriceIndex;
		using namespace std;
		Timer timer;
		timer.reset();




		//erase all entries in openOrdersByPrice for prices stored in the index	
		////failed attemt to iterate only through non-empty OpenOrdersByPrice
		////can come back to this later if this function proves to be too slow
		////now, just erase EVERYTHING every time and start from filling up from scratch
		//if (indexToErase.size()) {
		//	for (long price : indexToErase )
		//	{
		//		std::cout << " cued for erase: " << price << std::endl;
		//		//below for testing:
		//		cout << openOrdersByPrice.at(price).price << endl;
		////		cout << openOrdersByPrice.at(price).buyLimitAmount << endl;
		//		//THE FOLLOWING LINE OF CODE CRASHES. WILL COMPILE BUT CRASHES:
		//		//COMMENT OUT TO MAKE IT WORK
		//		//WHY?!?!?!?!?
		////		openOrdersByPrice.at(price).eraseall();
		//	}
		//}

		if (updateOpenOrdersByPriceIndex.size()) {
			for (long price : updateOpenOrdersByPriceIndex)
			{

				openOrdersByPrice.at(price).eraseall();
			}
		}

		//go through all the open orders in openOrderBook and update entries in OpenOrdersByPrice
		for (int OrderId : indexOpenOrd)
		{
			MikeOrder order = allOrders.at(OrderId);
			//update entries in openOrdersByPrice:
			switch (order.ordertype)
			{
			case BUYLMT:
				openOrdersByPrice.at(order.price).buyLimitAmount += order.amount;
				break;
			case BUYSTP:
				openOrdersByPrice.at(order.price).buyStopAmount += order.amount;
				break;
			case SELLLMT:
				openOrdersByPrice.at(order.price).sellLimitAmount += order.amount;
				break;
			case SELLSTP:
				openOrdersByPrice.at(order.price).sellStopAmount += order.amount;
				break;
			default:
				std::cout << " ERROR in MikePositionOrders::updateOpenOrdersByPrice()" << std::endl;
				break;
			}

			//update the index with the price:
			updateOpenOrdersByPriceIndex.insert(order.price);
		}

		//			cout << "Filling OrdersByPrice took: " << timer.elapsed() << endl;


		////THE BELOW WILL CRASH TOO:
		////remove empty entries from index:
		//if (index.size()) {
		//	for (long price : index)
		//	{
		//		if (openOrdersByPrice.at(price).checkifempty()) { indexToErase.insert(price); }
		//	}
		//}

	}

	void OrderbookPrototype::fill(int assignedtopos, int fillprice, int orderamount, long bidPrice, long askPrice)
	{
		mypositionorders->fillposition(assignedtopos, fillprice, orderamount, bidPrice, askPrice);
	//	std::cout << "\nImplement filling orders!!!" << std::endl;
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

	

