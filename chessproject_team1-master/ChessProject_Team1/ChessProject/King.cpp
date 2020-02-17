#include "King.h"

/*
This function is the king's c'tor.
Input:
	-Board* board: The address of the board.
*/
King::King(Board* board) : Figure(board)
{

};

/*
King's d'tor.
Input:
	-None.
*/
King::~King()
{

};

/*
This function checks if the move is valid.
Input:
	-std::string place_str: The movement of the piece.
Output:
	-bool: true if error.
*/
bool King::check_vaild_move(std::string place_str)
{
	char x_start = place_str[0];
	int y_start = place_str[1] - ASCII_TO_NUM;
	char x_end = place_str[SECOND_X_POS];
	int y_end = place_str[SECOND_Y_POS] - ASCII_TO_NUM;
	bool error = true;
	char type = this->board->getPiece(x_start, y_start);
	char i = '0';
	bool check = 0;

	if ((int)x_start - (int)x_end == 1 || (int)x_start - (int)x_end == -1) // king can move only one space
	{
		if (y_start - y_end == 1 || y_start - y_end == -1 || y_start - y_end == 0) // king can move only one space
		{
			if (this->board->getPiece(x_end, y_end) == '#') // if the space is empty
			{
				error = false;
			}
			else
			{
				if ((int)type > WHITE) // if it's a black figure
				{
					if (this->board->getPiece(x_end, y_end) <= WHITE && this->board->getPiece(x_end, y_end) != WHITE_KING) // if the figure in the end space is in different color
					{
						error = false;
					}
				}
				else
				{
					if (this->board->getPiece(x_end, y_end) > WHITE&& this->board->getPiece(x_end, y_end) != BLACK_KING) // if the figure in the end space is in different color
					{
						error = false;
					}
				}
			}
		}
	}
	else if ((int)x_start - (int)x_end == 0) // if the x value didn't change
	{
		if (y_start - y_end == 1 || y_start - y_end == -1) // if the x value didn't change the y value must change
		{
			if (this->board->getPiece(x_end, y_end) == '#') // Checking if the king can move
			{
				error = false;
			}
			else
			{
				if ((int)type > WHITE)
				{
					// Checking that we don't want to hit a friend / the other king
					if (this->board->getPiece(x_end, y_end) <= WHITE && this->board->getPiece(x_end, y_end) != WHITE_KING)
					{
						error = false;
					}
				}
				else
				{
					// Checking that we don't want to hit a friend / the other king
					if (this->board->getPiece(x_end, y_end) > WHITE&& this->board->getPiece(x_end, y_end) != BLACK_KING)
					{
						error = false;
					}
				}
			}
		}
	}
	return error;
}
