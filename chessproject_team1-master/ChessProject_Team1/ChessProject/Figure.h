#pragma once
#include <iostream>
#include <string>
#include "Board.h"
#include "Errors.h"

#define SECOND_X_POS 2
#define SECOND_Y_POS 3
#define REVERSE_INDEX 201
#define BLACK_PIECES "kqbnrp"
#define WHITE_PIECES "KQBNRP"
#define KING 0
#define QUEEN 1
#define BISHOP 2
#define KNIGHT 3
#define ROOK 4
#define PAWN 5

class Figure
{
protected:
	Board* board;

	virtual bool check_start_exist(std::string place_str); //check's if the start place is empty or with another player(can eat the player)
	virtual bool check_end_exist(std::string place_str); //check's if the end place is empty or with another player(can eat the player)
	virtual bool check_bounds(std::string place_str);
	virtual bool check_player_chess(std::string place_str); //if the player is dumb and did something that threat his king
	virtual bool check_vaild_move(std::string place_str) = 0; //check's if the move is legal(every Figure diffrent)
	virtual bool not_moving(std::string place_str); //check's if the character isn't moving

public:
	Figure* createFigure(unsigned char toGetX, unsigned int toGetY);
	virtual situation Update(int start_int, unsigned char start_chr, int end_int, unsigned char end_chr); //update the places of the figure in the local board
	Figure(Board* board);
	virtual ~Figure();
};
