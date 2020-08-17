//
//  main.cpp
//  Chess
//
//  Created by Me on 1/8/17.
//  Copyright (c) 2017 User. All rights reserved.
//

#include <bitset>
#include <iostream>
#include <vector>
#include <regex>
#include <exception>
#include <stdexcept>
#include "player.h"
#include "game.h"

bool ClearBuffer(char *input)
{
	try
	{
		std::cin.clear();
		for (int i = 0; i < sizeof(input) / sizeof(char); i++)
		input[i] = '\0';
	}
	catch (std::exception)
	{
		return false;
	}

	return true;
}

int main(int argc, const char * argv[])
{
    
	Game myGame;
   
    std::cout << "\n";
    
	myGame.StartGame();
    
	myGame.PrintBoard();

	int origin=0, destination;
	

	std::string seps = R"( ,\t\n)";

	char *token1;

    Player* myPlayer_orange = new Player(ChessBoard::Piece::color::orange, true);
    Player* myPlayer_purple = new Player(ChessBoard::Piece::color::purple, false);

	
	while (1==1)
	{
		try
		{
			
			char input[sizeof(char)*32];

			ClearBuffer(input);
			
			if (myGame.WhoseMove() == ChessBoard::Piece::color::purple)
			{
				if (!myPlayer_purple->GetNextMove(input, myGame.myBoard))
					return 0; // Quit the game if the next move function returns false.
			}
			else
			{
				if (!myPlayer_orange->GetNextMove(input, myGame.myBoard))
					return 0; // Quit the game if the next move function returns false.
			}

			
			// this is a flag made necessary because calling continue in the nested if statement below
			// doesn't continue the while statement above, and causes an assert fail for the string 
			// processing of the move numbers from std input
			bool continue_flag = false;

			

			// check to see if we should continue
			if (continue_flag)
			{
				ClearBuffer(input);
				continue;
			}


			try
			{
				std::regex pat{ R"(\d\d?)" };
				char *next_token;

				std::cout << "input: " << input << std::endl;

				if (input[0]=='\0')
				{
					std::cout << "Bad input.";
					continue;
				}

				std::string first_input = strtok_s(input, seps.c_str(), &next_token);
				if (!std::regex_match(first_input, pat))
				{
					std::cout << "Bad inpoot.";
					continue;
				}
				origin = atoi(first_input.c_str());

				std::cout << "origin: " << origin << std::endl;

				if (*next_token == '\0' || !std::regex_match(next_token, pat))
				{
					std::cout << "Bad input.";
					continue;
				}
				else{
					// I think this is NULL because it is just getting the next item in the
					// the input string
					try
					{

						destination = atoi(strtok_s(NULL, seps.c_str(), &next_token));

						std::cout << "destination: " << destination << std::endl;
					}
					catch (std::exception input_exception)
					{
						std::cout << "Bad input!" << input_exception.what();
						continue;
					}

				}
			}
			catch (std::exception input_exception)
			{
				std::cout << "Bad input.";
				continue;
			}

			if (!std::cin.fail())
			{
				std::cout << std::endl << origin << " " << destination;
				myGame.Move(origin, destination);
				myGame.PrintBoard();
			}
			else {
				std::cin.clear();
				std::cin.ignore(10, '\n');
			}
		}

		catch (std::exception &e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
			break;
		}
	}


	/*
    
    myBoard.Move(9,17);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    
    myBoard.Move(62,45);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    
    
    myBoard.Move(8,24);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
     myBoard.Move(51,35);
    
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    myBoard.Move(10,26);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();

    myBoard.Move(35,26);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    myBoard.Move(17,26);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();

    myBoard.Move(57,40);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
   
    
    myBoard.Move(2,9);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    
    myBoard.Move(56,57);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();

    myBoard.Move(9,16);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    
    myBoard.Move(3,17);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    

    myBoard.Move(60,51);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    
    myBoard.Move(4,3);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();

    myBoard.Move(51,43);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    myBoard.Move(3,10);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();

    myBoard.Move(43,34);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();

    
    myBoard.Move(10,19);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    myBoard.Move(34,35);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    myBoard.Move(19,20);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    myBoard.Move(35,37);
    
    std::cout << "\n\n\n";
    
    myBoard.PrintBoard();
    
    std::cout << "\n\n\n\n\n";
    */

	myGame.PrintMoves();
    
    
    char myChar;
    std::cin >> myChar;
    
	std::cout << myChar;
    

    return 0;
}

