#include "figure.h"
#include "Board.h"

#define DOUBLE_MOVE 2

class Pawn : public Figure
{
private:
	virtual bool check_vaild_move(std::string place_str); //check's if the move is leagal(every Figure diffrent)

public:
	static bool enPassantMade;
	static bool enPassant;

	Pawn(Board* board);
	~Pawn();

};