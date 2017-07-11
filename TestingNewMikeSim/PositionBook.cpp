#include <time.h> //for clock_t, clock, CLOCKS_PER_SEC
#include <vector>
#include <string>
#include <set>
#include <unordered_set>


#include "MikeOrderbook.h"
#include "MikeEnums.h"
#include "MikeTimer.h"
#include "MikePositionsOrders.h"

#include <iostream>
#include "PositionBook.h"



#define COMMENTSOFF //
//using namespace std;

PositionBook::PositionBook(long highestPrice)
{
	
	//positionBook is a vector of MikePosition classes that stores all positions
	positionBook.clear();
	

	//create a vector that is big enough to fit all the prices
	//eg price of 234.73 will be stored in
	//positionBook[23473]

	//how big is the positionBook? This is defined by PositionBookmaxPrice

	PositionBookmaxPrice = highestPrice;
	//create the postionbook:
	positionBook.resize(PositionBookmaxPrice + 1);
	
	//initialize with prices:
	for (long i = 0; i <= PositionBookmaxPrice; ++i)
	{
		positionBook[i].price = i;
	}

	//clear the open positions index

	openPosIndexSet.clear();

}


PositionBook::~PositionBook()
{
}

MikePosition PositionBook::getPosition(long priceRequested)
{
	MikePosition returnPosition = positionBook[priceRequested];
	return returnPosition;
}

const MikePosition * PositionBook::getPositionPtr(long priceRequested)
{
	MikePosition * PositionPtr = &positionBook[priceRequested];
	return PositionPtr;
}

void PositionBook::fillposition(int posprice, long fillprice, long filledamount, long bidPrice, long askPrice)
{
	//manipulate position:
	//fill the position:
	positionBook.at(posprice).fill(fillprice, filledamount);
	//TODO: change structure of code so that individual P/L can be calculated at a different time
	//calculate the P/L for the position:
	positionBook.at(posprice).calculatePL(bidPrice, askPrice);
	//see if it is still active:
	checkIfStillActive(posprice);


	//NOT IMPLEMENTED YET. FILLS HANDLED BY CALLING INDIVIDUAL MikePosition elements inside the orderbook vector
	std::cout << "NOT FULLY IMPLEMENTED YET. TESTING. FILLS HANDLED BY CALLING INDIVIDUAL MikePosition elements inside the orderbook vector" << std::endl;
}








































































































//TODO: STATIC VARIABLES HERE!!!!

long PositionBook::CalcAllOpenPL(long bidprice, long askprice)
{
	using namespace std;
	static long prevbidprice = 0;
	static long prevaskprice = 0; //for speed - to calculate only if bid or ask price has changed
	static long allOpenPL = 0;

	//first - check if bid or ask price has changed:
	if (bidprice != prevbidprice || askprice != prevaskprice)
	{
		allOpenPL = 0;//allOpenPL is static!
		
		//go through every position in the openPosIndex and calculate each individual position's openPL:
		for (long price : openPosIndexSet)
		{
			positionBook.at(price).calculatePL(bidprice, askprice);
			allOpenPL = allOpenPL + positionBook.at(price).open_pl;
		}
		prevaskprice = askprice;
		prevbidprice = bidprice;
	}

	// cout << "allOpenPL = " << allOpenPL << endl;
	return allOpenPL;
	
}

long PositionBook::CalcAllClosedPL(long bidprice, long askprice)
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

long PositionBook::CalcAllTotalPL(long bidprice, long askprice)
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
			allTotalPL = allTotalPL + positionBook.at(price).total_pl;
		}

		////update previous bid/ask prices for future checks:
		prevbidprice = bidprice;
		prevaskprice = askprice;
	}

	return allTotalPL;
}

long PositionBook::CalcTotalOpenPos()
{
	long totalOpenPosition = 0;
	//go through every position in the openPosIndex and add up all the open_amount values:
	for (long price : openPosIndexSet)
	{
		totalOpenPosition = totalOpenPosition + positionBook.at(price).open_amount;
	}

	return totalOpenPosition;
}

void PositionBook::calculateIndividualPLs(long bidprice, long askprice)
{
	for (long price : openPosIndexSet)
	{
		positionBook.at(price).calculatePL(bidprice, askprice);
	}
}

void PositionBook::printoutActivePositions(long bidprice, long askprice)
{
	using namespace std;
	//	if (openPosIndex.size() == 0)	cout << "\nNo active positions." << endl;
	if (openPosIndexSet.size() == 0)	cout << "\nNo active positions." << endl;

	//	Mike::Timer timer;

	Timer timer;
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

	cout << "All Open PL: " << CalcAllOpenPL(bidprice, askprice) << " All Closed PL: " << CalcAllClosedPL(bidprice, askprice)
		<< " All Total PL: " << CalcAllTotalPL(bidprice, askprice) << endl;

	//we have changed some positions by calling the calculatePL method.
	//so now, lets update the index in case some positions where completely zeroed out:
	//	for (unsigned int i = 0; i < openPosIndex.size(); i++)
	for (long price : openPosIndexSet)
	{
		checkIfStillActive(price);
	}


	cout << "Printing positions took : " << timer.elapsed() << endl;

}

bool PositionBook::checkIfStillActive(long price)
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
		positionBook.at(price).setInactive();

		return false;
	}
	else
	{
		addPosToIndex(price);
		positionBook.at(price).setActive();
		return true;
	}

	////UNCOMMENT ABOVE WHEN FINISHED ADDING NEEDED FUNTIONS. ERASE BELOW:
	//return true;

}

void PositionBook::addPosToIndex(long price)
{
	openPosIndexSet.insert(price);
}

void PositionBook::remPosFromIndex(long price)
{
	//remove the price from the index:
	openPosIndexSet.erase(price);
}
