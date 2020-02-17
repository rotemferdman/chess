#include "Knight.h"
#include "Board.h"
#include "figure.h"

/*
This is the knight C'tor
Input:
	-Board* board: A pointer to the board.
*/
Knight::Knight(Board* board) : Figure(board)
{

}

/*
Knight D'tor
*/
Knight::~Knight()
{

}

/*
	function that checking if the move is possible
	input: the move the player want to do 
	output: if there was a problem or not
*/
bool Knight::check_vaild_move(std::string place_str)
{
	bool err = true;
	char x_end = place_str[SECOND_X_POS];
	int y_end = place_str[SECOND_Y_POS] - ASCII_TO_NUM;
	char x_start = place_str[0];
	int y_start = place_str[1] - ASCII_TO_NUM;
	
	if (this->board->getCurrTurn() == 0) // white player
	{
		if ((x_end == x_start + KNIGHT_MAX_OFFSET && y_end == y_start + 1 && this->board->getPiece(x_end, y_end) <= WHITE ) || (x_end == x_start + KNIGHT_MAX_OFFSET && y_end == y_start - 1 && this->board->getPiece(x_end, y_end) <= WHITE) || (x_end == x_start - KNIGHT_MAX_OFFSET && y_end == y_start + 1 && this->board->getPiece(x_end, y_end) <= WHITE) || (x_end == x_start - KNIGHT_MAX_OFFSET && y_end == y_start - 1 && this->board->getPiece(x_end, y_end) <= WHITE) || (x_end == x_start + 1 && y_end == y_start + KNIGHT_MAX_OFFSET && this->board->getPiece(x_end, y_end) <= WHITE) || (x_end == x_start - 1 && y_end == y_start + KNIGHT_MAX_OFFSET && this->board->getPiece(x_end, y_end) <= WHITE) || (x_end == x_start + 1 && y_end == y_start - KNIGHT_MAX_OFFSET && this->board->getPiece(x_end, y_end) <= WHITE) || (x_end == x_start - 1 && y_end == y_start - KNIGHT_MAX_OFFSET && this->board->getPiece(x_end, y_end) <= WHITE)) // every possible move
		{
			err = false;
		}
	}
	else // black turn
	{
		if ((x_end == x_start + KNIGHT_MAX_OFFSET && y_end == y_start + 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start + KNIGHT_MAX_OFFSET && y_end == y_start - 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start - KNIGHT_MAX_OFFSET && y_end == y_start + 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start - KNIGHT_MAX_OFFSET && y_end == y_start - 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start + 1 && y_end == y_start + KNIGHT_MAX_OFFSET && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start - 1 && y_end == y_start + KNIGHT_MAX_OFFSET && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start + 1 && y_end == y_start - KNIGHT_MAX_OFFSET && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start - 1 && y_end == y_start - KNIGHT_MAX_OFFSET && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')))
		{
			err = false;
		}
	}
	
	return err;
}
