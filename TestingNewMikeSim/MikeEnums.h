#ifndef _MIKEENUMS_H_INCLUDED_
#define _MIKEENUMS_H_INCLUDED_


enum MikeOrderType
{
	CXLORDER,
	BUYLMT,
	BUYSTP,
	SELLLMT,
	SELLSTP,
};

//used for callbacks from UserInterface and WidgetTable
//to Control class
enum class BtnPressed
{
	UPBTN,
	DOWNBTN,
	EXTRABTN,
	SLIDER1,
	NEXTBTN,
	PREVBTN,
	PRINTORDERSBTN,
	CHECKFILLS,
	PRINTPOS,
	PRINTBUT,
	LIVEDATACONSOLEPRINTOUT,
	CONNECTLIVEDATA,
	STARTLOOP,
	EXPERIMENT
};

enum class OrderStatus {
	OPEN,
	FILLED,
	PARTFILL,
	CANCELLED
};

#ifndef _MIKEORDERCLASS_DEFINED_
#define _MIKEORDERCLASS_DEFINED_

class MikeOrder
{
public:
	//	MikeOrder();
	//	~MikeOrder();

	//BUYLMT, SELLLMT, BUYSTP, SELLSTP
	MikeOrderType ordertype;

	//this stores which position the order is assigned to
	//there can be multiple orders for one price
	//once order is filled - this tells which position is updated
	long assignedToPosition = 0;

	//the price of the order. prices are in cents.
	long price = 0;

	//the size of the order
	long amount = 0;

	//for future use - for passing orders into outside API
	long orderId;

	//for checking fills - has the order been filled already?
	bool isFilled = false;

	//for future implementation.
	bool partialFill = false;
};

//this class aggregates all the open orders by price. there can be multiple orders of
//multiple kind and amount for a single price. this class keeps track of the total
//b lmt, b stp, s lmt, s stp orders for a single price point.
class MikeOrdersAtPrice
{
public:
	long price = 0;
	long buyLimitAmount = 0;
	long buyStopAmount = 0;
	long sellLimitAmount = 0;
	long sellStopAmount = 0;

	void eraseall();//

					//returns true if all orders are empty at this price
	bool checkifempty();

};

class MikePosition
{
	friend class WidgetTable;
public:
	long price = 0;
	long open_amount = 0;//positive open_amount means the position is 'long'. negative open_amount means the position is 'short'.
	long open_pl = 0;
	long closed_pl = 0;
	long total_pl = 0;

private:
	bool isActive = false;
	long prevbidprice = 0;  //to check if open_pl needs to be recalculated
	long prevaskprice = 0;


public:
	//this is for indexing purposes - set to TRUE if position was ever
	//accessed or changed. Mainly to avoid iterating through tens of thousands
	//of positions
	inline bool checkifActive() { if (isActive == true) return true; else  return false; }
	inline void setActive() { isActive = true; }
	inline void setInactive() { isActive = false; }

public:
	//positive amount for buy orders, negative amount for sell orders!
	void fill(long fillprice, long filledamount)
	{
		//this will modify the closed_pl by:
		//difference in fill price and price of this position
		//multiplied by amount
		long tempclosed_pl = closed_pl;
		long profitloss;
		////////////////////////////////////////////////
		profitloss = (price - fillprice) * filledamount;
		closed_pl = tempclosed_pl + profitloss;
		////////////////////////////////////////////////
		//this updates the current open_amount by the amount that was filled
		long tempopenamount = open_amount;
		open_amount = tempopenamount + filledamount;
		//recalculate PL because the size of position has changed:
		calculatePL(prevbidprice, prevaskprice);
	}
	void calculatePL(long bidprice, long askprice)
	{
		//	static long prevbidprice = 0;
		//	static long prevaskprice = 0;
		if (bidprice != prevbidprice || askprice != prevaskprice)
		{
			open_pl = 0;
			//if position is 'long':
			if (open_amount >= 0) open_pl = (bidprice - price) * open_amount;
			//if position is 'short':
			if (open_amount < 0) open_pl = (askprice - price) * open_amount;

			//update total_pl with new open_pl
			total_pl = closed_pl + open_pl;
			//update bidprice and askprice to make future calculations faster:
			prevbidprice = bidprice;
			prevaskprice = askprice;
		}
	}
};//class MikePosition

#endif // !_MIKEORDERCLASS_DEFINED_

#endif _MIKEENUMS_H_INCLUDED_
