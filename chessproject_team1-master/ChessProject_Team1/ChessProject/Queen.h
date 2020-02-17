#pragma once
#include "Figure.h"
#include "Board.h"
#include <iostream>

class Queen : virtual public Figure
{
private:
	virtual bool check_vaild_move(std::string place_str); //check's if the move is leagal(every Figure diffrent)
public:
	Queen(Board* board);
	~Queen();
};
