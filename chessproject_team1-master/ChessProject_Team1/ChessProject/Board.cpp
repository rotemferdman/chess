#include "Board.h"

/*
This is the board constructor.
Input:
	-None.
*/
Board::Board()
{
	std::string defBoard = DEFAULT_BOARD;
	unsigned short int i = 0;
	unsigned short int j = 0;

	playerOneTurn = true;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = defBoard[(i * BOARD_SIZE) + j];
		}
	}
}

/*
This is the Board destructor.
Input:
	-None.
*/
Board::~Board()
{

}

/*
This function will change the turn.
Input:
	-None.
Output:
	-None.
*/
void Board::changeTurn()
{
	playerOneTurn = !playerOneTurn;
}

/*
This function moves from one place to another.
Input:
	-char toMoveX: The X to move from.
	-int toMoveY: The Y to move from.
	-char moveToX: The X to move to.
	-int moveToY: The Y to move to.
Output:
	-None.
*/
void Board::move(char toMoveX, int toMoveY, char moveToX, int moveToY)
{
	movedFigure = board[BOARD_SIZE - moveToY][moveToX - LETTER_TO_NUM];
	board[BOARD_SIZE - moveToY][moveToX - LETTER_TO_NUM] = board[BOARD_SIZE - toMoveY][toMoveX - LETTER_TO_NUM];
	board[BOARD_SIZE - toMoveY][toMoveX - LETTER_TO_NUM] = EMPTY;
}

/*
	function that changing location of 2 figures
	input: the location of the 2 figures
	output: no output
*/
void Board::swap(char firstX, int firstY, char secondX, int secondY)
{
	char first = this->getPiece(firstX, firstY);
	char second = this->getPiece(secondX, secondY);

	board[BOARD_SIZE - firstY][firstX - LETTER_TO_NUM] = second;
	board[BOARD_SIZE - secondY][secondX - LETTER_TO_NUM] = first;
}

/*
This function "Undoes" a move.
Input:
	-char movedX: The X we moved from.
	-int movedY: The Y we moved from.
	-char moveToX: The X to move to.
	-int moveToY: The Y to move to.
Output:
	-None.
*/
void Board::undo(char movedX, int movedY, char movedToX, int movedToY)
{
	board[BOARD_SIZE - movedY][movedX - LETTER_TO_NUM] = board[BOARD_SIZE - movedToY][movedToX - LETTER_TO_NUM];
	board[BOARD_SIZE - movedToY][movedToX - LETTER_TO_NUM] = movedFigure;
}

/*
changing a piece in the board
*/
void Board::changeBoard(char x, int y)
{
	this->board[8 - y][x - LETTER_TO_NUM] = '#';
}


/*
This function will print the board.
Input:
	-None.
Output:
	-None.
*/
void Board::printBoard()
{
	unsigned short int i = 0;
	unsigned short int j = 0;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			std::cout << " " << board[i][j];
		}

		std::cout << std::endl;
	}
}

/*
This function gets a piece from a location on the board.
Input:
	const char& x: The X location to get from.
	const int& y: The Y location to get from.
*/
char Board::getPiece(const char& x, const int& y)
{
	return board[BOARD_SIZE - y][x - LETTER_TO_NUM];
}

/*
This function returns the current player one turn status.
Input:
	-None.
Output:
	-bool: player one's turn status.
*/
bool Board::getCurrTurn()
{
	return playerOneTurn;
}

/*
This function checks if there's a win.
Input:
	-None.
Output:
	-bool: true if there's a win.
*/
bool Board::checkWin()
{
	std::string kingLoc = "";
	bool win = false;

	kingLoc = getKingLoc();

	if (kingLoc == "ERR")
	{
		win = true;
	}

	return win;
}

/*
This function searches and returns the location of the current player's king.
Input:
	-None.
Output:
	-std::string: The king's location.
*/
std::string Board::getKingLoc()
{
	std::string kingLoc = "ERR";
	char toSearch = BLACK_KING;
	unsigned short int i = 0;
	unsigned short int j = 0;

	if (playerOneTurn)
	{
		toSearch = WHITE_KING;
	}

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == toSearch)
			{
				kingLoc = (char)(j + LETTER_TO_NUM);
				kingLoc += std::to_string(BOARD_SIZE - i);
			}
		}
	}

	return kingLoc;
}
