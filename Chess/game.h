#pragma once

#include "player.h"
#include "board.h"

class Game
{

private:
	ChessBoard::Board myBoard;
public:
	Game();
	~Game();

	Player player[2];

	void StartGame();
	void PrintBoard();
	void PrintMoves();
	bool Move(const int start, const int destination);

	ChessBoard::Piece::color WhoseMove();

};

