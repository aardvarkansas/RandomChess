//
//  board.h
//  Chess
//
//  Created by User on 1/8/17.
//  Copyright (c) 2017 User. All rights reserved.
//
#pragma once

#ifndef __Chess__board__
#define __Chess__board__

#include <iostream>
#include <vector>
#include <unordered_map>

#define NUM_SPACES 64

#endif /* defined(__Chess__board__) */


namespace ChessBoard
{
    /*class Move
    {
    public:
        
        Move();
        Move (int start, int destination)
        {
            this->start = start;
            this->destination = destination;
        }
        ~Move();
        
    private:
        int start;
        int destination;
    };*/
    
    

    
    class Piece
    {
    public:
        bool hasMoved = false; // indicates whether the piece has moved already in the game.
        enum class color {
            none = 0,
            purple = 1,
            orange = 2,
        };
        enum class pieceType {
            empty = 0,
            pawn = 1,
            bishop = 2,
            knight = 3,
            rook = 4,
            king = 5,
            queen = 6
        };
        
        Piece();
        Piece(Piece & myPiece);
        Piece(pieceType myType, color myColor);
        ~Piece();
        
        color myColor;
        pieceType myType;
        
        Piece & operator= (const Piece &myPiece);
        
    };

    enum spaceRelativePosition
    {
        up=0,
        upRight=1,
        right=2,
        downRight = 3,
        down=4,
        downLeft=5,
        left=6,
        upLeft=7
    };

    class Space
    {
    public:
        Space();
        ~Space();
        
        
        void InitializeAdjacentSpaces();
        void GetAdjacentSpaces(Space *theSpaces);
        void GetLSpaces(Space *theSpaces);
        Space & operator= (const Space &mySpace);

        //Space & operator= (const Space &&mySpace);
        Piece *currentPiece = new Piece();
        
        short spaceID=-1;
        
    };
    
    class Board
    {

	private:
		Piece::color whoseMove = Piece::color::purple;

        std::unordered_map<std::string, int> movesAttempted;
    public:
        Space* theSpaces[64];

        std::vector<std::string> theMoves;

        Board();
        Board(const Board& rhs);
        ~Board();
        void StartGame();
        void PrintBoard();
        void PrintMoves();
        std::string PurpleOrOrange(const int spaceID);
		Piece::color WhoseMove();
        bool Move(const int start, const int destination);
        bool IsInCheck(Piece::color king_color, ChessBoard::Board &changedState);
		bool IsSameTeam(int start, int destination);
		int ValidateMove(const int start, const int destination);
        ChessBoard::Board& proposeChange(ChessBoard::Board &changedState, const int start, const int destination);

		// to do typedef and make a return value for validate move
		inline enum moveErrorCodes {
			SUCCESS = 0,
			WRONG_TEAM = 1,
			ILLEGAL_MOVE = 2,
			SAME_TEAM = 3,
			EMPTY_SPACE = 4,
            MOVING_INTO_CHECK =5
		};
        std::string GetPieceName(Piece::pieceType);
        
        
    };
    

}