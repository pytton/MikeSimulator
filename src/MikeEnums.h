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
enum BtnPressed
{
	UPBTN,
	DOWNBTN,
	EXTRABTN,
	SLIDER1,
	NEXTBTN,
	PREVBTN,
	PRINTORDERSBTN,
	CHECKFILLS
};

#endif _MIKEENUMS_H_INCLUDED_
