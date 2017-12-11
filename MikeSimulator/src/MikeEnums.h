#ifndef _MIKEENUMS_H_INCLUDED_
#define _MIKEENUMS_H_INCLUDED_

/*! \file
MikeEnums.h contains various enums and classes used by the rest of the code
*/

namespace Mike {

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
		EXPERIMENT,
		CANCELALLORDERS,
		CLEARALLPOSITIONS
	};

	enum class OrderStatus {
		OPEN,
		FILLED,
		PARTFILL,
		CANCELLED
	};



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

		//was the order cancelled?
		bool cancelled = false;
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

		void eraseall();

		//returns true if all orders are empty at this price
		bool checkifempty();

	};

	/*! A single position for a particular price - open amount, openPL, closedPL, totalPL. One Positions class can have many single MikePosition members - but only one for a particular price point.*/
	class MikePosition
	{
		friend class WidgetTable;
	public:
		/*! price in cents*/
		long mPositionPrice = 0;
		/*! positive open_amount means the position is 'long'. negative open_amount means the position is 'short'.*/
		long mPositionOpenAmount = 0;
		/*! open profit/loss. call calculatePL(bidprice, askprice) to update this*/
		long mOpenPL = 0;
		/* closed profit/loss for this particular price*/
		long mClosedPL = 0;
		/*! total profit/loss for this price*/
		long mTotalPL = 0;

	private:
		bool mIsActive = false;
		long mPrevbidprice = 0;  //to check if open_pl needs to be recalculated
		long mPrevaskprice = 0;


	public:
		//this is for indexing purposes - set to TRUE if position was ever
		//accessed or changed. Mainly to avoid iterating through tens of thousands
		//of positions
		inline bool checkifActive() { if (mIsActive == true) return true; else  return false; }
		inline void setActive() { mIsActive = true; }
		inline void setInactive() { mIsActive = false; }


	public:
		//positive amount for buy orders, negative amount for sell orders!
		void fill(long fillprice, long filledamount)
		{
			//this will modify the mClosedPL by:
			//difference in fill price and price of this position
			//multiplied by amount
			long tempclosed_pl = mClosedPL;
			long profitloss;
			////////////////////////////////////////////////
			profitloss = (mPositionPrice - fillprice) * filledamount;
			mClosedPL = tempclosed_pl + profitloss;
			////////////////////////////////////////////////
			//this updates the current open_amount by the amount that was filled
			long tempopenamount = mPositionOpenAmount;
			mPositionOpenAmount = tempopenamount + filledamount;
			//recalculate PL because the size of position has changed:
			calculatePL(mPrevbidprice, mPrevaskprice);
		}
		void calculatePL(long bidprice, long askprice)
		{

			if (bidprice != mPrevbidprice || askprice != mPrevaskprice)
			{
				mOpenPL = 0;
				//if position is 'long':
				if (mPositionOpenAmount >= 0) mOpenPL = (bidprice - mPositionPrice) * mPositionOpenAmount;
				//if position is 'short':
				if (mPositionOpenAmount < 0) mOpenPL = (askprice - mPositionPrice) * mPositionOpenAmount;

				//update mTotalPL with new open_pl
				mTotalPL = mClosedPL + mOpenPL;
				//update bidprice and askprice to make future calculations faster:
				mPrevbidprice = bidprice;
				mPrevaskprice = askprice;
			}
		}
	};//class MikePosition

}//namespace Mike



#endif _MIKEENUMS_H_INCLUDED_
