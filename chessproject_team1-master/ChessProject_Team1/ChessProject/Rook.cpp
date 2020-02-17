#define ASCII 48
#define MAX_Y 8
#define MAX_X 'h'
#include "Rook.h"
#include "Figure.h"
#include <iostream>

/*
Rook's c'tor, used to construct rooks.
Input:
	-Board* board: The board's address.
*/
Rook::Rook(Board* board) : Figure(board)
{

}

/*
Rook's d'tor, used to destruct rooks.
Input:
	-None.
*/
Rook::~Rook()
{

}

/*
checks if the move is ok and not passing above any other figures
input: the string that represent the place
out: bool - if theres error - true.
*/
bool Rook::check_vaild_move(std::string place_str)
{
	bool valid = false;
	char og_x = place_str[0];
	int og_y = place_str[1] - ASCII; //for the end

	char x = place_str[0];
	int y = place_str[1] - ASCII;

	if (place_str[0] == place_str[SECOND_X_POS]) //if the row isnt changes(change the numbers in the loop)
	{
		if (place_str[1] < place_str[SECOND_Y_POS]) //if y2 bigger then y1 we want to go up!
		{
			for (y = y + 1; y < place_str[SECOND_Y_POS] - ASCII; y++) //change the place in a loop
			{
				if (this->board->getPiece(x, y) != EMPTY) //if the place is not empty(ileagal to jump over another player) 
				{
					valid = true;
					y = place_str[SECOND_Y_POS] - ASCII; //ending the loop
				}
				else if (y > MAX_Y) //out of bounds
				{
					valid = true;
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
					valid = true;
					y = place_str[SECOND_Y_POS] - ASCII; //ending the loop
				}
				else if (y < 0) //out of bounds
				{
					valid = true;
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
					valid = true;
					x = place_str[SECOND_X_POS]; //ending the loop
				}
				else if (x > MAX_X) //out of bounds
				{
					valid = true;
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
					valid = true;
					x = place_str[SECOND_X_POS]; //ending the loop
				}
				else if (x < 'a') //out of bounds
				{
					valid = true;
					x = place_str[SECOND_X_POS]; //ending the loop
				}
			} //end of loop
		}
	}
	else
	{
		valid = true; //its an error.
	}
	return valid;
}
