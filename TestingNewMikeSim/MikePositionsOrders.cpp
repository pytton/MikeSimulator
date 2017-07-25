#include <time.h> //for clock_t, clock, CLOCKS_PER_SEC

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <stack>

#include "MikePositionsOrders.h"
#include <iostream>

#include "MikeTimer.h"
#include "MikeOrderbook.h"

#include "PositionBook.h"



MikePositionOrders::MikePositionOrders(std::string name, long highestPrice)
{
//initialize positionbook - the class that stores all positions. How big is the positionBook? This is defined by PositionBookmaxPrice:
	positionbook = new PositionBook(highestPrice);
	
//initialize orderbook with a pointer to this MikePositionOrders:
	orderbook = new MikeOrderbook(this , highestPrice);
//name this MikePositionOrders:
	nameOfBook = name;

	//BELOW TEMPORARY FIX FOR REFACTORING:
//	refactoringPositionvector.resize(highestPrice + 1);
//	refactorOrdersBP.resize(highestPrice + 1);

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
}

void MikePositionOrders::fillposition(int posprice, long fillprice, long filledamount, long bidPrice, long askPrice)
{
	positionbook->fillposition( posprice, fillprice, filledamount, bidPrice, askPrice);
}

long MikePositionOrders::CalcAllOpenPL(long bidprice, long askprice)
{
	return positionbook->CalcAllOpenPL(bidprice, askprice);
}

long MikePositionOrders::CalcAllClosedPL(long bidprice, long askprice)
{
	return positionbook->CalcAllClosedPL(bidprice, askprice);
}

long MikePositionOrders::CalcAllTotalPL(long bidprice, long askprice)
{
	return positionbook->CalcAllTotalPL(bidprice,askprice);
}

long MikePositionOrders::CalcTotalOpenPos()
{
	return positionbook->CalcTotalOpenPos();
}

double MikePositionOrders::CalcAvgPos()
{
	return positionbook->CalcAvgPos();
}

void MikePositionOrders::calculateIndividualPLs(long bidprice, long askprice)
{
}

void MikePositionOrders::clearAllPositions()
{
	positionbook->clearAllPositions();
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

}

void MikePositionOrders::cancelOrder(long orderId)
{
	using namespace std;
	cout << "Not implemented. Cancel orderId: " << orderId << endl;
}

void MikePositionOrders::cancelAllOrdAtPrice(long price)
{
	using namespace std;
	cout << "Print from MikePositionOrders: testing. Cancelling all orders at price: " << price << endl;

	// first, find all orders with the price supplied; add these orders to the stack
	std::stack<long> ordersToCancel;
	//iterate through all orders in orderbook that have an orderID that was stored in the open orders index:
	for (auto OrderIDToCancel = orderbook->indexOpenOrd.begin(); OrderIDToCancel != orderbook->indexOpenOrd.end(); OrderIDToCancel++) {
		//if any of the open orders has a price matching the price we want to cancel, add it to the stack of orders we want to cancel:
		if (orderbook->allOrders.at(*OrderIDToCancel).price == price) {
			ordersToCancel.push(*OrderIDToCancel);
		}
	}

	//go through the stack and erase all the orders:
	while (ordersToCancel.size() > 0) {
		long cancelThis = ordersToCancel.top();
		orderbook->cancelorder(cancelThis);
		ordersToCancel.pop();
	}
	//we erased some orders, so now update open orders by price in orderbook:
	orderbook->updateOpenOrdersByPrice();

}

void MikePositionOrders::cancelAllOpenOrders()
{
	orderbook->cancelAllOpenOrders();
}

const std::vector<MikeOrdersAtPrice>* MikePositionOrders::GetOpOrdersbyPrice()
{
	return orderbook->GetOpOrdersbyPrice();	
}


void MikePositionOrders::printoutActivePositions(long bidprice, long askprice)
{
	
}

void MikeOrdersAtPrice::eraseall()
{
	buyLimitAmount = 0;
	buyStopAmount = 0;
	sellLimitAmount = 0;
	sellStopAmount = 0;
}
