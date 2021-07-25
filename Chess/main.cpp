//
//  main.cpp
//  Chess
//
//  Created by Me on 1/8/17.
//  Copyright (c) 2017 User. All rights reserved.
//
/*
#include <assert.h>
#include <bitset>
#include <deque>
#include <fstream>*/
#include <iostream>
//#include <filesystem>
#include <vector>
#include <regex>
#include <exception>
#include <stdexcept>
#include <utility>
#include "player.h"
#include "game.h"
#include "board.h"

#if _MSC_VER > 1600
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#endif

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

int old_main(int argc, const char* argv[])
{
    if (argc > 1)
    {
        Game* myGame = new Game();
        myGame->StartGame(ChessBoard::Piece::color::purple);
        
        short argOrigin = atoi(argv[1]);

        short argDestination = atoi(argv[2]);

        std::string in_board_array;

        if (argc > 3) in_board_array = argv[3];
        
        myGame->myBoard.ImportJSON(in_board_array);

        Player* myPlayer_orange = new Player(ChessBoard::Piece::color::orange, false);
        Player* myPlayer_purple = new Player(ChessBoard::Piece::color::purple, true);
        
        ChessBoard::MoveData outMoveData;
        ChessBoard::moveErrorCodes ret_value = myGame->myBoard.Move(argOrigin, argDestination, outMoveData);

        std::string out_board_array;

        if (!ret_value == ChessBoard::moveErrorCodes::SUCCESS)
        {
            myGame->myBoard.ExportJSON(out_board_array);
            std::cout << out_board_array;

            std::cerr << "Error: " << ret_value << std::endl;
            delete myGame;
            return ret_value;
        }
        
        std::pair<short, short> npc_move;
        int movesAttempted = 0;
        do
        {
            ChessBoard::MoveData outMoveData;
            npc_move = myPlayer_orange->GetNextMove(myGame->myBoard);
            ret_value = myGame->myBoard.Move(npc_move.first, npc_move.second, outMoveData);
            movesAttempted++;
        } while (!ret_value == ChessBoard::moveErrorCodes::SUCCESS && movesAttempted<200);

        myGame->myBoard.ExportJSON(out_board_array);
        out_board_array.append("," + std::to_string(npc_move.first) + "," + std::to_string(npc_move.second));
        std::cout << out_board_array;

        delete myGame;

        return ret_value;
    }

    else return -1;
}

// This main function relies on MSFT libraries.
#if _MSC_VER > 1600
int main(int argc, const char * argv[])
{
    // C:\temp\chess\moves.txt

    Game myGame;
   
    std::cout << "\n";
    
	myGame.StartGame(ChessBoard::Piece::color::purple);
    
    
    myGame.myBoard.ImportJSON(std::string("0,0,0,0,2,3,0,2,2,0,0,0,0,0,0,0,2,2,1,2,5,0,0,0,1,2,4,0,0,0,0,0,0,0,2,1,0,2,1,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,1,0,0,1,1,3,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,2,6,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,4,0,1,3,0,1,2,0,1,6,0,0,0,0,1,2,1,0,0,0,1,4"));

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

            std::string input;

            input.clear();

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

                std::cout << "input: " << input << std::endl;

                if (input[0] == '\0')
                {
                    std::cout << "Bad input.";
                    continue;
                }

                std::string first_input = input.substr(0,input.find(' '));
                if (!std::regex_match(first_input, pat))
                {
                    std::cout << "Bad inpoot.";
                    continue;
                }
                origin = atoi(first_input.c_str());

                std::cout << "origin: " << origin << std::endl;

                std::string next_token = input.substr(input.find(' ')+1, input.length());
                if (next_token[0] == '\0' || !std::regex_match(next_token, pat))
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
                        destination = atoi(next_token.c_str());

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
                ChessBoard::MoveData outMoveData;
                myGame.Move(origin, destination, outMoveData);
                myGame.PrintMoves();
                myGame.PrintBoard();
                std::string export_board;
                myGame.myBoard.ExportJSON(export_board);
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

#endif

