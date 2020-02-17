#pragma once
#include <iostream>
#include <string>

#define BOARD_SIZE 8
#define DEFAULT_BOARD "rbnkqnbrpppppppp################################PPPPPPPPRBNKQNBR"
#define EMPTY '#'
#define BLACK_KING 'k'
#define WHITE_KING 'K'
#define LETTER_TO_NUM 97
#define ASCII_TO_NUM 48
#define TURN_SIZE 2
#define WHITE 90

class Board
{
private:
	char board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	bool playerOneTurn;
	char movedFigure;

public:
	Board();
	~Board();
	void changeTurn();
	void move(char toMoveX, int toMoveY, char moveToX, int moveToY);
	void swap(char firstX, int firstY, char secondX, int secondY);
	void undo(char movedX, int movedY, char movedToX, int movedToY);
	void changeBoard(char x, int y);
	void printBoard();
	char getPiece(const char& x, const int& y);
	bool getCurrTurn();
	bool checkWin();
	std::string getKingLoc();
};
