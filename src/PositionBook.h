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

	MikePosition();
};//class MikePosition

class PositionBook
{
//	using namespace std;
public:

	PositionBook(std::string name, long startprice, long endprice);

	void newPosition(long price, long position);
	MikePosition getPosition(long price);
	bool clearPosition(long price);
	bool changePostion(long price, long amount);




	
	std::vector <MikePosition> positionBook;
	std::string nameOfBook;
	
	


};











#endif _POSITIONBOOK_H_INCLUDED_