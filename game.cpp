#include "game.h"


Game::Game()
{
}


Game::~Game()
{
}



ChessBoard::Piece::color Game::WhoseMove()
{
	return this->myBoard.WhoseMove();
}


void Game::StartGame()
{
	this->myBoard.StartGame();
}

void Game::PrintBoard()
{
	this->myBoard.PrintBoard();
}
void Game::PrintMoves()
{
	this->myBoard.PrintMoves();
}
bool Game::Move(const int start, const int destination)
{
	return this->myBoard.Move(start,destination);
}

