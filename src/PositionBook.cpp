#include "PositionBook.h"

PositionBook::PositionBook(std::string name, long startprice, long endprice)
{
	positionBook.clear();
	//MikePosition temp;
	//temp.open_amount = 0;
	nameOfBook = name;

	if (startprice < 0) startprice = 0;
	if (endprice < startprice) endprice = startprice;
	positionBook.resize(endprice - startprice + 1);


}

MikePosition PositionBook::getPosition(long priceRequested)
{
	MikePosition returnPosition;

	for (long i = 0; i < positionBook.size(); ++i)
	{
		if (positionBook[i].price = priceRequested)
		{
			returnPosition = positionBook[i];
		}


	}



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
