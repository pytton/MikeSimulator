#ifndef _POSITIONBOOK_H_INCLUDED_
#define _POSITIONBOOK_H_INCLUDED_

#include <string>
#include <vector>



class MikePosition
{
public:
	long price;
	long open_amount;
	long open_pl;
	long closed_pl;
	long total_pl;


	//this is for indexing purposes - set to TRUE if position was ever
	//accessed or changed. Mainly to avoid iterating through tens of thousands
	//of positions
	bool isActive = false ;

	MikePosition();
};//class MikePosition

class PositionBook
{
	
public:

	PositionBook(std::string name, long highestPrice);

	void newPosition(long price, long position);
	MikePosition getPosition(long price);
	bool clearPosition(long price);
	bool changePostion(long price, long amount);

	//calculates the total open P/L for all active positions
	long calculatedTotalOpenPL();

	//calculates the total closed P/L for all active positions
	long calculatedTotalClosedPL();

	//calculates the total total_pl P/L for all active positions
	long calculateTotalTotalPL();

	//gives the total open position above a certain price level:
	long totalOpenAbove(long price);

	//gives the total open position below a certain price level:
	long totalOpenBelow(long price);

	

private:
	//stores all the positions
	//the vector number reflects the price in cents - eg positionBook[10073]
	//reflects a price of 100 dollars and 73 cents
	std::vector <MikePosition> positionBook;
	std::string nameOfBook;

	long minPrice; //stores the price of the smallest active position - for quicker iterating through all of book
	long maxPrice; //highest active price - for index
	
	//for knowing which postitions are active or not - if I need to access only
	//the 'not empty' positions
	std::vector <long> index;


};











#endif _POSITIONBOOK_H_INCLUDED_