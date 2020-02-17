#include "Queen.h"
#include "Board.h"
#include "Figure.h"
#include "Bishop.h"
#include "Rook.h"
#define ASCII 48
#define MAX_Y 8
#define MAX_X 'h'

/*
Queen C'tor
Input:
	-Board* board: A pointer to the board.
*/
Queen::Queen(Board* board) : Figure(board)
{
}

/*
Queen D'tor
*/
Queen::~Queen()
{
}

/*
This function checks if the move is valid.
Input:
	-std::string place_str: The move made
Output:
	-bool: True if error.
*/
bool Queen::check_vaild_move(std::string place_str)
{
	bool valid = false;
	char og_x = place_str[0];
	int og_y = place_str[1] - ASCII; //for the end

	char x = place_str[0];
	int y = place_str[1] - ASCII;

	bool val = false;
	char start_x = place_str[0];
	int start_y = place_str[1] - ASCII_TO_NUM;

	char end_x = place_str[SECOND_X_POS];
	int end_y = place_str[SECOND_Y_POS] - ASCII_TO_NUM;

	unsigned int counter = 0;
	bool check = false;

	if (place_str[0] == place_str[SECOND_X_POS]) //if the row isnt changes(change the numbers in the loop)
	{
		if (place_str[1] < place_str[SECOND_Y_POS]) //if y2 bigger then y1 we want to go up!
		{
			for (y = y + 1; y < place_str[SECOND_Y_POS] - ASCII; y++) //change the place in a loop
			{
				if (this->board->getPiece(x, y) != EMPTY) //if the place is not empty(ileagal to jump over another player) 
				{
					val = true;
					y = place_str[SECOND_Y_POS] - ASCII; //ending the loop
				}
				else if (y > MAX_Y) //out of bounds
				{
					val = true;
					y = place_str[SECOND_Y_POS] - ASCII; //ending the loop
				}
			} //end of loop
		}
		else //we want to go down
		{
			for (y = y - 1; y > place_str[SECOND_Y_POS] - ASCII; y--) //change the place in a loop
			{

				if (this->board->getPiece(x, y) != EMPTY) //if the place is not empty(ileagal to jump over another player) 
				{
					val = true;
					y = place_str[SECOND_Y_POS] - ASCII; //ending the loop
				}
				else if (y < 0) //out of bounds
				{
					val = true;
					y = place_str[SECOND_Y_POS] - ASCII; //ending the loop
				}
			} //end of loop
		}
	}


	else if (place_str[1] == place_str[SECOND_Y_POS]) //if the line is changed(change the chars in the loop)
	{
		if (place_str[0] < place_str[2]) //if the 2nd char bigger then the first we wanna go up in the abc
		{
			for (x = x + 1; x < place_str[SECOND_X_POS]; x++) //change the place in a loop
			{

				if (this->board->getPiece(x, y) != EMPTY) //if the place is not empty(ileagal to jump over another player) 
				{
					val = true;
					x = place_str[SECOND_X_POS]; //ending the loop
				}
				else if (x > MAX_X) //out of bounds
				{
					val = true;
					x = place_str[SECOND_X_POS]; //ending the loop
				}
			} //end of loop
		}
		else
		{
			for (x = x - 1; x > place_str[SECOND_X_POS]; x--) //change the place in a loop
			{

				if (this->board->getPiece(x, y) != EMPTY) //if the place is not empty(ileagal to jump over another player) 
				{
					val = true;
					x = place_str[SECOND_X_POS]; //ending the loop
				}
				else if (x < 'a') //out of bounds
				{
					val = true;
					x = place_str[SECOND_X_POS]; //ending the loop
				}
			} //end of loop
		}
	}
	/* END OF ROOK*/
	else if (end_y > start_y&& end_x > start_x) //if it's alahson to the right and up
	{

		for (start_x = start_x + 1; check != true; start_x++)
		{

			if (counter > BOARD_SIZE - 1) //something is wrong, move isn't valid
			{
				val = true;
				check = true; //end of loop
			}
			else
			{
				counter++;
				start_y++;
				if (!((start_x == end_x && start_y == end_y)))
				{
					if (board->getPiece(start_x, start_y) != EMPTY) //if place isn't empty, you can't skip any other Figure
					{
						val = true;
						check = true;
					}
				}
				if (start_x == end_x && start_y == end_y)
				{
					check = true;
				}
			}
		}
	}
	else if (end_y > start_y&& start_x > end_x) //if it moves left and up
	{

		for (start_x = start_x - 1; check != true; start_x--)
		{

			if (counter > BOARD_SIZE - 1) //something is wrong, move isn't valid
			{
				val = true;
				check = true; //end of loop
			}
			else
			{
				counter++;
				start_y++;
				if (!(start_x == end_x && start_y == end_y))
				{
					if (board->getPiece(start_x, start_y) != EMPTY) //if place isn't empty, you can't skip any other Figure
					{
						val = true;
						check = true;
					}
				}
				if (start_x == end_x && start_y == end_y)
				{
					check = true;
				}
			}
		}
	}
	else if (end_y < start_y && start_x < end_x) //if it moves right and down
	{

		for (start_x = start_x + 1; check != true; start_x++)
		{

			if (counter > BOARD_SIZE - 1) //something is wrong, move isn't valid
			{
				val = true;
				check = true; //end of loop
			}
			else
			{
				counter++;
				start_y--; //going down
				if (!(start_x == end_x && start_y == end_y))
				{
					if (board->getPiece(start_x, start_y) != EMPTY) //if place isn't empty, you can't skip any other Figure
					{
						val = true;
						check = true;
					}
				}
				if (start_x == end_x && start_y == end_y)
				{
					check = true;
				}
			}
		}
	}
	else if (start_x > end_x&& start_y > end_y) //if going down and left
	{

		for (start_x = start_x - 1; check != true; start_x--)
		{

			if (counter > BOARD_SIZE - 1) //something is wrong, move isn't valid
			{
				val = true;
				check = true; //end of loop
			}
			else
			{
				counter++;
				start_y--; //going down
				if (!(start_x == end_x && start_y == end_y))
				{
					if (board->getPiece(start_x, start_y) != EMPTY) //if place isn't empty, you can't skip any other Figure
					{
						val = true;
						check = true;
					}
				}
				if (start_x == end_x && start_y == end_y)
				{
					check = true;
				}
			}
		}
	}
	else //invalid move
	{
		val = true;
	}
	return val;
}

