#pragma once
#include "Figure.h"

class King : virtual public Figure
{
private:
	virtual bool check_vaild_move(std::string place_str); //check's if the move is leagal(every Figure diffrent)

public:
	King(Board* board);
	~King();
};
