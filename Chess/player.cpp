#include "player.h"
#include "board.h"
#include <ctime>

#include <random>
#include <vector>
#include <iostream>

Player::Player()
{

}

Player::Player(ChessBoard::Piece::color myColor, bool isHuman)
{
	this->color = myColor;
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

// If this returns false, that means the player has quit.
bool Player::GetNextMove(char input[32], ChessBoard::Board &gameBoard)
{
	if (this->isHuman)
	{
		std::cout << std::endl << "Enter your move: ";
		std::cin.clear();
		std::cin.sync();
		std::cin.getline(input, 32, '\n');


		if (!strcmp(input, "q") && ConfirmQuit())
		{
			return false;
		}
	}

	else // it's an NPC
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		seed_for_random_move++;
		return GetRandomMove(input, gameBoard, seed_for_random_move);
	}

	return true;
}

bool Player::GetRandomMove(char *input, ChessBoard::Board &gameBoard, int seed)
{
	std::vector<int> list_source(0);
	std::vector<int> list_destination(0);

	for (int i = 0; i < 64 ; i++)
	{
		if (gameBoard.theSpaces[i]->currentPiece.myColor == this->color)
		{
			list_source.push_back(i);
		}

		// TO DO: Check for castling, and if it's still legal, add one or two options for castling 
		/* To check for castling: 
			1. No pieces between king and rook.
			2. Neither king nor rook has moved yet.
			3. King will not move out of, through, or into check.
		*/ 
		else list_destination.push_back(i);
	}
	
	list_destination.shrink_to_fit();

	srand(static_cast<unsigned int>(time(nullptr)/seed));
	short origin=-1, destination=-1;
	
	origin = list_source[(rand() % list_source.size())];
	destination = list_destination[(rand() % list_destination.size())];

	for (int i = 0; i < sizeof(input) / sizeof(char); i++)
		input[i] = '\0';
	char space[] = { " " };
	char origin_char[3]= { '  ' };
	char destination_char[3] = { '  ' };
	_itoa_s(origin,origin_char,10);
	_itoa_s(destination, destination_char, 10);
	char my_input[7];
	strcpy_s(my_input, sizeof(origin_char), origin_char);
	strncat_s(my_input, space, sizeof(space));
	strncat_s(my_input, destination_char, 3);
	strcat_s(input,32,my_input);
	return true;
}
