#include "Bishop.h"
#include <iostream>
#include "Board.h"

/*
This is the bishop C'tor
Input:
	-Board* board: A pointer to the board.
*/
Bishop::Bishop(Board* board) : Figure(board)
{
}

/*
Bishop D'tor
*/
Bishop::~Bishop()
{
}

/*
This function checks if the move is valid
Input:
	-std::string place_str: The move made.
Output:
	-bool: True if error.
*/
bool Bishop::check_vaild_move(std::string place_str)
{
	bool val = false;
	char start_x = place_str[0];
	int start_y = place_str[1] - ASCII_TO_NUM;

	char end_x = place_str[2];
	int end_y = place_str[3] - ASCII_TO_NUM;
	
	unsigned int counter = 0;
	bool check = false;

	if (end_y > start_y && end_x > start_x) //if it's alahson to the right and up
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
	else if (end_y > start_y && start_x > end_x) //if it moves left and up
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
	else if(start_x > end_x && start_y > end_y) //if going down and left
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
