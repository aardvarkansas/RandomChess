#pragma once
#include <deque>
#include "board.h"

class Player
{
private:
	
	bool isHuman=false;
	unsigned int seed_for_random_move = 0;
public:
	Player();
	Player(ChessBoard::Piece::color myColor, bool isHuman = true);
	~Player();

	// These functions 
	std::pair<short, short> GetNextMove(ChessBoard::Board& myBoard, 
		const ChessBoard::MoveData& inMoveData);
	bool GetNextMove(std::string& input, ChessBoard::Board& gameBoard, 
		std::deque<std::pair<short, short>>& movesFromFile, 
		const ChessBoard::MoveData& inMoveData);

	std::pair<short, short> GetRandomMove(ChessBoard::Board& gameBoard, int seed, const ChessBoard::MoveData& inMoveData);
	bool GetRandomMove(char *input, ChessBoard::Board &gameBoard, int seed, const ChessBoard::MoveData& inMoveData);
	
	ChessBoard::Piece::color myColor;

};

