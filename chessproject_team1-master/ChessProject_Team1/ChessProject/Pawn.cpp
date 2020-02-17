#include "Pawn.h"
#include "Board.h"

bool Pawn::enPassantMade = false;
bool Pawn::enPassant = false;

/*
Pawn C'tor
Input:
	-Board* board: A pointer to the board.
*/
Pawn::Pawn(Board* board) : Figure(board)
{
}

/*
Pawn D'tor
*/
Pawn::~Pawn()
{
}

/*
	function that checking if the player want to do a valid move
	input: the move the player want to do
	output: if there was a problem ot not
*/
bool Pawn::check_vaild_move(std::string place_str)

{
	
	bool err = true;
	char x_end = place_str[SECOND_X_POS];
	int y_end = place_str[SECOND_Y_POS] - ASCII_TO_NUM;
	char x_start = place_str[0];
	int y_start = place_str[1] - ASCII_TO_NUM;
	enPassantMade = false;

	if (board->getCurrTurn() == 0) // black turn
	{
		if (y_start == BOARD_SIZE - 1) // if the pawn is in this place the pawn can move 2 spaces
		{
			if ((x_end == x_start && y_end == y_start - DOUBLE_MOVE && (board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start && y_end == y_start - 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start + 1 && y_end == y_start - 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) != '#')) || (x_end == x_start - 1 && y_end == y_start - 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) != '#'))) // every move the player can do
			{
				enPassant = true;
				err = false;
			}
		}
		else
		{
			if ((x_end == x_start && y_end == y_start - 1 && (board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) == '#')) || (x_end == x_start + 1 && y_end == y_start - 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) != '#')) || (x_end == x_start - 1 && y_end == y_start - 1 && (this->board->getPiece(x_end, y_end) > WHITE || this->board->getPiece(x_end, y_end) != '#'))) // every move the player can do
			{
				err = false;
			}
			if (enPassant == true && board->getPiece(x_end, y_end + 1) == 'P') //if the last turn was move 2, theres no error and the piece that is in the end minus 1 is a pawn, then it can eat it due to En Passent.
			{
				err = false;
				enPassantMade = true;
				board->changeBoard(place_str[SECOND_X_POS], y_end + 1);
			}
			if (board->getPiece(x_end, y_end) != BLACK_KING)
			{
				enPassant = false;
			}
			
		}

	}
	else // white turn
	{
		if (y_start == 2) // if the pawn is in this place the pawn can move 2 spaces
		{
			if ((x_end == x_start && y_end == y_start + DOUBLE_MOVE && (board->getPiece(x_end, y_end) <= WHITE)) || (x_end == x_start && y_end == y_start + 1 && (this->board->getPiece(x_end, y_end) <= WHITE)) || (x_end == x_start + 1 && y_end == y_start + 1 && (this->board->getPiece(x_end, y_end) > WHITE)) || (x_end == x_start - 1 && y_end == y_start + 1 && (this->board->getPiece(x_end, y_end) > WHITE))) // every move the player can do
			{
				enPassant = true;
				err = false;
			}
		}
		else
		{
			if ((x_end == x_start && y_end == y_start + 1 && (board->getPiece(x_end, y_end) <= WHITE)) || (x_end == x_start + 1 && y_end == y_start + 1 && (this->board->getPiece(x_end, y_end) > WHITE)) || (x_end == x_start - 1 && y_end == y_start + 1 && (this->board->getPiece(x_end, y_end) > WHITE))) // every move the player can do
			{
				err = false;
			}
			if (enPassant == true && board->getPiece(x_end, y_end - 1) == 'p') //if the last turn was move 2, theres no error and the piece that is in the end minus 1 is a pawn, then it can eat it due to En Passent.
			{
				err = false;
				enPassantMade = true;
				board->changeBoard(place_str[SECOND_X_POS], y_end - 1);
				
			}
			if (board->getPiece(x_end, y_end) != WHITE_KING)
			{
				enPassant = false;
			}
		}
	}


	return err;
}
