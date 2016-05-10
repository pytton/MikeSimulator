#ifndef _MIKEORDERBOOK_H_INCLUDED_
#define _MIKEORDERBOOK_H_INCLUDED_

/*
	TODO:
Stores all positions
Make it so that multiple OrderBooks can exist - each for one strategy

METHODS:
New Order
Cancel Order

Check fills -> all positions or in a range (prev bid/ask - current bid/ask)
Calculate total P/L Position closed P/L etc
Print in display?
Cancel All Orders? Flatten Position? - do that later


*/

#include "UserInterface.h"
#include <vector>

struct MikePosition
{
	long price;

	int order_type;
	long order_size;
	long order_price;
	double open_pl;
	double closed_pl;
	double total_pl;
};

class MikeOrderBook
{//private:
	std::vector <MikePosition> Orders;

public:
	//constructors:
	MikeOrderBook();	

	void NewOrder();	//adds a new order to the Orderbook
	void CancelOrder();	//cancels order
	void CheckFills();	//check fills -> all positions or in a range (prev bid/ask - current bid/ask)
	void PrintInTable(WidgetTable * table);	//printsout all oreders/positions

	MikePosition position(int price);

	int ReturnPrice(int pos);
	int ReturnSomething();

};




#endif //_MIKEORDERBOOK_H_INCLUDED_
