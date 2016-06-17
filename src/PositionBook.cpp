#include "PositionBook.h"

//create a <vector> containg all the MikePositions
//with an index to keep track which positions are active
//and which empty and never used - for quick access
//
PositionBook::PositionBook(std::string name, long highestPrice)
{
	positionBook.clear();
	nameOfBook = name;

	//create a vector that is big enough to fit all the prices
	//eg price of 234.73 will be stored in
	//positionBook[23473]
	
	
	positionBook.resize(highestPrice + 1);
	for (long i = 0; i <= highestPrice; ++i)
	{
		positionBook[i].price = i;
	}

}

MikePosition PositionBook::getPosition(long priceRequested)
{
	MikePosition returnPosition;

	positionBook[priceRequested].isActive = true;
	returnPosition = positionBook[priceRequested];



	return returnPosition;
}

MikePosition::MikePosition()
{
	price = 0;
	open_amount = 0;
	open_pl = 0;
	closed_pl = 0;
	total_pl = 0;
}
