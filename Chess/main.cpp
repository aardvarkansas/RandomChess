//
//  main.cpp
//  Chess
//
//  Created by Me on 1/8/17.
//  Copyright (c) 2017 User. All rights reserved.
//

#include <assert.h>
#include <bitset>
#include <deque>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>
#include <exception>
#include <stdexcept>
#include <utility>
#include "player.h"
#include "game.h"
#include "board.h"

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

int test_main(int argc, const char* argv[])
{
    
        ChessBoard::Board* myBoard = new ChessBoard::Board();
        myBoard->StartGame();
        myBoard->PrintBoard();
        myBoard->Move(11, 18);
        
        delete myBoard;
    
    return 0;
}
int main(int argc, const char * argv[])
{
    Game myGame;
   
    std::cout << "\n";
    
	myGame.StartGame();
    
	myGame.PrintBoard();

    // vector of pairs with start and destination
	std::deque<std::pair<short, short>> movesFromFile;

    short origin, destination;

    if (argc > 1)
    {
        std::filesystem::path p{ argv[1] };   // create a path from the command line
        std::cout << p << " " << exists(p) << '\n';    // note: a path can be printed like a string     // ...
        std::ifstream fs{ p };

        assert(exists(p));
        size_t count = 0;
        while (true)
        {
            std::pair<short,short> nextMove;
            fs >> nextMove.first >> nextMove.second;

            std::cout << "Move: " << (count++) << std::setw(10) << 
                "start: " << nextMove.first <<
                " destination: " << nextMove.second
                << std::endl;
            movesFromFile.push_back(nextMove);
            if (fs.eof()) break;
        }
    }
	
	std::string seps = R"( ,\t\n)";

	char *token1;

    Player* myPlayer_orange = new Player(ChessBoard::Piece::color::orange, true);
    Player* myPlayer_purple = new Player(ChessBoard::Piece::color::purple, true);

	
    while (1 == 1)
    {
        try
        {

            char input[sizeof(char) * 32];

            ClearBuffer(input);

            if (myGame.WhoseMove() == ChessBoard::Piece::color::purple)
            {
                if (!movesFromFile.empty())
                {
                    myPlayer_purple->GetNextMove(input, myGame.myBoard, movesFromFile);
                }
                else if (!myPlayer_purple->GetNextMove(input, myGame.myBoard, movesFromFile))
                    return 0; // Quit the game if the next move function returns false.
            }
            else
            {
                if (!myPlayer_orange->GetNextMove(input, myGame.myBoard, movesFromFile))
                    return 0; // Quit the game if the next move function returns false.
            }

            // this is a flag made necessary because calling continue in the nested if statement below
            // doesn't continue the while statement above, and causes an assert fail for the string 
            // processing of the move numbers from std input
            /*bool continue_flag = false;



            // check to see if we should continue
            if (continue_flag)
            {
                ClearBuffer(input);
                continue;
            }*/

            try
            {
                std::regex pat{ R"(\d\d?)" };
                char* next_token;

                std::cout << "input: " << input << std::endl;

                if (input[0] == '\0')
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
                else
                {
                    // I think this strtok uses NULL because it is just getting the next item in the
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
                myGame.PrintMoves();
                myGame.PrintBoard();
            }
            else {
                std::cin.clear();
                std::cin.ignore(10, '\n');
            }
        }

        catch (std::exception& e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
            break;
        }


        //if (myGame.myBoard.theMoves.size() > 99) exit(0);
    }
    

	myGame.PrintMoves();
    
    
    return 0;
}

