#include "MikePositionsOrders.h"
#include <iostream>

MikePositionOrders::MikePositionOrders(std::string name, long highestPrice)
{
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

	positionBook.resize(PositionBookmaxPrice + 1);
	for (long i = 0; i <= PositionBookmaxPrice; ++i)
	{
		positionBook[i].price = i;
	}

	//clear the open positions index
	openPosIndex.clear();

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

	cout << "new order received. Type: " << /*tempOrderType<<*/ " " << type << " Price: " <<
		orderPrice << " Size: " << orderAmount << " Order ID: " << newOrderId << endl;

	MikeOrder tempOrder;

	tempOrder.orderId = newOrderId;
	tempOrder.ordertype = type;
	tempOrder.assignedToPosition = orderPrice;
	tempOrder.price = orderPrice;
	tempOrder.amount = orderAmount;
	tempOrder.isFilled = false;

	openOrderBook.push_back(tempOrder);

}

void MikePositionOrders::checkFills(long bidPrice, long askPrice)
{
	using namespace std;
	//WORK IN PROGRESS BELOW:
	//Go through all open orders and check for fills.

	timer1 = clock();
	timer2 = clock();//time this operation

	cout << "\nChecking fills. openOrderBook.size(): " << openOrderBook.size() << endl;	
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

					cout << " Order ID: " << order.orderId << " Filled at price: " << askPrice << endl;
				}

			}
			if (order.ordertype == SELLLMT)
			{	//if bid price is above SELL LIMIT ORDER price, fill it at bid price 
				//and move the order from openOrderBook to closedOrderBook
				if (order.price <= bidPrice)
				{
					//fill the position:
					positionBook.at(order.assignedToPosition).fill(askPrice, (order.amount) * -1);
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


	timer2 = clock();
	cout << "Checking fills took : " << ((timer2 - timer1) /*/ CLOCKS_PER_SEC*/) << endl;
}

void MikePositionOrders::printoutAllOrders()
{
	using namespace std;
	cout << "Print orders button pressed - implement this!!!!" << endl;
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
	if (openPosIndex.size() == 0)	cout << "\nNo active positions." << endl;
	
	timer1 = clock();
	timer2 = clock();//time this operation
	/*
	Go through all active positions and print them out.
	To do this, I require an index that stores only active positions so that I do not need to
	iterate through 1000000 positions every time
	*/

	for (unsigned int i = 0; i < openPosIndex.size(); ++i)
	{
		positionBook.at(openPosIndex.at(i)).calculatePL(bidprice, askprice);
		//openPosIndex stores the PRICES which have active positions
		MikePosition temp = positionBook.at(openPosIndex.at(i));
		
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
	for (unsigned int i = 0; i < openPosIndex.size(); i++)
	{
		checkIfStillActive(openPosIndex.at(i));
	}

	timer2 = clock();
	cout << "Printing positions took : " << ((timer2 - timer1) /*/ CLOCKS_PER_SEC*/) 
		<< "Clocks per sec: " << CLOCKS_PER_SEC << endl;

}


MikePosition MikePositionOrders::getPosition(long priceRequested)
{
	MikePosition returnPosition;


	returnPosition = positionBook[priceRequested];



	return returnPosition;
}

bool MikePositionOrders::changePostion(long price, long amount)
{
	//change the open_amount by amount:
	long temp = positionBook.at(price).open_amount;
	positionBook.at(price).open_amount = temp + amount;

	//update the active positions index:
	checkIfStillActive(price);


	return true;
}

long MikePositionOrders::AllOpenPL(long bidprice, long askprice)
{
	static long prevbidprice = 0;
	static long prevaskprice = 0; //for speed - to calculate only if bid or ask price has changed
	static long allOpenPL = 0;

	//first - check if bid or ask price has changed:
	if (bidprice != prevbidprice || askprice != prevaskprice)
	{
		allOpenPL = 0;//allOpenPL is static!

		//go through every position in the openPosIndex and calculate each individual position's openPL:
		for (long price : openPosIndex)
		{
			positionBook.at(price).calculatePL(bidprice, askprice);
			allOpenPL = allOpenPL + positionBook.at(price).open_pl;
		}
	}



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
		for (long price : openPosIndex)
		{
			positionBook.at(price).calculatePL(bidprice, askprice);
			allClosedPL = allClosedPL + positionBook.at(price).closed_pl;
		}
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
		for (long price : openPosIndex)
		{
			positionBook.at(price).calculatePL(bidprice, askprice);
			allTotalPL = allTotalPL + positionBook.at(price).total_pl ;
		}
	}

	return allTotalPL;
}

long MikePositionOrders::TotalOpenPos()
{
	
	long totalOpenPosition = 0; 
	//go through every position in the openPosIndex and add up all the open_amount values:
	for (long price : openPosIndex)
	{
		totalOpenPosition = totalOpenPosition + positionBook.at(price).open_amount;
	}
	
	return totalOpenPosition ;
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

	//first, check if position is already in the index:
	for (unsigned int i = 0; i < openPosIndex.size(); ++i)
	{
		if (openPosIndex.at(i) == price)
		{
			//if it is in the index, no need to add that same price again
			return;
		}
	}

	
		//if it is not, add it to the index
		openPosIndex.push_back(price);
		cout << "\nPosition at price: " << price << " added to active positions index!! " << endl;
	

}

void MikePositionOrders::remPosFromIndex(long price)
{
	using namespace std;
	//find the position in the index:
	for (unsigned int i = 0; i < openPosIndex.size(); ++i)
	{
		if (openPosIndex.at(i) == price)
		{
			openPosIndex.erase(openPosIndex.begin()+i);
			cout << "\nPosition at price: " << price << " removed from active positions index!! " << endl;
			return;
		}
		else
		{
			cout << "\nPosition at price: " << price << " not found in active positions index!! " << endl;
		}
	}
}


long MikePositionOrders::generateID()
{
	static long s_itemID = 0;
	return s_itemID++;
}