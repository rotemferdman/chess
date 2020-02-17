#include "figure.h"
#include "Board.h"

#define KNIGHT_MAX_OFFSET 2

class Knight : public Figure
{
public:
	Knight(Board* board);
	~Knight();
	
private:
	virtual bool check_vaild_move(std::string place_str); //check's if the move is leagal(every Figure diffrent)
};