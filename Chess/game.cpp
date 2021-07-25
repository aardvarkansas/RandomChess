#include "game.h"
#include "board.h"


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


void Game::StartGame(ChessBoard::Piece::color startWhoseMove)
{
	this->myBoard.StartGame(startWhoseMove);
}

void Game::PrintBoard()
{
	this->myBoard.PrintBoard();
}
void Game::PrintMoves()
{
	this->myBoard.PrintMoves();
}
ChessBoard::moveErrorCodes Game::Move(const int start, const int destination, ChessBoard::MoveData& outMoveData)
{
	return this->myBoard.Move(start, destination, outMoveData);
}

