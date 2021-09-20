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

	void StartGame(ChessBoard::Piece::color startWhoseMove = ChessBoard::Piece::color::orange);
	void PrintBoard();
	void PrintMoves();
	ChessBoard::moveErrorCodes Move(const int start, const int destination, 
		const ChessBoard::MoveData& inMoveData, ChessBoard::MoveData& outMoveData);

	ChessBoard::Piece::color WhoseMove();

};

