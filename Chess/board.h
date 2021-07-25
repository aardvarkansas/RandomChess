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
#include <deque>
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
    
    
    // to do typedef and make a return value for validate move
    enum moveErrorCodes : short {
        SUCCESS = 0,
        CASTLE = 1,
        WRONG_TEAM = 2,
        ILLEGAL_MOVE = 3,
        SAME_TEAM = 4,
        EMPTY_SPACE = 5,
        CASTLE_OUT_OF_CHECK = 6,
        MOVING_INTO_CHECK = 7,
        CANT_TAKE_KING = 8,
        CHECK_MATE = 9,
        PAWN_TRADE=10,
    };

    using MoveData = struct {
        moveErrorCodes moveStatus;
        std::vector<std::pair<short, short>> enPassantMoves; 
    };
    
    class Piece
    {
    public:
        bool hasMoved = false; // indicates whether the piece has moved already in the game.
        enum struct color: short {
            none = 0,
            purple = 1,
            orange = 2,
        };
        enum struct pieceType: short {
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

    enum spaceRelativePosition : short
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

        friend class Board;
        
        
        void InitializeAdjacentSpaces();
        void GetAdjacentSpaces(Space *theSpaces);
        void GetLSpaces(Space *theSpaces);
        Space & operator= (const Space &mySpace);

        //Space & operator= (const Space &&mySpace);
        Piece *currentPiece;
        
        short spaceID=-1;
        
    };
    
    class Board
    {

	private:
		Piece::color whoseMove = Piece::color::orange;

    public:
        Space* theSpaces[64];

        std::vector<std::string> theMoves;

        Board();
        Board(const Board& rhs);
        ~Board();
        void StartGame(Piece::color startWhoseMove = Piece::color::orange);
        void PrintBoard();
        void PrintMoves();
        void ImportJSON(std::string& in_board_array);
        void ExportJSON(std::string& out_board_array);

        std::unordered_map<std::string, ChessBoard::moveErrorCodes> movesAttempted;

        std::string PurpleOrOrange(const int spaceID);
		Piece::color WhoseMove();
        moveErrorCodes Move(const short start, const short destination, MoveData& outMoveData,
            const Piece::pieceType pawn_trade_piece = Piece::pieceType::queen);
        bool IsInCheck(const Piece::color king_color, const ChessBoard::Board &changedState);
        bool IsCheckMate(const Piece::color king_color, ChessBoard::Board& changedState);
		bool IsSameTeam(const int start, const int destination);
        void getPossibleMoves(std::deque<std::pair<short, short>>& moveQueue);
        void findAvailableMoves(
            std::deque<std::pair<short, short>>& newMoves, 
            std::vector<short>& directionalIncrement,
            const short theOrigin,
            bool isKing = false);
        ChessBoard::moveErrorCodes ValidateMove(const int start, const int destination, MoveData& outMoveData);
        ChessBoard::Board& proposeChange(ChessBoard::Board &changedState, const int start, const int destination);

		
        std::string GetPieceName(Piece::pieceType);
        
        
    };
    

}