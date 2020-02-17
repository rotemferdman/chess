enum situation
{
	valid, // if the move is ok
	chess, // if the move made a chess to the other player
	noFigure, // if the user chose a location that has no figure
	sameColor, // if the final location has a figure with the same color
	selfChess, // if the move made a chess to the player
	invalidLocation, // if the player chose a location that doesn't exist
	invalidMove, // if the player made an invalid move
	sameLocation, // if the start location and end location are the same
	win, // if the player won the game
	enPassant // If the player know the rules and made en passant.
};