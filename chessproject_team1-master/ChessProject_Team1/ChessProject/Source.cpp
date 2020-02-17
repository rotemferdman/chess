/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/
#include "music.h"
#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Figure.h"
#include "Rook.h"
#include "King.h"

using std::cout;
using std::endl;
using std::string;


int main()
{
	std::thread music(music_thread);
	
	srand(time_t(NULL));

	Board board;
	char turn[TURN_SIZE] = { 0 };
	situation err_code = valid;
	Figure* oldFigure = nullptr;
	Figure* figure = new King(&board); // Just to initialize.

	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			music.detach();
			p.close();
			return 0;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol

	strcpy_s(msgToGraphics, DEFAULT_BOARD);
	turn[0] = (int)board.getCurrTurn() + ASCII_TO_NUM;
	if (board.getCurrTurn())
	{
		turn[0]--;
	}
	strcat_s(msgToGraphics, turn);

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		
		if (board.getPiece(msgFromGraphics[0], msgFromGraphics[1] - ASCII_TO_NUM) != EMPTY) //if place isn't empty
		{
			oldFigure = figure;
			figure = oldFigure->createFigure(msgFromGraphics[0], msgFromGraphics[1] - ASCII_TO_NUM); // Creating a new figure
			delete oldFigure;

			err_code = figure->Update(msgFromGraphics[1] - ASCII_TO_NUM, msgFromGraphics[0], msgFromGraphics[SECOND_Y_POS] - ASCII_TO_NUM, msgFromGraphics[SECOND_X_POS]);
		}
		else
		{
			err_code = noFigure;
		}
			turn[0] = (int)err_code + 48;
			strcpy_s(msgToGraphics, turn); // msgToGraphics should contain the result of the operation

			board.printBoard();

			// return result to graphics		
			p.sendMessageToGraphics(msgToGraphics);

			// get message from graphics
			msgFromGraphics = p.getMessageFromGraphics();
		
	}
	music.detach(); // Detaching the music thread
	p.close(); // Closing the pipe.
	delete figure;
	return 0;
	
}
