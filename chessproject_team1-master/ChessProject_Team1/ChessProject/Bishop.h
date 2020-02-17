#pragma once
#include "Figure.h"
#include "Board.h"

class Bishop : virtual public Figure
{
	virtual bool check_vaild_move(std::string place_str); //check's if the move is leagal(every Figure diffrent)
public:
	Bishop(Board* board);
	~Bishop();
};