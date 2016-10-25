#include <time.h> //for clock_t, clock, CLOCKS_PER_SEC

#include <vector>
#include <string>
#include <set>
#include <unordered_set>

#include "MikePositionsOrders.h"
#include <iostream>

#include "MikeTimer.h"
#include "OrderbookPrototype.h"

#include "PositionBook.h"



MikePositionOrders::MikePositionOrders(std::string name, long highestPrice)
{
//initialize positionbook - the class that stores all positions. How big is the positionBook? This is defined by PositionBookmaxPrice:
	positionbook = new PositionBook(highestPrice);
	
//initialize orderbook with a pointer to this MikePositionOrders:
	orderbook = new OrderbookPrototype(this, highestPrice);
//name this MikePositionOrders:
	nameOfBook = name;

	//BELOW TEMPORARY FIX FOR REFACTORING:
	refactoringPositionvector.resize(highestPrice + 1);
	refactorOrdersBP.resize(highestPrice + 1);

}

MikePositionOrders::~MikePositionOrders()
{
	delete positionbook;
	positionbook = NULL;
	delete orderbook;
	orderbook = NULL;
}

void MikePositionOrders::newOrder(MikeOrderType type, long orderPrice, long orderAmount)
{
	orderbook->neworder( type, orderPrice, orderAmount);	
}

void MikePositionOrders::checkFills(long bidPrice, long askPrice)
{
	orderbook->checkfills(bidPrice, askPrice);
}

const std::vector<MikePosition>* MikePositionOrders::GetMikePositions()
{
	return positionbook->GetMikePositions();
//	return nullptr;
}

void MikePositionOrders::fillposition(int posprice, long fillprice, long filledamount, long bidPrice, long askPrice)
{
	positionbook->fillposition( posprice, fillprice, filledamount, bidPrice, askPrice);
}

long MikePositionOrders::CalcAllOpenPL(long bidprice, long askprice)
{

	//using namespace std;
	//static long prevbidprice = 0;
	//static long prevaskprice = 0; //for speed - to calculate only if bid or ask price has changed
	//static long allOpenPL = 0;
	////first - check if bid or ask price has changed:
	//if (bidprice != prevbidprice || askprice != prevaskprice)
	//{
	//	allOpenPL = 0;//allOpenPL is static!
	//	cout << "CalcAllOpenPL called" << endl;
	//	//go through every position in the openPosIndex and calculate each individual position's openPL:
	//	for (long price : openPosIndexSet)
	//	{
	//		positionBook.at(price).calculatePL(bidprice, askprice);
	//		allOpenPL = allOpenPL + positionBook.at(price).open_pl;
	//	}
	//	prevaskprice = askprice;
	//	prevbidprice = bidprice;
	//}

	//cout << "allOpenPL = " << allOpenPL << endl;


	//return allOpenPL;

	return positionbook->CalcAllOpenPL(bidprice, askprice);
}

long MikePositionOrders::CalcAllClosedPL(long bidprice, long askprice)
{
	//static long prevbidprice = 0;
	//static long prevaskprice = 0; //for speed - to calculate only if bid or ask price has changed
	//static long allClosedPL = 0;

	////first - check if bid or ask price has changed:
	//if (bidprice != prevbidprice || askprice != prevaskprice)
	//{
	//	allClosedPL = 0;//allClosedPL is static!

	//				  //go through every position in the openPosIndex and calculate each individual position's openPL:
	//	for (long price : openPosIndexSet)
	//	{
	//		positionBook.at(price).calculatePL(bidprice, askprice);
	//		allClosedPL = allClosedPL + positionBook.at(price).closed_pl;
	//	}
	//	prevaskprice = askprice;
	//	prevbidprice = bidprice;
	//}

	//return allClosedPL;
	return positionbook->CalcAllClosedPL(bidprice, askprice);
}

long MikePositionOrders::CalcAllTotalPL(long bidprice, long askprice)
{
	//static long prevbidprice = 0;
	//static long prevaskprice = 0; //for speed - to calculate only if bid or ask price has changed
	//static long allTotalPL = 0;

	////first - check if bid or ask price has changed:
	//if (bidprice != prevbidprice || askprice != prevaskprice)
	//{
	//	allTotalPL = 0;//allTotalPL is static!

	//	//go through every position in the openPosIndex and calculate each individual position's openPL:
	//	for (long price : openPosIndexSet)
	//	{
	//		positionBook.at(price).calculatePL(bidprice, askprice);
	//		allTotalPL = allTotalPL + positionBook.at(price).total_pl ;
	//	}

	//	////update previous bid/ask prices for future checks:
	//	prevbidprice = bidprice;
	//	prevaskprice = askprice;
	//}

	//return allTotalPL;

	return positionbook->CalcAllTotalPL(bidprice,askprice);
}

long MikePositionOrders::CalcTotalOpenPos()
{
	//
	//long totalOpenPosition = 0; 
	////go through every position in the openPosIndex and add up all the open_amount values:
	//for (long price : openPosIndexSet)
	//{
	//	totalOpenPosition = totalOpenPosition + positionBook.at(price).open_amount;
	//}
	//
	//return totalOpenPosition ;

	return positionbook->CalcTotalOpenPos();
}

void MikePositionOrders::calculateIndividualPLs(long bidprice, long askprice)
{
	//for (long price : openPosIndexSet)
	//{
	//	positionBook.at(price).calculatePL(bidprice, askprice);
	//}
}

void MikePositionOrders::updateOpenOrdersByPrice()
{
	orderbook->updateOpenOrdersByPrice();
}





bool MikeOrdersAtPrice::checkifempty()
{
		if (buyLimitAmount == 0 && buyStopAmount == 0 && sellLimitAmount == 0 && sellStopAmount == 0)
			return true;
		else
			return false;
}

//this for testing purposes only.
void MikePositionOrders::printoutAllOrders()
{
	//using namespace std;
	//cout << "Print orders button pressed. " << endl;
	//MikeOrder temp;
	//for (unsigned int i = 0; i < openOrderBook.size(); ++i)
	//{
	//	temp = openOrderBook[i];
	//	cout << "Order ID: " << temp.orderId << " Order type: " 
	//		<< temp.ordertype << " Order Price: " << temp.price 
	//		<< " Amount: " << temp.amount << endl;
	//}
}

const std::vector<MikeOrdersAtPrice>* MikePositionOrders::GetOpOrdersbyPrice()
{
	return orderbook->GetOpOrdersbyPrice();
//	return &orderbook->openOrdersByPrice;   /*return &refactorOrdersBP;*/ /*return &openOrdersByPrice;*/
	
}


void MikePositionOrders::printoutActivePositions(long bidprice, long askprice)
{
	//	using namespace std;
	////	if (openPosIndex.size() == 0)	cout << "\nNo active positions." << endl;
	//	if (openPosIndexSet.size() == 0)	cout << "\nNo active positions." << endl;
	//
	////	Mike::Timer timer;
	//
	//	timer.reset();
	//
	//	/*
	//	Go through all active positions and print them out.
	//	To do this, I require an index that stores only active positions so that I do not need to
	//	iterate through 1000000 positions every time
	//	*/
	//
	////	for (unsigned int i = 0; i < openPosIndex.size(); ++i)
	//	
	//	for (long price : openPosIndexSet)
	//	{
	//
	//		positionBook.at(price).calculatePL(bidprice, askprice);
	//		
	//		//openPosIndex stores the PRICES which have active positions
	//		MikePosition temp = positionBook.at(price);
	//		
	//		cout << 
	//			" Pos price: " << temp.price << 
	//			" size: " << temp.open_amount <<
	//			" Closed PL: " << temp.closed_pl <<
	//			" Open PL: " << temp.open_pl <<
	//			" Total PL: " << temp.total_pl			
	//			<< endl;
	//	}
	//
	//	cout << "All Open PL: " << CalcAllOpenPL(bidprice, askprice) << " All Closed PL: " << CalcAllClosedPL(bidprice, askprice)
	//		<< " All Total PL: " << CalcAllTotalPL(bidprice, askprice) << endl;
	//
	//	//we have changed some positions by calling the calculatePL method.
	//	//so now, lets update the index in case some positions where completely zeroed out:
	////	for (unsigned int i = 0; i < openPosIndex.size(); i++)
	//		for (long price : openPosIndexSet)
	//	{
	//		checkIfStillActive(price);
	//	}
	//
	//
	//	cout << "Printing positions took : " << timer.elapsed() << endl;

}

void MikeOrdersAtPrice::eraseall()
{
	buyLimitAmount = 0;
	buyStopAmount = 0;
	sellLimitAmount = 0;
	sellStopAmount = 0;
}
