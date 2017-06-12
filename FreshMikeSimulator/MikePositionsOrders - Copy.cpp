#include "MikePositionsOrders.h"
#include <iostream>

#include "MikeTimer.h"

MikePositionOrders::MikePositionOrders(std::string name, long highestPrice)
{
	orderbook = new Mike::OrderbookPrototype(this);
		

//positionBook is a vector of MikePosition classes that stores all positions
	positionBook.clear();
	nameOfBook = name;

	//create a vector that is big enough to fit all the prices
	//eg price of 234.73 will be stored in
	//positionBook[23473]

	//TODO: create an indexs to store only open positions
	//so that there is no need to iterate through tens of thousands
	//of positions

	//how big is the positionBook? This is defined by PositionBookmaxPrice
	 
	PositionBookmaxPrice = highestPrice;
	//create the postionbook:
	positionBook.resize(PositionBookmaxPrice + 1);
	//create the openOrdersByPrice index:
	openOrdersByPrice.resize(PositionBookmaxPrice + 1);
	//initialize both with prices:
	for (long i = 0; i <= PositionBookmaxPrice; ++i)
	{
		positionBook[i].price = i;
		openOrdersByPrice[i].price = i;
	}

	//clear the open positions index
//	openPosIndex.clear();
	openPosIndexSet.clear();

	using namespace std;
	//openOrderBook is a ector of Mikeorder classes that stores all open orders
	openOrderBook.clear();
	//this stores all the filled orders
	closedOrderBook.clear();
	cout << endl << "OrderBook created." << endl;
}

MikePositionOrders::~MikePositionOrders()
{
}

void MikePositionOrders::newOrder(MikeOrderType type, long orderPrice, long orderAmount)
{
	using namespace std;
	long newOrderId = generateID();
	string tempOrderType;
	//if (type == BUYLMT) tempOrderType = "Buy Limit";

	switch (type)
	{
	case CXLORDER:
		tempOrderType = "CANCEL";
		break;
	case BUYLMT:
		tempOrderType = "BUY LIMIT";
		break;
	case BUYSTP:
		tempOrderType = "BUY STOP";
		break;
	case SELLLMT:
		tempOrderType = "SELL LIMIT";
		break;
	case SELLSTP:
		tempOrderType = "SELL STOP";
		break;
	default:
		break;
	}

	cout << "new order received. Type: " << tempOrderType << " Price: " <<
		orderPrice << " Size: " << orderAmount << " Order ID: " << newOrderId << endl;

	MikeOrder tempOrder;

	tempOrder.orderId = newOrderId;
	tempOrder.ordertype = type;
	tempOrder.assignedToPosition = orderPrice;
	tempOrder.price = orderPrice;
	tempOrder.amount = orderAmount;
	tempOrder.isFilled = false;

	openOrderBook.push_back(tempOrder);

	//EXPERIMENTING by calling newOrder inside OrderBookPrototype class:

	orderbook->neworder(type, orderPrice, orderAmount);
	
}

void MikePositionOrders::checkFills(long bidPrice, long askPrice)
{
	using namespace std;
	//WORK IN PROGRESS BELOW:
	//Go through all open orders and check for fills.

	//Mike::Timer timer;
	timer.reset();


		
	for (unsigned int i = 0; i < openOrderBook.size(); i++)
	{
		MikeOrder order;
		//MikeOrder * ptr_order = &openOrderBook.at(i);
		order = openOrderBook.at(i);

		
		if (openOrderBook.at(i).isFilled == false)
		{
			//check buy limit orders only for now. do rest later:
			if (order.ordertype == BUYLMT)
			{	//if ask price is below BUY LIMIT ORDER price, fill it at ask price 
				//and move the order from openOrderBook to closedOrderBook
				if (order.price >= askPrice)
				{
					//fill the position:
					positionBook.at(order.assignedToPosition).fill(askPrice, order.amount);
					//calculate the P/L for the position:
					positionBook.at(order.assignedToPosition).calculatePL(bidPrice, askPrice);
					//see if it is still active:
					checkIfStillActive(order.assignedToPosition);
					//mark order as filled in openOrderBook:
					openOrderBook.at(i).isFilled = true;
					//copy the order to closedOrderBook:
					closedOrderBook.push_back(order);

					//TODO: update the openOrdersByPrice vector!!!!

					cout << " Order ID: " << order.orderId << " Filled at price: " << askPrice << endl;
				}

			}
			if (order.ordertype == SELLLMT)
			{	//if bid price is above SELL LIMIT ORDER price, fill it at bid price 
				//and move the order from openOrderBook to closedOrderBook
				if (order.price <= bidPrice)
				{
					//fill the position:
					positionBook.at(order.assignedToPosition).fill(bidPrice, (order.amount) * -1);
					//calculate the P/L for the position:
					positionBook.at(order.assignedToPosition).calculatePL(bidPrice, askPrice);
					//see if it is still active:
					checkIfStillActive(order.assignedToPosition);
					//mark order as filled in openOrderBook:
					openOrderBook.at(i).isFilled = true;
					//copy the order to closedOrderBook:
					closedOrderBook.push_back(order);

					cout << " Order ID: " << order.orderId << " Filled at price: " << bidPrice << endl;
				}

			}
			if (order.ordertype == BUYSTP)
			{	//if ask price is above BUY STOP ORDER price, fill it at ask price
				//and move the order from openOrderBook to closedOrderBook
				if (order.price <= askPrice)
				{
					//fill the position:
					positionBook.at(order.assignedToPosition).fill(askPrice, order.amount);
					//calculate the P/L for the position:
					positionBook.at(order.assignedToPosition).calculatePL(bidPrice, askPrice);
					//see if it is still active:
					checkIfStillActive(order.assignedToPosition);
					//mark order as filled in openOrderBook:
					openOrderBook.at(i).isFilled = true;
					//copy the order to closedOrderBook:
					closedOrderBook.push_back(order);

					cout << " Order ID: " << order.orderId << " Filled at price: " << askPrice << endl;
				}

			}
			if (order.ordertype == SELLSTP)
			{	//if bid price is below SELL STOP ORDER price, fill it at bid price 
				//and move the order from openOrderBook to closedOrderBook
				if (order.price >= askPrice)
				{
					//fill the position:
					positionBook.at(order.assignedToPosition).fill(bidPrice, (order.amount) * -1);
					//calculate the P/L for the position:
					positionBook.at(order.assignedToPosition).calculatePL(bidPrice, askPrice);
					//see if it is still active:
					checkIfStillActive(order.assignedToPosition);
					//mark order as filled in openOrderBook:
					openOrderBook.at(i).isFilled = true;
					//copy the order to closedOrderBook:
					closedOrderBook.push_back(order);

					cout << " Order ID: " << order.orderId << " Filled at price: " << bidPrice << endl;
				}

			}

		}

	}

	//erase all filled orders from openOrderBook:

	for (unsigned int i = 0; i < openOrderBook.size();)
	{
		if (openOrderBook.at(i).isFilled == true)
		{
			openOrderBook.erase(openOrderBook.begin() + i);
			i = 0;
			continue;
		}
		i++;
	}
	cout << "\nChecking fills. Open orders: " << openOrderBook.size() << 
		" Closed orders: " << closedOrderBook.size() << 
		" Checking fills took : " << timer.elapsed() << endl;
}

//this for testing purposes only.
void MikePositionOrders::printoutAllOrders()
{
	using namespace std;
	cout << "Print orders button pressed. " << endl;
	MikeOrder temp;
	for (unsigned int i = 0; i < openOrderBook.size(); ++i)
	{
		temp = openOrderBook[i];
		cout << "Order ID: " << temp.orderId << " Order type: " 
			<< temp.ordertype << " Order Price: " << temp.price 
			<< " Amount: " << temp.amount << endl;
	}
}


void MikePositionOrders::printoutActivePositions(long bidprice, long askprice)
{
	using namespace std;
//	if (openPosIndex.size() == 0)	cout << "\nNo active positions." << endl;
	if (openPosIndexSet.size() == 0)	cout << "\nNo active positions." << endl;

//	Mike::Timer timer;

	timer.reset();

	/*
	Go through all active positions and print them out.
	To do this, I require an index that stores only active positions so that I do not need to
	iterate through 1000000 positions every time
	*/

//	for (unsigned int i = 0; i < openPosIndex.size(); ++i)
	
	for (long price : openPosIndexSet)
	{

		positionBook.at(price).calculatePL(bidprice, askprice);
		
		//openPosIndex stores the PRICES which have active positions
		MikePosition temp = positionBook.at(price);
		
		cout << 
			" Pos price: " << temp.price << 
			" size: " << temp.open_amount <<
			" Closed PL: " << temp.closed_pl <<
			" Open PL: " << temp.open_pl <<
			" Total PL: " << temp.total_pl			
			<< endl;
	}

	cout << "All Open PL: " << AllOpenPL(bidprice, askprice) << " All Closed PL: " << AllClosedPL(bidprice, askprice)
		<< " All Total PL: " << AllTotalPL(bidprice, askprice) << endl;

	//we have changed some positions by calling the calculatePL method.
	//so now, lets update the index in case some positions where completely zeroed out:
//	for (unsigned int i = 0; i < openPosIndex.size(); i++)
		for (long price : openPosIndexSet)
	{
		checkIfStillActive(price);
	}


	cout << "Printing positions took : " << timer.elapsed() << endl;

}


MikePosition MikePositionOrders::getPosition(long priceRequested)
{
	MikePosition returnPosition;

	returnPosition = positionBook[priceRequested];

	return returnPosition;
}

void MikePositionOrders::fillposition(int posprice, long fillprice, long filledamount)
{

}

//bool MikePositionOrders::changePostion(long price, long amount)
//{
//	//change the open_amount by amount:
//	long temp = positionBook.at(price).open_amount;
//	positionBook.at(price).open_amount = temp + amount;
//
//	//update the active positions index:
//	checkIfStillActive(price);
//
//	return true;
//}

long MikePositionOrders::AllOpenPL(long bidprice, long askprice)
{
	using namespace std;
	static long prevbidprice = 0;
	static long prevaskprice = 0; //for speed - to calculate only if bid or ask price has changed
	static long allOpenPL = 0;

	//first - check if bid or ask price has changed:
	if (bidprice != prevbidprice || askprice != prevaskprice)
	{
		allOpenPL = 0;//allOpenPL is static!
		cout << "AllOpenPL called" << endl;
		//go through every position in the openPosIndex and calculate each individual position's openPL:
		for (long price : openPosIndexSet)
		{
			positionBook.at(price).calculatePL(bidprice, askprice);
			allOpenPL = allOpenPL + positionBook.at(price).open_pl;
		}
		prevaskprice = askprice;
		prevbidprice = bidprice;
	}

	cout << "allOpenPL = " << allOpenPL << endl;


	return allOpenPL;
}

long MikePositionOrders::AllClosedPL(long bidprice, long askprice)
{
	static long prevbidprice = 0;
	static long prevaskprice = 0; //for speed - to calculate only if bid or ask price has changed
	static long allClosedPL = 0;

	//first - check if bid or ask price has changed:
	if (bidprice != prevbidprice || askprice != prevaskprice)
	{
		allClosedPL = 0;//allClosedPL is static!

					  //go through every position in the openPosIndex and calculate each individual position's openPL:
		for (long price : openPosIndexSet)
		{
			positionBook.at(price).calculatePL(bidprice, askprice);
			allClosedPL = allClosedPL + positionBook.at(price).closed_pl;
		}
		prevaskprice = askprice;
		prevbidprice = bidprice;
	}

	return allClosedPL;
}

long MikePositionOrders::AllTotalPL(long bidprice, long askprice)
{
	static long prevbidprice = 0;
	static long prevaskprice = 0; //for speed - to calculate only if bid or ask price has changed
	static long allTotalPL = 0;

	//first - check if bid or ask price has changed:
	if (bidprice != prevbidprice || askprice != prevaskprice)
	{
		allTotalPL = 0;//allTotalPL is static!

		//go through every position in the openPosIndex and calculate each individual position's openPL:
		for (long price : openPosIndexSet)
		{
			positionBook.at(price).calculatePL(bidprice, askprice);
			allTotalPL = allTotalPL + positionBook.at(price).total_pl ;
		}

		////update previous bid/ask prices for future checks:
		prevbidprice = bidprice;
		prevaskprice = askprice;
	}

	return allTotalPL;
}

long MikePositionOrders::TotalOpenPos()
{
	
	long totalOpenPosition = 0; 
	//go through every position in the openPosIndex and add up all the open_amount values:
	for (long price : openPosIndexSet)
	{
		totalOpenPosition = totalOpenPosition + positionBook.at(price).open_amount;
	}
	
	return totalOpenPosition ;
}

void MikePositionOrders::calculateIndividualPLs(long bidprice, long askprice)
{
	for (long price : openPosIndexSet)
	{
		positionBook.at(price).calculatePL(bidprice, askprice);
	}
}

void MikePositionOrders::updateOpenOrdersByPrice()
{
	//this is how this works. the internal static index stores prices at which there have ever
	//been any open orders. at first pass, it erases every entry in the openOrdersByPrice vector
	//with a price stored in the index. Then, it goes through all of the open orders stored in
	//the openOrderBook vector and updates entiries in the openOrdersByPrice vector.
	//finally, after this is done, it goes through all of the index and checks if any of the
	//openOrdersByPrice entries corresponding to the prices stored in the index have been zeroed
	//out. if they have been zeroed out it means there are no longer any open orders corresponding
	//to that price. it then removes that price which no longer holds any open orders from the index

	//index for storing prices to iterate through:
//	static std::vector<long> index;
	using namespace std;
	timer.reset();

	static std::set<long> index;
//	static std::set<long> indexToErase;
//	indexToErase.clear();

//	cout << " Checking problem index " << endl;

//	MikeOrdersAtPrice temp;

	//erase all entries in openOrdersByPrice for prices stored in the index:
	
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

	if (index.size()) {
		for (long price : index)
		{
		//	std::cout << " order index: " << std::endl;

		////	below for testing:
		//	cout << openOrdersByPrice.at(price).price << endl;
		//	cout << openOrdersByPrice.at(price).buyLimitAmount << endl;
		//	cout << openOrdersByPrice.at(price).buyStopAmount << endl;
		//	cout << openOrdersByPrice.at(price).sellLimitAmount << endl;
		//	cout << openOrdersByPrice.at(price).sellStopAmount << endl;
			//THE FOLLOWING LINE OF CODE CRASHES. WILL COMPILE BUT CRASHES:
			//COMMENT OUT TO MAKE IT WORK
			//WHY?!?!?!?!?
					openOrdersByPrice.at(price).eraseall();
		}
	}

	//go through all the open orders in openOrderBook and update entries in OpenOrdersByPrice
	for (MikeOrder order : openOrderBook)
	{
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
		index.insert(order.price);
	}

	cout << "Filling OrdersByPrice took: " << timer.elapsed() << endl;


	////THE BELOW WILL CRASH TOO:
	////remove empty entries from index:
	//if (index.size()) {
	//	for (long price : index)
	//	{
	//		if (openOrdersByPrice.at(price).checkifempty()) { indexToErase.insert(price); }
	//	}
	//}

}

bool MikePositionOrders::checkIfStillActive(long price)
{
	MikePosition posToCheck = positionBook.at(price);

	//check if any members of this position are other than zero
	//if they are - designate the position as active
	//and add to active position index
	//if everything is zero - designate the position as not active
	//and remove from active position index:
	
	if (
		posToCheck.closed_pl == 0 &&
		posToCheck.open_amount == 0 &&
		posToCheck.open_pl == 0 &&
		posToCheck.total_pl == 0
		)
	{
		//then this position is no longer active.
		//let the index know:
		remPosFromIndex(price);
		//and change the 'isActive' flag:
		positionBook.at(price).isActive = false;

		return false;
	}
	else
	{
		addPosToIndex(price);
		return true;
	}

}

void MikePositionOrders::addPosToIndex(long price)
{
	using namespace std;


	openPosIndexSet.insert(price);

	//unordered_set<long>::const_iterator itr = openPosIndexSet.find(price);
	//if (itr != openPosIndexSet.end()) openPosIndexSet.insert(price);
	

	////first, check if position is already in the index:
	//for (unsigned int i = 0; i < openPosIndex.size(); ++i)
	//{
	//	if (openPosIndex.at(i) == price)
	//	{
	//		//if it is in the index, no need to add that same price again
	//		return;
	//	}
	//}

	//
	//	//if it is not, add it to the index
	//	openPosIndex.push_back(price);
	//	cout << "\nPosition at price: " << price << " added to active positions index!! " << endl;
	

}

void MikePositionOrders::remPosFromIndex(long price)
{
	using namespace std;

	//remove the price from the index:
	openPosIndexSet.erase(price);

	////find the position in the index:
	//for (unsigned int i = 0; i < openPosIndex.size(); ++i)
	//{
	//	if (openPosIndex.at(i) == price)
	//	{
	//		openPosIndex.erase(openPosIndex.begin()+i);
	//		cout << "\nPosition at price: " << price << " removed from active positions index!! " << endl;
	//		return;
	//	}
	//	else
	//	{
	//		cout << "\nPosition at price: " << price << " not found in active positions index!! " << endl;
	//	}
	//}
}


long MikePositionOrders::generateID()
{
	static long s_itemID = 0;
	return s_itemID++;
}

void MikeOrdersAtPrice::eraseall()
{
		buyLimitAmount = 0;
		buyStopAmount = 0;
		sellLimitAmount = 0;
		sellStopAmount = 0;
}

bool MikeOrdersAtPrice::checkifempty()
{
		if (buyLimitAmount == 0 && buyStopAmount == 0 && sellLimitAmount == 0 && sellStopAmount == 0)
			return true;
		else
			return false;
}

