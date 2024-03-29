﻿//
//  main.cpp
//  Chess
//
//  Created by Me on 1/8/17.
//  Copyright (c) 2017 User. All rights reserved.
//
/*
#include <assert.h>
#include <bitset>

#include <fstream>*/
#include <iostream>
#include <iomanip>
//#include <filesystem>
#include <vector>
#include <deque>
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

        Player* myPlayer_orange = new Player(ChessBoard::Piece::color::orange, true);
        Player* myPlayer_purple = new Player(ChessBoard::Piece::color::purple, true);
        
        ChessBoard::MoveData outMoveData;
        ChessBoard::MoveData inMoveData;
        ChessBoard::moveErrorCodes ret_value = 
            myGame->myBoard.Move(argOrigin, argDestination, inMoveData, outMoveData);

        std::string out_board_array;
        std::string out_en_passant_moves;

        if (!ret_value == ChessBoard::moveErrorCodes::SUCCESS)
        {
            myGame->myBoard.ExportJSON(out_board_array, inMoveData);
            short i = 0;
            std::string comma = "";
            for (std::pair<short, short>& myEnPassantMove : outMoveData.enPassantMoves)
            {
                if (i == 1) comma = ',';
                out_en_passant_moves += comma + std::to_string(myEnPassantMove.first) 
                    + ',' + std::to_string(myEnPassantMove.second);
                i++;
            }
            std::cout << out_board_array << " \n\nenPassant: " << out_en_passant_moves;

            std::cerr << "Error: " << ret_value << std::endl;
            delete myGame;
            return ret_value;
        }

        // If you get to this point, then the move was successful and it's time to get
        // an NPC move. Change the out data from the recently completed move from "out"
        // data to "in" data for the upcoming NPC move.

        std::pair<short, short> npc_move;
        int movesAttempted = 0;

        ChessBoard::MoveData npc_outMoveData;
        ChessBoard::MoveData npc_inMoveData;

        npc_inMoveData.enPassantMoves = outMoveData.enPassantMoves;
        npc_inMoveData.spacesToDraw = outMoveData.spacesToDraw;
        inMoveData.enPassantMoves = outMoveData.enPassantMoves;
        do
        {
            npc_move = myPlayer_orange->GetNextMove(myGame->myBoard, npc_inMoveData);
            ret_value = myGame->myBoard.Move(
                npc_move.first, 
                npc_move.second, 
                npc_inMoveData, 
                npc_outMoveData
            );
            movesAttempted++;
        } while (!ret_value == ChessBoard::moveErrorCodes::SUCCESS && movesAttempted<200);

        myGame->myBoard.ExportJSON(out_board_array, npc_inMoveData);
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
    
    //myGame.myBoard.ImportJSON(std::string("0,2,4,0,2,3,0,2,2,0,2,6,0,2,5,0,2,2,0,2,3,0,2,4,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,4,0,1,3,0,1,2,0,1,6,0,1,5,0,1,2,0,1,3,0,1,4"));
    // myGame.myBoard.ImportJSON(std::string("0,2,4,0,2,3,0,2,2,0,0,0,0,2,5,0,2,2,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,2,1,0,2,1,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,1,0,0,1,1,3,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,2,6,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,4,0,1,3,0,1,2,0,1,6,0,1,5,0,1,2,1,0,0,0,1,4"));

    //castling through pawn check
    // myGame.myBoard.ImportJSON(std::string("0,2,4,0,2,3,0,2,2,0,2,6,0,2,5,0,0,0,0,2,3,0,2,4,0,2,1,0,0,0,0,2,1,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1,2,1,0,0,0,1,1,1,0,0,0,1,2,1,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3,0,0,0,1,1,1,1,1,1,0,0,0,1,1,2,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,1,1,6,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,4,0,0,0,0,0,0,0,0,0,0,1,5,0,1,2,0,1,3,0,1,4"));
    
    // weird stalemate
    myGame.myBoard.ImportJSON(std::string("1,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,0,2,4,0,0,0,1,2,5,1,2,6,0,2,1,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,1,2,1,1,1,1,1,2,3,1,2,1,1,1,1,0,0,0,1,1,3,0,0,0,1,2,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,2,1,1,1,4,0,0,0,1,1,2,0,0,0,0,0,0,0,0,0,1,1,6,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,4,0,0,0,0,0,0,0,0,0,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0"));
    // stalemate
//    myGame.myBoard.ImportJSON(std::string("0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0"));
//    myGame.myBoard.ImportJSON(std::string("0,2,4,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,1,0,0,1,2,5,0,2,1,0,0,0,0,2,1,0,0,0,0,0,0,1,1,6,0,0,0,0,0,0,0,0,0,1,2,3,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,2,1,0,0,0,1,2,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,2,6,0,1,1,0,1,4,0,1,3,0,1,2,0,0,0,0,1,5,0,1,2,0,0,0,0,0,0,63,54"));
    //myGame.myBoard.ImportJSON(std::string("0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3,0,0,0,0,0,0,0,0,0,1,1,6,0,0,0,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25"));
    // myGame.myBoard.ImportJSON(std::string("0,0,0,1,0,0,0,0,0,0,0,0,1,2,5,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,2,3,0,0,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1,6,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,2,1,2,1,1,1,3,0,0,0,1,1,6,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,4,0,0,0,0,0,0,0,0,0,0,1,5,0,0,0,1,1,4,1,0,0"));

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


    ChessBoard::MoveData inMoveData;

    while (1 == 1)
    {
        inMoveData.spacesToDraw.clear();
        try
        {

            std::string input;

            input.clear();

            if (myGame.WhoseMove() == ChessBoard::Piece::color::purple)
            {
                if (!movesFromFile.empty())
                {
                    myPlayer_purple->GetNextMove(input, myGame.myBoard, movesFromFile, inMoveData);
                }
                else if (!myPlayer_purple->GetNextMove(input, myGame.myBoard, movesFromFile, inMoveData))
                    return 0; // Quit the game if the next move function returns false.
            }
            else
            {
                if (!myPlayer_orange->GetNextMove(input, myGame.myBoard, movesFromFile, inMoveData))
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

                // std::cout << "input: " << input << std::endl;

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

                std::cout << "\n\norigin: " << origin << std::endl;

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
                std::string out_en_passant_moves;
                std::cout << std::endl << origin << " " << destination;
                ChessBoard::MoveData outMoveData;
                
                ChessBoard::moveErrorCodes ret_value = myGame.Move(origin, destination, inMoveData, outMoveData);
                short i = 0;
                std::string comma = "";
                for (std::pair<short, short>& myEnPassantMove : outMoveData.enPassantMoves)
                {
                    if (i == 1) comma = ',';
                    out_en_passant_moves += comma + std::to_string(myEnPassantMove.first) 
                        + ',' + std::to_string(myEnPassantMove.second);
                    i++;
                }
                // std::cout << "\n\nenPassant: " << out_en_passant_moves;
                myGame.PrintMoves();
                myGame.PrintBoard();
                std::string export_board;
                myGame.myBoard.ExportJSON(export_board, outMoveData);
                inMoveData = outMoveData;
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

