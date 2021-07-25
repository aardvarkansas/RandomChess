#include "player.h"
#include "board.h"
#include <ctime>
#include <cstring>

#include <deque>
#include <string>
#include <random>
#include <vector>
#include <iostream>

Player::Player()
{

}

Player::Player(ChessBoard::Piece::color myColor, bool isHuman)
{
	this->myColor = myColor;
	this->isHuman = isHuman;
}


Player::~Player()
{
}


bool ConfirmQuit()
{
	std::cout << "Quitting? Press y to quit, n to continue: ";
	char quit_char;
	std::cin.get(quit_char);
	if (quit_char == 'y')
	{
		return true;
	}
	else{
		return false;
	}

}

std::pair<short, short> Player::GetNextMove(ChessBoard::Board &myBoard)
{
	char input[32];
	srand(static_cast<unsigned int>(time(nullptr)));
	seed_for_random_move++;
	return GetRandomMove(myBoard, seed_for_random_move);
}
// If this returns false, that means the player has quit.
bool Player::GetNextMove(std::string& input, ChessBoard::Board &gameBoard, std::deque<std::pair<short, short>> &movesFromFile)
{
	if (!movesFromFile.empty())
	{
		for (int i = 0; i < input.length(); i++)
			input[i] = '\0';
		std::string input_from_file;
		input_from_file.append(std::to_string(movesFromFile.front().first) + ' ' + 
			std::to_string(movesFromFile.front().second));
		movesFromFile.pop_front();

		input =  input_from_file;
	}
	else if (this->isHuman)
	{
		std::string input_from_user;
		std::cerr << std::endl << "Enter your move: ";
		std::cin.clear();
		std::cin.sync();
		std::getline(std::cin, input_from_user);

		if (!input_from_user.compare("q") && ConfirmQuit())
		{
			return false;
		}

		input = input_from_user;
	}

	else // it's an NPC
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		seed_for_random_move++;
		std::pair<short, short> random_move = GetRandomMove(gameBoard, seed_for_random_move);
		
		input = std::to_string(random_move.first) + ' ' + std::to_string(random_move.second);
		return true;
	}

	return true;
}

std::pair<short,short> Player::GetRandomMove(ChessBoard::Board& gameBoard, int seed)
{
	std::vector<int> list_source(0);
	std::vector<int> list_destination(0);

	std::deque<std::pair<short, short>> myQueue;

	gameBoard.getPossibleMoves(myQueue);

	srand(static_cast<unsigned int>(time(nullptr) / seed));

	std::pair<short, short> nextMove = myQueue.at(rand() % myQueue.size());

	/*
	for (int i = 0; i < 64 ; i++)
	{
		if (gameBoard.theSpaces[i]->currentPiece->myColor == this->myColor)
		{
			list_source.push_back(i);
		}

		// TO DO: Check for castling, and if it's still legal, add one or two options for castling
		/* To check for castling:
			1. No pieces between king and rook.
			2. Neither king nor rook has moved yet.
			3. King will not move out of, through, or into check.

		else list_destination.push_back(i);
	}
	*/

	return nextMove;
}

#if 0
bool Player::GetRandomMove(char *input, ChessBoard::Board &gameBoard, int seed)
{
	std::vector<int> list_source(0);
	std::vector<int> list_destination(0);

	std::deque<std::pair<short, short>> myQueue;

	gameBoard.getPossibleMoves(myQueue);

	srand(static_cast<unsigned int>(time(nullptr) / seed));

	std::pair<short, short> nextMove = myQueue.at(rand() % myQueue.size());

	/*
	for (int i = 0; i < 64 ; i++)
	{
		if (gameBoard.theSpaces[i]->currentPiece->myColor == this->myColor)
		{
			list_source.push_back(i);
		}

		// TO DO: Check for castling, and if it's still legal, add one or two options for castling 
		/* To check for castling: 
			1. No pieces between king and rook.
			2. Neither king nor rook has moved yet.
			3. King will not move out of, through, or into check.
		
		else list_destination.push_back(i);
	}
	
	list_destination.shrink_to_fit();

	
	origin = list_source[(rand() % list_source.size())];
	destination = list_destination[(rand() % list_destination.size())];

	*/
	
	short origin=nextMove.first, destination=nextMove.second;
	
	for (int i = 0; i < sizeof(input) / sizeof(char); i++)
		input[i] = '\0';
	char space[] = { " " };
	char origin_char[3]= { ' ' };
	char destination_char[3] = { ' ' };
	std::string input_to_string;
	input_to_string.append(std::to_string(origin) +  ' ' + std::to_string(destination));

	_itoa_s(origin,origin_char,10);
	_itoa_s(destination, destination_char, 10);
	char my_input[7];
	strcpy_s(my_input, sizeof(origin_char), origin_char);
	strncat_s(my_input, space, sizeof(space));
	strncat_s(my_input, destination_char, 3);
	strcat_s(input,32,my_input);

	return true;
}
#endif
