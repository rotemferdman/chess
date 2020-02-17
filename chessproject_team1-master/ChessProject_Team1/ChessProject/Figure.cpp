#include "Figure.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "Pawn.h"

#include <iostream>

/*
This is the Figure constructor.
Input:
	-Board* board: A pointer to the main game board.
*/
Figure::Figure(Board* newBoard)
{
	board = newBoard;
}

/*
This is the Figure destructor.
Input:
	-None.
*/
Figure::~Figure()
{
}

/*
This function will create a new figure!
Input:
	-unsigned char toGetx: The x spot of the figure to create.
	-unsigned char toGetY: The y spot of the figure to create.
Output:
	-Figure*: A pointer to the new figure.
*/
Figure* Figure::createFigure(unsigned char toGetX, unsigned int toGetY)
{
	Figure* newFig = nullptr;
	switch (board->getPiece(toGetX, toGetY))
	{
	// If it is a king
	case 'k':
		newFig = new King(board);
		break;
	case 'K':
		newFig = new King(board);
		break;
	// If it is a rook
	case 'r':
		newFig = new Rook(board);
		break;
	case 'R':
		newFig = new Rook(board);
		break;
	// If it is a bishop
	case 'b':
		newFig = new Bishop(board);
		break;
	case 'B':
		newFig = new Bishop(board);
		break;
	// If it is a knight
	case 'n':
		newFig = new Knight(board);
		break;
	case 'N':
		newFig = new Knight(board);
		break;
	// If it is a queen
	case 'Q':
		newFig = new Queen(board);
		break;
	case 'q':
		newFig = new Queen(board);
		break;
	// If it is a pawn
	case 'P':
		newFig = new Pawn(board);
		break;
	case 'p':
		newFig = new Pawn(board);
		break;
	default:
		std::cout << "Fatal error! Please restart the program." << std::endl;
		break;
	}

	return newFig;
}

/*
This function 'Updates' the board (if can do, if not - returns an error code).
Input:
	-int start_int: The starting Y index.
	-unsigned char start_chr: The starting X index.
	-int end_int: The ending Y index.
	-unsigned char end_chr: The ending X index.
Output:
	-situation: An enum that contains the error.
*/
situation Figure::Update(int start_int, unsigned char start_chr, int end_int, unsigned char end_chr)
{
	situation err_code = valid;
	std::string place = "";
	std::string kingLoc = "";

	// Moving the parameters to a string.
	place += start_chr;
	place += std::to_string(start_int);
	place += end_chr;
	place += std::to_string(end_int);

	if (this->check_bounds(place))
	{
		err_code = invalidLocation;
	}
	// Checking for the existence of you in the place.
	else if (this->check_start_exist(place))
	{
		err_code = noFigure;
	}
	// Checking for the existence of the end in the place.
	else if (this->check_end_exist(place))
	{
		err_code = sameColor;
	}
	// Checking if the move was valid.
	else if (this->check_vaild_move(place))
	{
		err_code = invalidMove;
	}
	// Checking if the player even moved.
	else if (this->not_moving(place))
	{
		err_code = sameLocation;
	}

	if (err_code == valid)
	{
		// Making a move on the board
		board->move(start_chr, start_int, end_chr, end_int);

		// Checking if the player made a chess on himself.
		if (this->check_player_chess(place))
		{
			board->undo(start_chr, start_int, end_chr, end_int);
			err_code = selfChess;
		}
		// Checking En Passant
		else if ((board->getPiece(end_chr, end_int) == 'p' || board->getPiece(end_chr, end_int) == 'P') && ((Pawn*)this)->enPassantMade)
		{
			err_code = enPassant;
		}
		// Checking for win
		else if (board->checkWin())
		{
			err_code = win;
		}

		if (err_code == valid)
		{
			place[0] = place[SECOND_X_POS];
			place[1] = place[SECOND_Y_POS];
			kingLoc = board->getKingLoc();
			place[SECOND_X_POS] = kingLoc[0];
			place[SECOND_Y_POS] = kingLoc[1];

			// Checking for a chess on the rival
			if (!(this->check_vaild_move(place)))
			{
				err_code = chess;
			}
		}
	}

	return err_code;
}

/*
This function checks if the figure isn't moving at all.
Input:
	-std::string place_str: The place of the piece.
Output:
	-bool: true if error, false if ok.
*/
bool Figure::not_moving(std::string place_str)
{
	bool err = false;

	if (place_str[0] == place_str[SECOND_X_POS] && place_str[1] == place_str[SECOND_Y_POS]) //if the places are equal
	{
		err = true; //invalid move
	}

	return err;
}

/*
This function checks the bounds of the place_str.
Input:
	-std::string place_str: The string the contains the places to move.
Output:
	-bool: true if error.
*/
bool Figure::check_bounds(std::string place_str)
{
	bool err = false;

	if (place_str[0] - LETTER_TO_NUM > BOARD_SIZE || place_str[1] - ASCII_TO_NUM > BOARD_SIZE ||
		place_str[SECOND_X_POS] - LETTER_TO_NUM > BOARD_SIZE || place_str[SECOND_Y_POS] - ASCII_TO_NUM > BOARD_SIZE
		|| place_str[0] - LETTER_TO_NUM < 0 || place_str[1] - ASCII_TO_NUM < 0 ||
		place_str[SECOND_X_POS] - LETTER_TO_NUM < 0 || place_str[SECOND_Y_POS] - ASCII_TO_NUM < 0)
	{
		err = true;
	}

	return err;
}

/*
This function checks if the figure exists at start.
Input:
	-std::string place_str: The place of the piece.
Output:
	-bool: true if error, false if ok.
*/
bool Figure::check_start_exist(std::string place_str)
{
	bool err = false;
	char x = place_str[0];
	int y = place_str[1] - ASCII_TO_NUM;

	// Checking if the start is empty
	if (board->getPiece(x, y) == EMPTY)
	{
		err = true;
	}
	else if (board->getCurrTurn() && board->getPiece(x, y) > WHITE) // if black
	{
		err = true;
	}
	else if (!board->getCurrTurn() && board->getPiece(x, y) <= WHITE) // if white
	{
		err = true;
	}

	return err;
}

/*
This function checks for the end existence.
Input:
	-std::string place_str: contains the movement of the piece.
Output:
	-bool: true if error.
*/
bool Figure::check_end_exist(std::string place_str)
{
	char x = place_str[0];
	int y = place_str[1] - ASCII_TO_NUM;

	char x_end = place_str[SECOND_X_POS];
	int y_end = place_str[SECOND_Y_POS] - ASCII_TO_NUM;
	bool val = false; //setting the values

	if (this->board->getCurrTurn()) //if the turn is white
	{
		if (board->getPiece(x_end, y_end) <= WHITE && board->getPiece(x_end, y_end) != EMPTY) //if the white Figure trying to hit another white - it's illeagal
		{
			val = true;
		}
	}
	else //if it's the black turn
	{
		if (board->getPiece(x_end, y_end) > WHITE && board->getPiece(x_end, y_end) != EMPTY) //if black trying to hit black
		{
			val = true;
		}
	}

	return val;
}

/*
	function that checking if there was a chess
	input: the move the player did
	output: if there is a chess or not
*/
bool Figure::check_player_chess(std::string place_str)
{
	bool error = false;
	std::string king = this->board->getKingLoc();
	std::string piecesToCheck = WHITE_PIECES;
	char i = king[0];
	int j = king[1] - ASCII_TO_NUM;

	// If we need to change the set we're working on..
	if (board->getCurrTurn())
	{
		piecesToCheck = BLACK_PIECES;
	}

	if (this->board->getPiece(i - 1, j - 1) == piecesToCheck[PAWN] || this->board->getPiece(i + 1, j - 1) == piecesToCheck[PAWN] ||
		this->board->getPiece(i - 1, j + 1) == piecesToCheck[PAWN] || this->board->getPiece(i + 1, j + 1) == piecesToCheck[PAWN] ||
		this->board->getPiece(i - KNIGHT_MAX_OFFSET, j - 1) == piecesToCheck[KNIGHT] || this->board->getPiece(i - KNIGHT_MAX_OFFSET, j + 1) == piecesToCheck[KNIGHT] ||
		this->board->getPiece(i - 1, j - KNIGHT_MAX_OFFSET) == piecesToCheck[KNIGHT] || this->board->getPiece(i - 1, j + KNIGHT_MAX_OFFSET) == piecesToCheck[KNIGHT] ||
		this->board->getPiece(i + KNIGHT_MAX_OFFSET, j - 1) == piecesToCheck[KNIGHT] || this->board->getPiece(i + KNIGHT_MAX_OFFSET, j + 1) == piecesToCheck[KNIGHT] ||
		this->board->getPiece(i + 1, j - KNIGHT_MAX_OFFSET) == piecesToCheck[KNIGHT] || this->board->getPiece(i + 1, j + KNIGHT_MAX_OFFSET) == piecesToCheck[KNIGHT])
	{
		error = true;
	}

	// Checking right
	for (i = king[0] + 1; !error && i <= 'h' && i >= 'a'; i++)
	{
		if (board->getPiece(i, king[1] - ASCII_TO_NUM) == piecesToCheck[ROOK]) // If rook is in the way (More will come soon)
		{
			error = true;
		}
		// If we reaches something that "blocks" the opportunity
		else if (board->getPiece(i, king[1] - ASCII_TO_NUM) != EMPTY && piecesToCheck.find(board->getPiece(i, king[1] - ASCII_TO_NUM)) == std::string::npos)
		{
			i = -1; // Breaking the loop
		}
	}

	// Checking left
	for (i = king[0] - 1; !error && i <= 'h' && i >= 'a'; i--)
	{
		if (board->getPiece(i, king[1] - ASCII_TO_NUM) == piecesToCheck[ROOK] || board->getPiece(i, king[1] - ASCII_TO_NUM) == piecesToCheck[QUEEN]) // If Rook / Queen is in the way.
		{
			error = true;
		}
		// If we reaches something that "blocks" the opportunity
		else if (board->getPiece(i, king[1] - ASCII_TO_NUM) != EMPTY && piecesToCheck.find(board->getPiece(i, king[1] - ASCII_TO_NUM)) == std::string::npos)
		{
			i = -1; // Breaking the loop
		}
	}

	// Checking up
	for (i = king[1] - ASCII_TO_NUM + 1; !error && i <= BOARD_SIZE && i > 0; i++)
	{
		if (board->getPiece(king[0], i) == piecesToCheck[ROOK] || board->getPiece(king[0], i) == piecesToCheck[QUEEN]) // If Rook / Queen is in the way.
		{
			error = true;
		}
		// If we reaches something that "blocks" the opportunity
		else if (board->getPiece(king[0], i) != EMPTY && piecesToCheck.find(board->getPiece(king[0], i)) == std::string::npos)
		{
			i = -1; // Breaking the loop
		}
	}

	// Checking down
	for (i = king[1] - ASCII_TO_NUM - 1; !error && i <= BOARD_SIZE && i > 0; i--)
	{
		if (board->getPiece(king[0], i) == piecesToCheck[ROOK] || board->getPiece(king[0], i) == piecesToCheck[QUEEN]) // If Rook / Queen is in the way.
		{
			error = true;
		}
		// If we reaches something that "blocks" the opportunity
		else if (board->getPiece(king[0], i) != EMPTY && piecesToCheck.find(board->getPiece(king[0], i)) == std::string::npos)
		{
			i = -1; // Breaking the loop
		}
	}

	// Checking up-right
	j = king[1] - ASCII_TO_NUM + 1;
	for (i = king[0] + 1; !error && i <= 'h' && i >= 'a' && j > 0 && j <= BOARD_SIZE; i++)
	{
		if (board->getPiece(i, j) == piecesToCheck[BISHOP] || board->getPiece(i, j) == piecesToCheck[QUEEN]) // If Bishop / Queen is in the way
		{
			error = true;
		}
		// If we reaches something that "blocks" the opportunity
		else if (board->getPiece(i, king[1] - ASCII_TO_NUM) != EMPTY && piecesToCheck.find(board->getPiece(i, king[1] - ASCII_TO_NUM)) == std::string::npos)
		{
			i = -1; // Breaking the loop
		}
		j++;
	}

	// Checking up-left
	j = king[1] - ASCII_TO_NUM + 1;
	for (i = king[0] - 1; !error && i <= 'h' && i >= 'a' && j > 0 && j <= BOARD_SIZE; i--)
	{
		if (board->getPiece(i, j) == piecesToCheck[BISHOP] || board->getPiece(i, j) == piecesToCheck[QUEEN]) // If Bishop / Queen is in the way.
		{
			error = true;
		}
		// If we reaches something that "blocks" the opportunity
		else if (board->getPiece(i, king[1] - ASCII_TO_NUM) != EMPTY && piecesToCheck.find(board->getPiece(i, king[1] - ASCII_TO_NUM)) == std::string::npos)
		{
			i = -1; // Breaking the loop
		}
		j++;
	}

	// Checking down-right
	j = king[1] - ASCII_TO_NUM - 1;
	for (i = king[0] + 1; !error && i <= 'h' && i >= 'a' && j > 0 && j <= BOARD_SIZE; i++)
	{
		if (board->getPiece(i, j) == piecesToCheck[BISHOP] || board->getPiece(i, j) == piecesToCheck[QUEEN]) // If Bishop / Queen is in the way.
		{
			error = true;
		}
		// If we reaches something that "blocks" the opportunity
		else if (board->getPiece(i, j) != EMPTY && piecesToCheck.find(board->getPiece(i, j)) == std::string::npos)
		{
			i = -1; // Breaking the loop
		}
		j--;
	}

	// Checking down-left
	j = king[1] - ASCII_TO_NUM - 1;
	for (i = king[0] - 1; !error && i <= 'h' && i >= 'a' && j > 0 && j <= BOARD_SIZE; i--)
	{
		if (board->getPiece(i, j) == piecesToCheck[BISHOP] || board->getPiece(i, j) == piecesToCheck[QUEEN]) // If Bishop / Queen is in the way.
		{
			error = true;
		}
		// If we reaches something that "blocks" the opportunity
		else if (board->getPiece(i, j) != EMPTY && piecesToCheck.find(board->getPiece(i, j)) == std::string::npos)
		{
			i = -1; // Breaking the loop
		}
		j--;
	}

	// If all's good
	if (!error)
	{
		board->changeTurn(); // We ought to do it in the function call for the natural order of the functions.
	}

	return error;
}
