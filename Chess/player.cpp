#include "player.h"

#include <iostream>


Player::Player()
{
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
bool Player::GetNextMove(char input[32])
{
	std::cout << std::endl << "Enter your move: ";
	std::cin.clear();
	std::cin.sync();
	std::cin.getline(input, 32, '\n');


	if (!strcmp(input, "q") && ConfirmQuit())
	{
		return false;
	}

	return true;
}
