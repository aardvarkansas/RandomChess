#include "player.h"

#include <iostream>


Player::Player()
{
	isHuman = true;
}

Player::Player(bool isHuman)
{
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
bool Player::GetNextMove(char input[32])
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
		GetRandomMove(input);
		return true;
	}

	return true;
}

bool Player::GetRandomMove(char *input)
{
	for (int i = 0; i < sizeof(input) / sizeof(char); i++)
		input[i] = '\0';
	char * my_input = { "48 40" };
	strcat_s(input,32,my_input);
	return true;
}
