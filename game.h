#pragma once

#include "player.h"
#include "board.h"

class Game
{

public:
	Game();
	~Game();

	Player player[2];
	ChessBoard::Board myBoard;

	void StartGame();
	void PrintBoard();
	void PrintMoves();
	bool Move(const int start, const int destination);

	ChessBoard::Piece::color WhoseMove();

};

