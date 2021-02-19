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

	char* GetNextMove();

	bool GetRandomMove(char *input, ChessBoard::Board &gameBoard, int seed);
	bool GetNextMove(char input[32], ChessBoard::Board &gameBoard, std::deque<std::pair<short,short>> &movesFromFile);
	
	ChessBoard::Piece::color myColor;

};

