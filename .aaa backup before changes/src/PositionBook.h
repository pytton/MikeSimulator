#ifndef _POSITIONBOOK_H_INCLUDED_
#define _POSITIONBOOK_H_INCLUDED_


#include <time.h> //for clock_t, clock, CLOCKS_PER_SEC
#include <vector>
#include <string>
#include <set>
#include <unordered_set>

//#include "OrderbookPrototype.h"
//#include "MikeEnums.h"
//#include "MikeTimer.h"
//#include "MikePositionsOrders.h"




class MikeOrder;
class MikeOrdersAtPrice;
class MikePositionOrders;
class MikePosition;


enum BtnPressed;
enum MikeOrderType;

//class Timer;



class PositionBook
{
public:
	PositionBook(long highestPrice);
	~PositionBook();

	//POSITION METHODS:
	//used for printing open positions in WidgetTable
	const std::vector <MikePosition> * GetMikePositions() { return   &positionBook; }
	void newPosition(long price, long position);//not implemented
	MikePosition getPosition(long priceRequested);
	const MikePosition * getPositionPtr(long priceRequested);

	//used by orderbook to update a position after an order is filled. NOT IMPLEMENTED YET
	void fillposition(int posprice, long fillprice, long filledamount);
	
	//Methods below are slow because each one iterates over all open positions in openPosIndexSet individually. So calling AllOpenPL will go through the whole index, and then if you call AllClosedPL it will go through the whole index again. To speed it up, consider making one method to calculate all of them at once at each iteration of accessing the postions pointed to by openPosIndexSet and then supplying all the answers as a struct:
	
	//calculates the total aggregate open P/L for all active positions of the whole book
	long AllOpenPL(long bidprice, long askprice);
	//calculates the total aggregate closed P/L for all active positions of the whole book
	long AllClosedPL(long bidprice, long askprice);
	//calculates the total aggregate total P/L (open+closed) for all active positions of the whole book
	long AllTotalPL(long bidprice, long askprice);
	//calculates the total aggregate position for all active positions of the whole book
	long TotalOpenPos();
	//calculate individual P/L for each position that is stored in the openPosIndex
	//this should be done before attempting to print out the positions
	void calculateIndividualPLs(long bidprice, long askprice);

	//prototype for printing activePositions:
	void printoutActivePositions(long bidprice, long askprice);


private:
	//stores all the positions
	//the vector number reflects the price in cents - eg positionBook[10073]
	//reflects a price of 100 dollars and 73 cents
	std::vector <MikePosition> positionBook;

	///////////////////////////////////////////////////////////
	// INDEX:
	//stores the prices of active postions for knowing which postitions are active or not - if I need to access only the 'not empty' positions.
	std::unordered_set<long> openPosIndexSet;	//trying to implement a faster way
	///////////////////////////////////////////////////////////

	//this is the size of positionBook. used in constructor to determine what is the highest price position that can be stored in positionBook.
	long PositionBookmaxPrice = 1000000;
	
	//check if any members of this position are other than zero if they are - designate the position as active and add to active position index if everything is zero - designate the position as not active and remove from active position index:
	bool checkIfStillActive(long price);
	//add position to active position index:
	void addPosToIndex(long price);
	//remove position from active position index:
	void remPosFromIndex(long price);

	//naming the class to enable having multiple instances of MikePositionOrders
	//for multiple different strategies. This is done during class construction:
//	std::string nameOfBook;

	//simple timer for testing purposes:
	Timer * timer;
};

#endif//_POSITIONBOOK_H_INCLUDED_