#pragma once
#include "Figure.h"
#include "Board.h"
#include <iostream>

class Rook : virtual public Figure
{
	virtual bool check_vaild_move(std::string place_str); //check's if the move is leagal(every Figure diffrent)
public:
	Rook(Board* board);
	~Rook();
};