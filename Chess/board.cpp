//
//  board.cpp
//  Chess
//
//  Created by User on 1/8/17.
//  Copyright (c) 2017 User. All rights reserved.
//

#include "board.h"
#include <algorithm>
#include <deque>
#include <iomanip>
#include <iterator>
#include <regex>
#include <string>
#include <locale>
#include <cctype>
#include <cmath>


ChessBoard::Piece::Piece()
{
    myType = ChessBoard::Piece::pieceType::empty;
    myColor = ChessBoard::Piece::color::none;
    //do nothing
}
ChessBoard::Piece & ChessBoard::Piece::operator= (const Piece &myPiece)
{
    this->myType = myPiece.myType;
    this->myColor = myPiece.myColor;
    return *this;
}
ChessBoard::Piece::Piece(Piece &myPiece)
{
    this->myType = myPiece.myType;
    this->myColor = myPiece.myColor;
}
ChessBoard::Piece::Piece(Piece::pieceType myType, Piece::color myColor)
{
    this->myType = myType;
    this->myColor = myColor;
}

ChessBoard::Piece::~Piece()
{
    //do nothing
}

/* future move operator, may not be necessary or useful
 Piece & Piece::operator= (const Piece &&myPiece)
 {
 if (this != &myPiece)
 {
 free();
 }
 
 return *this;
 }
*/
ChessBoard::Space::Space() {    
    currentPiece = new Piece();
};
    
ChessBoard::Space::~Space()
{
    delete currentPiece;
    //spaceID = NULL;
}

ChessBoard::Space & ChessBoard::Space::operator= (const Space &mySpace)
{
    this->spaceID = mySpace.spaceID;
    this->currentPiece = mySpace.currentPiece;
    return *this;
}

/* future move operator, may not be necessary or useful
ChessBoard::Space & ChessBoard::Space::operator= (const Space &&mySpace)
{
    if (this != &mySpace)
    {
        free();
    }
    
    return *this;
}
 */

void ChessBoard::Space::GetLSpaces(Space theLSpaces[8])
{
    
    for (size_t i=0;i<8;i++)
    {
		theLSpaces[i].spaceID = -1;
    }
    
    // up two, left one
	if ((this->spaceID - 17) >= 0 && (this->spaceID % 8)>0) theLSpaces[0].spaceID = this->spaceID - 17;
    
    // up one, left two 
	if ((this->spaceID - 10) >= 0 && (this->spaceID % 8)>1) theLSpaces[1].spaceID = this->spaceID - 10;
    
    // up two, right one
	if ((this->spaceID - 15) >= 0 && (this->spaceID % 8) < 7) theLSpaces[2].spaceID = this->spaceID - 15;
    
	// up one, right two
	// can't be in bottom row, or rightmost two columns
	if ((this->spaceID - 8) >= 0 && (this->spaceID % 8) < 6) theLSpaces[3].spaceID = this->spaceID - 6;

	// down one, right two
	// can't be in bottom row, or rightmost two columns
	if ((this->spaceID + 10) <= 63 && (this->spaceID % 8) < 6) theLSpaces[4].spaceID = this->spaceID + 10;
	
	// down one, left two
	// can't be in bottom row, or leftmost two columns
	if ((this->spaceID + 6) <= 63 && (this->spaceID % 8) > 1) theLSpaces[5].spaceID = this->spaceID + 6;

	// down two, right one
	// can't be in bottom two rows, or leftmost column
	if ((this->spaceID + 17) <= 63 && (this->spaceID % 8) < 7) theLSpaces[6].spaceID = this->spaceID + 17;

	// down two, left one
	// can't be in bottom two rows, or rightmost column
	if ((this->spaceID + 15) <= 63 && (this->spaceID % 8) > 0) theLSpaces[7].spaceID = this->spaceID + 15;

}


void ChessBoard::Space::GetAdjacentSpaces(Space *theSpaces)
{
    
    for (size_t i=0;i<8;i++)
    {
        theSpaces[i].spaceID = -1;
    }
    
    //space directly above this one
    if (this->spaceID > 7) theSpaces[spaceRelativePosition::up].spaceID = this->spaceID - 8;
    
    //above right
    if (this->spaceID > 7 && (this->spaceID%8) < 7) theSpaces[spaceRelativePosition::upRight].spaceID = this->spaceID - 7;
    
    //right
    if ((this->spaceID%8) <7) theSpaces[spaceRelativePosition::right].spaceID = this->spaceID + 1;
    
    //below right
    if (this->spaceID < 56 && (this->spaceID%8) < 7) theSpaces[spaceRelativePosition::downRight].spaceID = this->spaceID + 9;
    
    //below
     if (this->spaceID < 56) theSpaces[spaceRelativePosition::down].spaceID = this->spaceID + 8;
    
    //below left
    if (this->spaceID < 56 && (this->spaceID%8) != 0) theSpaces[spaceRelativePosition::downLeft].spaceID = this->spaceID + 7;
    
    //left
     if ((this->spaceID%8) != 0) theSpaces[spaceRelativePosition::left].spaceID = this->spaceID - 1;
    
    //above left
    if (this->spaceID > 7 && (this->spaceID%8) != 0) theSpaces[spaceRelativePosition::upLeft].spaceID = this->spaceID - 9;
    
}
    
void ChessBoard::Space::InitializeAdjacentSpaces()
    {
        for (size_t i=0;i<8;++i)
        {
           // this->adjacentSpaces[i] = new Space;
           // this->adjacentSpaces[i]->spaceID = -1;
        }
    }


ChessBoard::Board::Board()
{
    //std::cerr << "initializing board";

    theMoves.reserve(10);
    
    for (auto i=0;i<NUM_SPACES;++i)
    {
        //theSpaces[i].InitializeAdjacentSpaces();
        theSpaces[i] = new Space();
        theSpaces[i]->spaceID = i;
        char newLine = '\n';
        if (i%8 != 0) newLine = ' ';
      //  std::cerr <<  newLine << std::setw(4) << theSpaces[i]->spaceID;
    }

    //std::cerr <<  std::endl;


    this->theSpaces[0]->currentPiece->myColor = Piece::color::orange;
    this->theSpaces[0]->currentPiece->myType = Piece::pieceType::rook;
    this->theSpaces[1]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[1]->currentPiece->myType = Piece::pieceType::knight;
    this->theSpaces[2]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[2]->currentPiece->myType = Piece::pieceType::bishop;
    this->theSpaces[3]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[3]->currentPiece->myType = Piece::pieceType::queen;
    this->theSpaces[4]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[4]->currentPiece->myType = Piece::pieceType::king;
    this->theSpaces[5]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[5]->currentPiece->myType = Piece::pieceType::bishop;
    this->theSpaces[6]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[6]->currentPiece->myType = Piece::pieceType::knight;
    this->theSpaces[7]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[7]->currentPiece->myType = Piece::pieceType::rook;
    this->theSpaces[8]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[8]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[9]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[9]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[10]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[10]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[11]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[11]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[12]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[12]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[13]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[13]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[14]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[14]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[15]->currentPiece->myColor = Piece::color::orange;
	this->theSpaces[15]->currentPiece->myType = Piece::pieceType::pawn;

    for (size_t i = 16; i < 48; ++i)
    {
        this->theSpaces[i]->currentPiece->myColor = Piece::color::none;
	    this->theSpaces[i]->currentPiece->myType = Piece::pieceType::empty;
    }


    this->theSpaces[48]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[48]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[49]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[49]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[50]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[50]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[51]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[51]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[52]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[52]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[53]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[53]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[54]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[54]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[55]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[55]->currentPiece->myType = Piece::pieceType::pawn;
    this->theSpaces[56]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[56]->currentPiece->myType = Piece::pieceType::rook;
    this->theSpaces[57]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[57]->currentPiece->myType = Piece::pieceType::knight;
    this->theSpaces[58]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[58]->currentPiece->myType = Piece::pieceType::bishop;
    this->theSpaces[59]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[59]->currentPiece->myType = Piece::pieceType::queen;
    this->theSpaces[60]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[60]->currentPiece->myType = Piece::pieceType::king;
    this->theSpaces[61]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[61]->currentPiece->myType = Piece::pieceType::bishop;
    this->theSpaces[62]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[62]->currentPiece->myType = Piece::pieceType::knight;
    this->theSpaces[63]->currentPiece->myColor = Piece::color::purple;
	this->theSpaces[63]->currentPiece->myType = Piece::pieceType::rook;

}

short getRow(short theSpace)
{
    return (theSpace / 8);
}

short getColumn(short theSpace)
{
    return (theSpace % 8);
}


ChessBoard::Board::~Board()
{
    for (auto i = 0; i < NUM_SPACES; ++i)
    {
        if (theSpaces[i]->currentPiece!=nullptr)
        {
            //delete theSpaces[i]->currentPiece;
        }
       delete theSpaces[i];
    }

    movesAttempted.clear();
   // delete[] theSpaces;
}

ChessBoard::Board::Board(const ChessBoard::Board &rhs)
{
    for (auto i = 0; i < NUM_SPACES; ++i)
    {
        //theSpaces[i].InitializeAdjacentSpaces();
        theSpaces[i] = new Space();
        theSpaces[i]->spaceID = i;
        theSpaces[i]->currentPiece->myType = rhs.theSpaces[i]->currentPiece->myType;
        theSpaces[i]->currentPiece->myColor = rhs.theSpaces[i]->currentPiece->myColor;
    }

    this->movesAttempted = rhs.movesAttempted;


}

// This function is used to print the terminal version of the chess board.
std::string ChessBoard::Board::PurpleOrOrange(const int spaceID)
{
    std::string myType; // type of piece, e.g., bishop pawn rook king queen

	// this routine uppercases the strings for any purple pieces
    if (theSpaces[spaceID]->currentPiece->myColor == Piece::color::purple)
    {
        for (auto &myChar : GetPieceName(theSpaces[spaceID]->currentPiece->myType))
            myType += std::toupper(myChar);
    }
    else myType = GetPieceName(theSpaces[spaceID]->currentPiece->myType);
    
    return myType;
}
void ChessBoard::Board::PrintBoard()
{
	// print space numbers (for debugging gameplay)
	for (int i = 0; i < 64; ++i)
	{
		char newLine = '\n';
		if (i % 8 != 0) newLine = ' ';
		std::cerr << newLine << std::setw(4) << theSpaces[i]->spaceID;
	}

	//std::cerr << " -- -- -- -- " << std::endl;

    for (int i=0;i<64;++i)
    {
        //theSpaces[i].InitializeAdjacentSpaces();
        theSpaces[i]->spaceID = i;
        char newLine = '\n';
        if (i%8 != 0) newLine = ' ';
       
        std::cerr <<  newLine << std::setw(8) << PurpleOrOrange(i);
    }
}

void ChessBoard::Board::ImportJSON(std::string& in_board_array)
{
    std::regex my_pattern("[\\d]+");

    const std::sregex_token_iterator end;
    auto i = 0;
    short space_index = 0;
    for (std::sregex_token_iterator iter(in_board_array.cbegin(), in_board_array.cend(), my_pattern); iter != end; ++iter)
    { 
        if (space_index < 64)
        {
            short my_value = stoi(*iter);
            switch (i % 3)
            {
            case 0:
                this->theSpaces[space_index]->currentPiece->hasMoved = static_cast<bool>(my_value);
                break;
            case 1:
                this->theSpaces[space_index]->currentPiece->myColor = static_cast<ChessBoard::Piece::color>(my_value);
                break;
            case 2:
                this->theSpaces[space_index]->currentPiece->myType = static_cast<ChessBoard::Piece::pieceType>(my_value);
                space_index++;
                break;
            }
        }
        else {
            // skip everything after the pieces for now -- they just communicate possible valid moves
            // We could check to see that the proposed move from the user is within those 
            // but we could also just check through the regular program
        }
        i++;
    }
    
     /*for (int space_index = 0; space_index < 64; space_index++)
    {
        int i = 0;
        while (in_board_array[i]!=',')
        {
        }
    }*/
}

void ChessBoard::Board::ExportJSON(std::string& out_board_array)
{
    std::string my_output;

    for (int i = 0; i < 64; ++i)
    {
        my_output += std::to_string(this->theSpaces[i]->currentPiece->hasMoved) + ",";
        my_output += std::to_string((short)this->theSpaces[i]->currentPiece->myColor) + ",";
        my_output += std::to_string((short)this->theSpaces[i]->currentPiece->myType);
        if (i < 63) my_output += ",";
    }

    std::deque<std::pair<short, short>> moveQueue;
    this->getPossibleMoves(moveQueue);

    for (std::pair<short, short> my_move : moveQueue)
    {
        //my_output += "," + std::to_string(my_move.first) + ","
          //  + std::to_string(my_move.second);
    }

    out_board_array = my_output;
}


void ChessBoard::Board::PrintMoves()
{
    int i(0);
    for (std::string theMove : this->theMoves)
    {
        i++;
        std::cerr << "Move #" << std::to_string(i) << " " << theMove << "\n";
    }
        
}


std::string ChessBoard::Board::GetPieceName(Piece::pieceType thePiece)
{
    switch (thePiece)
    {
    case Piece::pieceType::empty:
            return " - ";
            break;
        case Piece::pieceType::pawn:
            return "pawn";
            break;
        case Piece::pieceType::bishop:
            return "bishop";
            break;
        case Piece::pieceType::knight:
            return "knight";
            break;
        case Piece::pieceType::rook:
            return "rook";
            break;
        case Piece::pieceType::king:
            return "king";
            break;
        case Piece::pieceType::queen:
            return "queen";
            break;
        default:
            return "unknown";
            break;
            
    }
    
}

ChessBoard::moveErrorCodes ChessBoard::Board::Move(const short start, const short destination, 
    MoveData& outMoveData,
    const Piece::pieceType pawn_trade_piece)
{
    std::string startString, destinationString;
    if (start < 10)
    {
        startString = "0" + std::to_string(start);
    }
    else
    {
        startString = std::to_string(start);
    }
    
    if (destination < 10)
    {
        destinationString = "0" + std::to_string(destination);
    }
    else
    {
        destinationString = std::to_string(destination);
    }

    auto moveKey = startString + destinationString;

    if (this->movesAttempted[moveKey] > 0)
    {
        // Return the cached value, no need to go further
        return this->movesAttempted[moveKey];
    }

	int returnCode = ValidateMove(start, destination, outMoveData);

    if (returnCode == SUCCESS || returnCode == CASTLE || returnCode == PAWN_TRADE)
    {
        // clear the per-move buffer of moves attempted
        movesAttempted.clear();

        //std::cerr << std::endl << std::to_string((int)this->theSpaces[destination]->currentPiece->myType) << std::setw(8) << std::to_string((int)this->theSpaces[destination]->currentPiece->myColor);

        std::string capturedPieceString = "";
        if (this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty)
        {
            capturedPieceString = "_x" + PurpleOrOrange(destination);
        }
        Piece* tempPiece = this->theSpaces[destination]->currentPiece;
        tempPiece->myType = Piece::pieceType::empty;
        tempPiece->myColor = Piece::color::none;
        this->theSpaces[destination]->currentPiece = this->theSpaces[start]->currentPiece;
        this->theSpaces[destination]->currentPiece->hasMoved = true;
        this->theSpaces[start]->currentPiece = tempPiece;

        if (returnCode == CASTLE)
        {
            short rook_destination, rook_start;
            switch (destination)
            {
                case 58:
                    rook_destination = 59;
                    rook_start = 56;
                    break;
                case 62:
                    rook_destination = 61;
                    rook_start = 63;
                    break;
                case 2:
                    rook_destination = 3;
                    rook_start = 0;
                    break;
                case 6:
                    rook_destination = 5;
                    rook_start = 7;
                    break;
            }

            Piece* rook_temp = this->theSpaces[rook_destination]->currentPiece;
            rook_temp->myType = Piece::pieceType::empty;
            rook_temp->myColor = Piece::color::none;
            this->theSpaces[rook_destination]->currentPiece = this->theSpaces[rook_start]->currentPiece;
            this->theSpaces[rook_destination]->currentPiece->hasMoved = true;
            this->theSpaces[rook_start]->currentPiece = rook_temp;

        }
        else if (returnCode == PAWN_TRADE)
        {
            this->theSpaces[destination]->currentPiece->myType = Piece::pieceType::queen;
        }

        this->theMoves.push_back(std::to_string(theMoves.size()) + "_" + std::to_string((int)this->theSpaces[destination]->currentPiece->myType) + "_" + std::to_string((int)this->theSpaces[destination]->currentPiece->myColor) + "_" + std::to_string(start) + "_" + std::to_string(destination) + capturedPieceString);

        //switch the move to the other color
        (this->whoseMove == Piece::color::purple) ? this->whoseMove = Piece::color::orange : this->whoseMove = Piece::color::purple;

        // See if this move puts the opposing king in check or check mate.
        if (IsInCheck(this->whoseMove, *this))
        {
            if (IsCheckMate(this->whoseMove, *this))
            {
                this->PrintBoard();
                std::cerr << "check mate!";
                //std::cin.get();
                return CHECK_MATE;
            }
            std::cerr << "\n\n Your king is in check!!!\n\n";
        }

        return SUCCESS;
    }
    
	else
    {
        // Add the move to the hash table for this player's turn
        movesAttempted[moveKey] = (ChessBoard::moveErrorCodes)returnCode;
		
        std::string errorMessage;
		
		switch (returnCode)
		{
			case moveErrorCodes::WRONG_TEAM: errorMessage = "It's not your turn you big ol' goofball!!!";
				break;
			case moveErrorCodes::ILLEGAL_MOVE: errorMessage = "That move is illegal, my friend!!!";
				break;
			case moveErrorCodes::SAME_TEAM: errorMessage = "You can't take your own piece silly goose!!!";
				break;
			case moveErrorCodes::EMPTY_SPACE: errorMessage = "What do you think you're doing? There's no piece there. Please try.";
				break;
            case moveErrorCodes::MOVING_INTO_CHECK: errorMessage = "King is in check my friend. Please don't try that again.";
                break;
            case moveErrorCodes::CANT_TAKE_KING: errorMessage = "You can't take the king, my friend.";
                break;
		}
		std::cerr << "\n\nBAD MOVE, PUNK: " << errorMessage << "\n\n";


        return ChessBoard::moveErrorCodes(returnCode);

    }
}

bool ChessBoard::Board::IsCheckMate(const Piece::color king_color, ChessBoard::Board& changedState)
{
    std::deque<std::pair<short, short>> moveQueue;
        
        changedState.getPossibleMoves(moveQueue);

    for (std::pair<short, short> nextMove : moveQueue)
    {
        ChessBoard::Board* out_possible_move_changed_state = new ChessBoard::Board(changedState);

        proposeChange(*out_possible_move_changed_state, nextMove.first, nextMove.second);
        if (!IsInCheck(this->theSpaces[nextMove.first]->currentPiece->myColor, *out_possible_move_changed_state))
        {
            delete out_possible_move_changed_state;
            return false;
        }

        delete out_possible_move_changed_state;
    }

    return true;
}

bool ChessBoard::Board::IsInCheck(const Piece::color king_color, const ChessBoard::Board &changedState)
{
    //return false;
    bool is_in_check = false;
    int kingSpaceId = -1;

    for (auto i = 0; i < NUM_SPACES; ++i)
    {
        if (changedState.theSpaces[i]->currentPiece->myColor == king_color 
            && changedState.theSpaces[i]->currentPiece->myType == Piece::pieceType::king)
        {
            kingSpaceId = i;
            break;
        }
    }
    // need to check for opposing team's rooks, queens, kings, bishops, knights, and pawns
    for (auto i=0; i < NUM_SPACES; ++i)
    {
        if (changedState.theSpaces[i]->currentPiece->myColor != changedState.theSpaces[kingSpaceId]->currentPiece->myColor
            && changedState.theSpaces[i]->currentPiece->myType != Piece::pieceType::empty)
        {
            switch (changedState.theSpaces[i]->currentPiece->myType)
            {
                case (ChessBoard::Piece::pieceType::pawn):
                {
                    if (changedState.theSpaces[i]->currentPiece->myColor == Piece::color::orange
                        && changedState.theSpaces[kingSpaceId]->currentPiece->myColor == Piece::color::purple)
                    { 
                        // std::cerr << "\n\norange pawn!\n\n\n";
                        if ((i + 7 == kingSpaceId && (getColumn(i) > getColumn(kingSpaceId)))
                            ||
                           (i + 9 == kingSpaceId && (getColumn(i) < getColumn(kingSpaceId))))
                        {
                            // std::cerr << "\n\nKing is in check\n\n";
                            is_in_check = true;
                        }
                    }
                    else if (changedState.theSpaces[i]->currentPiece->myColor == Piece::color::purple &&
                        changedState.theSpaces[kingSpaceId]->currentPiece->myColor == Piece::color::orange)
                    {
                        if ((i - 7 == kingSpaceId && (getColumn(i) < getColumn(kingSpaceId)))
                            ||
                            (i - 9 == kingSpaceId && (getColumn(i) > getColumn(kingSpaceId)))) 
                        {
                            // std::cerr << "\n\nKing is in check\n\n";
                            is_in_check = true;
                        }
                        // std::cerr << "\n\npurple pawn!\n\n\n";
                    }
                     
                    break;
                }
                    
                case (ChessBoard::Piece::pieceType::bishop):
                {
                    // get the minimum value of the spaces
                    auto min_space = std::min(i, kingSpaceId);
                    auto max_space = std::max(i, kingSpaceId);

                    bool is_occluded = false;

                    // find out if the bishop is on a diagonal vector with the opposing king
                    if ((i - kingSpaceId) % 7 == 0 && 
                            (
                                // Check to see if the path wraps around the board, making it invalid
                                // This could probably be more precise, like check to see if the bishop / king's row/columns are exact.
                                (i > kingSpaceId && (getColumn(i) < getColumn(kingSpaceId)))
                                ||
                                (i < kingSpaceId && (getColumn(i) > getColumn(kingSpaceId)))
                            )
                        )
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 7; min_space < max_space; min_space += 7)
                        {
                            if (changedState.theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
                            {
                                is_occluded = true;
                                break;
                            }
                        }

                        // if there's nothing between the bishop and opposing king
                        if (is_occluded == false)
                        {
                            is_in_check = true;
                        }
                    }
                    if ((i - kingSpaceId) % 9 == 0 &&
                        (
                            // This could probably be more precise, like check to see if the bishop / king's row/columns are exact.
                            (i > kingSpaceId && (getColumn(i) > getColumn(kingSpaceId)))
                            ||
                            (i < kingSpaceId && (getColumn(i) < getColumn(kingSpaceId)))
                            )
                        )
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 9; min_space < max_space; min_space += 9)
                        {
                            if (changedState.theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
                            {
                                is_occluded = true;
                                break;
                            }
                        }
                        if (is_occluded == false)
                        {
                            is_in_check = true;
                        }
                    }
                    // std::cerr << "\n\nbishop!\n\n\n";
                    break;
                }
                    
                case (ChessBoard::Piece::pieceType::knight):
                {
                    // std::cerr << "\n\nknight!\n\n\n";

                    Space lSpaces[8];
                    changedState.theSpaces[i]->GetLSpaces(lSpaces);
                    for (auto i = 0; i < 8; i++)
                    {
                        if (lSpaces[i].spaceID == kingSpaceId)
                        {
                            is_in_check = true;
                        }
                    }
                    break;
                }
                    
                case (ChessBoard::Piece::pieceType::rook):
                {
                    // get the minimum value of the spaces
                    auto min_space = std::min(i, kingSpaceId);
                    auto max_space = std::max(i, kingSpaceId);

                    bool is_occluded = false;

                    // if the rook is on the vertical path to the opposing king
                    if ((i - kingSpaceId) % 8 == 0)
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 8; min_space < max_space; min_space += 8)
                        {
                            if (changedState.theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
                            {
                                is_occluded = true;
                                break;
                            }
                        }
                        if (is_occluded == false)
                        {
                            is_in_check = true;
                        }
                    }

                    // are they in the same row?
                    if (floor(i / 8) == floor(kingSpaceId / 8))
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 1; min_space < max_space; min_space++)
                        {
                            if (changedState.theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
                            {
                                is_occluded = true;
                                break;
                            }
                        }
                        if (is_occluded == false)
                        {
                            is_in_check = true;
                        }

                    }
                    // std::cerr << "\n\nrook!\n\n\n";
                    break;
                }
                    
                case (ChessBoard::Piece::pieceType::queen):
                {
                    // get the minimum value of the spaces
                    auto min_space = std::min(i, kingSpaceId);
                    auto max_space = std::max(i, kingSpaceId);

                    bool is_occluded = false;

                    // find out if the queen is on a vector with the king
                     // if the queen is on a diagonal path to the opposing king
                    if ((i - kingSpaceId) % 7 == 0 &&
                        (
                            // This could probably be more precise, like check to see if the bishop / king's row/columns are exact.
                            (i > kingSpaceId && (getColumn(i) < getColumn(kingSpaceId)))
                            ||
                            (i < kingSpaceId && (getColumn(i) > getColumn(kingSpaceId)))
                            )
                        )
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 7; min_space < max_space; min_space += 7)
                        {
                            if (changedState.theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
                            {
                                is_occluded = true;
                                break;
                            }
                        }

                        // if there's nothing between queen and opposing king
                        if (is_occluded == false)
                        {
                            is_in_check = true;
                        }
                    }
                    if ((i - kingSpaceId) % 9 == 0 &&
                        (
                            // This could probably be more precise, like check to see if the bishop / king's row/columns are exact.
                            (i > kingSpaceId && (getColumn(i) > getColumn(kingSpaceId)))
                            ||
                            (i < kingSpaceId && (getColumn(i) < getColumn(kingSpaceId)))
                            )
                        )
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 9; min_space < max_space; min_space += 9)
                        {
                            if (changedState.theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
                            {
                                is_occluded = true;
                                break;
                            }
                        }
                        if (is_occluded == false)
                        {
                            is_in_check = true;
                        }
                    }
                    // if the queen is on the vertical path to the opposing king
                    if ((i - kingSpaceId) % 8 ==0)
                    {
                        // check to see if there are any pieces in between
                        for (min_space+=8; min_space < max_space; min_space += 8)
                        {
                            if (changedState.theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
                            {
                                is_occluded = true;
                                break;
                            }
                        }
                        if (is_occluded == false)
                        {
                            is_in_check = true;
                        }
                    }

                    // are they in the same row?
                    if (floor(i / 8) == floor(kingSpaceId / 8))
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 1; min_space < max_space; min_space++)
                        {
                            if (changedState.theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
                            {
                                is_occluded = true;
                                break;
                            }
                        }
                        if (is_occluded == false)
                        {
                            is_in_check = true;
                        }

                    }

                    // std::cerr << "\n\nqueen!\n\n\n";
                    break;
                }
                case (ChessBoard::Piece::pieceType::king):
                {

                    Space adjacentSpaces[8];

                    // Get the adjacent spaces of the other team's piece (in this case it's the opposing king)
                    changedState.theSpaces[i]->GetAdjacentSpaces(adjacentSpaces);

                    for (auto j=0;j<8;j++)
                    {
                        if (adjacentSpaces[j].spaceID == kingSpaceId)
                        {
                            is_in_check = true;
                        }
                    }

                    // std::cerr << "\n\nking!\n\n\n";
                    break;
                }
            }
        }
        if (is_in_check == true)
        {
            // std::cerr << "\n\n!!!king in check!!!!\n\n\n";
            return true;
        }
    }
    return false;
}

bool ChessBoard::Board::IsSameTeam(const int start, const int destination)
{
	if (this->theSpaces[destination]->currentPiece->myColor == this->theSpaces[start]->currentPiece->myColor) return true;
	else return false;
}

ChessBoard::Board& ChessBoard::Board::proposeChange(ChessBoard::Board &out_changedState, const int start, const int destination)
{

    out_changedState.theSpaces[destination]->currentPiece->myColor = out_changedState.theSpaces[start]->currentPiece->myColor;
    out_changedState.theSpaces[destination]->currentPiece->myType = out_changedState.theSpaces[start]->currentPiece->myType;
    out_changedState.theSpaces[destination]->currentPiece->hasMoved = true;
    out_changedState.theSpaces[start]->currentPiece->hasMoved = true;
    out_changedState.theSpaces[start]->currentPiece->myColor = Piece::color::none;
    out_changedState.theSpaces[start]->currentPiece->myType = Piece::pieceType::empty;


    return out_changedState;
}

void ChessBoard::Board::getPossibleMoves(std::deque<std::pair<short, short>>& moveQueue)
{
    std::vector<int> list_origin(0);
    std::vector<int> list_destination(0);

    for (int i = 0; i < 64; i++)
    {
        if (this->theSpaces[i]->currentPiece->myColor == this->whoseMove)
        {
            list_origin.push_back(i);
        }

        // TO DO: Check for castling, and if it's still legal, add one or two options for castling 
        /* To check for castling:
            1. No pieces between king and rook.
            2. Neither king nor rook has moved yet.
            3. King will not move out of, through, or into check.
        */
    }

    for (auto &elem : list_origin)
    {
        auto theOrigin = (short)elem;
        switch (this->theSpaces[theOrigin]->currentPiece->myType)
        {
            case (Piece::pieceType::pawn):
            {
                // if it's a purple pawn

                if (this->theSpaces[theOrigin]->currentPiece->myColor == Piece::color::purple)
                {
                    if (theOrigin >= 16 && this->theSpaces[theOrigin]->currentPiece->hasMoved == false
                        && this->theSpaces[theOrigin - 16]->currentPiece->myType == Piece::pieceType::empty)
                        moveQueue.push_back(std::pair<short, short>(theOrigin, theOrigin - 16));

                    if (theOrigin>=8 && this->theSpaces[theOrigin - 8]->currentPiece->myType == Piece::pieceType::empty)
                    {
                        moveQueue.push_back(std::pair<short, short>(theOrigin, theOrigin - 8));
                    }
                    if (theOrigin >= 7 && this->theSpaces[theOrigin - 7]->currentPiece->myColor == Piece::color::orange
                        && this->theSpaces[theOrigin - 7]->currentPiece->myType != Piece::pieceType::king)
                    {
                        moveQueue.push_back(std::pair<short, short>(theOrigin, theOrigin - 7));
                    }
                    if (theOrigin >= 9 && this->theSpaces[theOrigin - 9]->currentPiece->myColor == Piece::color::orange
                        && this->theSpaces[theOrigin - 9]->currentPiece->myType != Piece::pieceType::king)
                    {
                        moveQueue.push_back(std::pair<short, short>(theOrigin, theOrigin - 9));
                    }
                }
                //then it's an orange pawn
                else
                {
                    if (theOrigin <= NUM_SPACES-16 
                        && this->theSpaces[theOrigin]->currentPiece->hasMoved == false
                        && this->theSpaces[theOrigin + 16]->currentPiece->myType == Piece::pieceType::empty)
                        moveQueue.push_back(std::pair<short, short>(theOrigin, theOrigin + 16));

                    if (theOrigin <= NUM_SPACES - 8
                        && this->theSpaces[theOrigin + 8]->currentPiece->myType == Piece::pieceType::empty)
                    {
                        moveQueue.push_back(std::pair<short, short>(theOrigin, theOrigin + 8));
                    }
                    if (theOrigin <= NUM_SPACES - 7 && 
                        this->theSpaces[theOrigin + 7]->currentPiece->myColor == Piece::color::purple
                        && this->theSpaces[theOrigin + 7]->currentPiece->myType != Piece::pieceType::king)
                    {
                        moveQueue.push_back(std::pair<short, short>(theOrigin, theOrigin + 7));
                    }
                    if (theOrigin <= NUM_SPACES - 9 &&
                        this->theSpaces[theOrigin + 9]->currentPiece->myColor == Piece::color::purple
                        && this->theSpaces[theOrigin + 9]->currentPiece->myType != Piece::pieceType::king)
                    {
                        moveQueue.push_back(std::pair<short, short>(theOrigin, theOrigin + 9));
                    }
                } //end else
                break;
            }

            case (Piece::pieceType::bishop):
            {
                std::vector<short> directionalIncrement = { -7,7,-9,9 };

                std::deque<std::pair<short, short>> newMoves;

                findAvailableMoves(newMoves, directionalIncrement, theOrigin);

                moveQueue.insert(moveQueue.end(), newMoves.begin(), newMoves.end());

                break; // break case
            }

            case (Piece::pieceType::knight):
            {
                Space lSpaces[8];
                this->theSpaces[theOrigin]->GetLSpaces(lSpaces);
                for (auto &elem : lSpaces)
                {
                    if (elem.spaceID > 0
                        && !IsSameTeam(theOrigin, elem.spaceID)
                        )
                    {
                        moveQueue.push_back(std::pair<short, short>(theOrigin, elem.spaceID));
                    }
                }
                break; // break case
            }
            case (Piece::pieceType::rook):
            {
                std::vector<short> directionalIncrement = { -8,8,-1,1 };

                std::deque<std::pair<short, short>> newMoves;
            
                findAvailableMoves(newMoves, directionalIncrement, theOrigin);

                moveQueue.insert(moveQueue.end(), newMoves.begin(), newMoves.end());
            
                break; // break case
            }

            case (Piece::pieceType::queen):
            {
                std::vector<short> directionalIncrement = { -8,8,-1,1,-7,7,-9,9 };

                std::deque<std::pair<short, short>> newMoves;

                findAvailableMoves(newMoves, directionalIncrement, theOrigin);

                moveQueue.insert(moveQueue.end(), newMoves.begin(), newMoves.end());

                break; // break case
            }
            case (Piece::pieceType::king):
            {
                std::vector<short> directionalIncrement = { -8,8,-1,1,-7,7,-9,9 };

                std::deque<std::pair<short, short>> newMoves;

                findAvailableMoves(newMoves, directionalIncrement, theOrigin, true);

                // If the king hasn't moved, let's add potential castle moves
                if (!this->theSpaces[theOrigin]->currentPiece->hasMoved)
                {
                    if (this->theSpaces[theOrigin - 1]->currentPiece->myType == Piece::pieceType::empty
                        && this->theSpaces[theOrigin - 2]->currentPiece->myType == Piece::pieceType::empty)
                        newMoves.emplace_back(std::pair<short, short>(theOrigin, theOrigin-2));
                    if (this->theSpaces[theOrigin + 1]->currentPiece->myType == Piece::pieceType::empty
                        && this->theSpaces[theOrigin + 2]->currentPiece->myType == Piece::pieceType::empty)
                        newMoves.emplace_back(std::pair<short, short>(theOrigin, theOrigin + 2));
                }


                moveQueue.insert(moveQueue.end(), newMoves.begin(), newMoves.end());

                break; // break case
            }
        }
    }

    //return moveQueue;
}

void ChessBoard::Board::findAvailableMoves(
    std::deque<std::pair<short, short>>& availableMoves,
    std::vector<short>& directionalIncrement,
    const short theOrigin, 
    bool isKing)
{
    for (auto& increment : directionalIncrement)
    {
        int currentSpace = theOrigin;
        currentSpace += increment;
        size_t count = 0; // count to limit the king piece's potential moves to just one space

        while (currentSpace < NUM_SPACES
            && currentSpace >= 0)
        {
            if (isKing == true && count > 0) break;
            else count++;

            // if you go over the edge of the board
            if ((increment == 1) && getColumn(theOrigin) > getColumn(currentSpace))
                break;
            else if ((increment == -1) && getColumn(theOrigin) < getColumn(currentSpace))
                break;
            // if you go over the edge of the board
            else if ((increment == 9 || increment == -7) && getColumn(theOrigin) > getColumn(currentSpace))
                break;
            else if ((increment == -9 || increment == 7) && getColumn(theOrigin) < getColumn(currentSpace))
                break;

            if (this->theSpaces[currentSpace]->currentPiece->myType == Piece::pieceType::empty)
            {
                availableMoves.push_back(std::pair<short, short>(theOrigin, currentSpace));
            }
            // if it's an opposing team's piece
            else if (this->theSpaces[currentSpace]->currentPiece->myColor !=
                this->theSpaces[theOrigin]->currentPiece->myColor
                && this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::king)
            {
                availableMoves.push_back(std::pair<short, short>(theOrigin, currentSpace));
                break; // break while loop
            }

            else break;

            currentSpace += increment;
        }
    }
}

short GetRookForCastle(short destination)
{
    short rook_position;

    switch (destination)
    {
    case 6:
        rook_position = 7;
        break;
    case 2:
        rook_position = 0;
        break;
    case 62:
        rook_position = 63;
        break;
    case 58:
        rook_position = 56;
        break;
    default:
        rook_position = -1;  // The rook position isn't castle-able.
    }

    return rook_position;

}
ChessBoard::moveErrorCodes ChessBoard::Board::ValidateMove(const int start, const int destination, MoveData& outMoveData)
{
	// to do: 
	// > Check to see whose turn
	// > Check to see if a piece is trying to take its own color

    if (start==destination || 
		start > 64 || 
		destination > 64 || 
		start < 0 || 
		destination < 0 /*||
		start == NULL ||
		destination == NULL */
		) return ILLEGAL_MOVE;
    
	// if it's not the turn of the color of the piece that's being moved.
	if (this->theSpaces[start]->currentPiece->myColor == Piece::color::none)
		return EMPTY_SPACE;

	// if it's not the turn of the color of the piece that's being moved.
	else if (this->theSpaces[start]->currentPiece->myColor != WhoseMove())
		return WRONG_TEAM;

    // if it's not the turn of the color of the piece that's being moved.
    else if (this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::king)
        return CANT_TAKE_KING;

    // if the proposed move puts the king in check, invalidate move
    ChessBoard::Board* out_changed_state = new ChessBoard::Board(*this);
    proposeChange(*out_changed_state, start, destination);
    if (IsInCheck(this->theSpaces[start]->currentPiece->myColor, *out_changed_state))
    {
        delete out_changed_state;
        return MOVING_INTO_CHECK;
    }
    delete out_changed_state;

    switch (this->theSpaces[start]->currentPiece->myType)
    {
        case (Piece::pieceType::empty):
        {            
            return ILLEGAL_MOVE;
        }
        case (Piece::pieceType::queen):
        {
            // if she's going vertically
            // this if statement checks for non-empty spaces between start and destination
            if ((start % 8) == (destination%8))
            {
                if (start>destination)
                {
                    int currentSpace = start - 8;
                    while (currentSpace>0 && currentSpace>=destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                            )
                            return ILLEGAL_MOVE;
                        else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace != destination))
                            return ILLEGAL_MOVE;
                        else currentSpace -= 8;
                        
                    }
                }
                else
                {
                    int currentSpace = start + 8;
                    while (currentSpace<NUM_SPACES && currentSpace<=destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                            )
                            return ILLEGAL_MOVE;
                        else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace != destination))
                            return ILLEGAL_MOVE;
                        else currentSpace += 8;
                        
                    }
                    
                    
                }
                return SUCCESS;
                
            }
            
            // if she's going horizontally, checks for non-empty spaces
            else if (floor(start/8)==floor(destination/8))
            {
                if (start>destination)
                {
                    int currentSpace = start - 1;
                    while (currentSpace >= destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                            )
                            return ILLEGAL_MOVE;
                        else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace != destination))
                            return ILLEGAL_MOVE;
                        else currentSpace -= 1;
                    }
                }
                //destination is greater than start
                else
                {
                    int currentSpace = start + 1;
                    while (currentSpace<=destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                            )
                            return ILLEGAL_MOVE;
                        else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace != destination))
                            return ILLEGAL_MOVE;
                        else currentSpace += 1;
                        
                    }
                }
                return SUCCESS;
            }
            
            // if she's moving diagonally, checks for non-empty spaces

            else if ((((destination - start) % 7 == 0) || ((destination - start) % 9 == 0)) && (this->theSpaces[destination]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor))
            {
                int currentSpace = start;
                while (currentSpace<NUM_SPACES && currentSpace>=0)
                {
                    if ((destination - start) % 7 == 0 )
                    {
                        if (destination > start) currentSpace+=7;
                        else currentSpace-=7;
                    }
                    else if ((destination - start) % 9 == 0 )
                    {
                        if (destination > start) currentSpace+=9;
                        else currentSpace-=9;
                    }
                    
                    if (currentSpace!=destination && this->theSpaces[currentSpace]->currentPiece->myType!=Piece::pieceType::empty)
                    {
                        // if it's trying to cross over a non-empty space
                        return ILLEGAL_MOVE;
                    }
                    
                    if (this->theSpaces[currentSpace]->currentPiece->myColor == this->theSpaces[start]->currentPiece->myColor) return ILLEGAL_MOVE;
                    
                    if (currentSpace == destination)
                    {
                        break;
                    }
                }
                return SUCCESS;
            }
            
            else return ILLEGAL_MOVE;

        }
        case (Piece::pieceType::bishop):
        {
            if (
                (
                    ((destination - start) > 0 && (destination - start) % 7 == 0 && (destination % 8 < start % 8))
                    ||
                    ((destination - start) > 0 && (destination - start) % 9 == 0 && (destination % 8 > start % 8))
                    ||
                    ((destination - start) < 0 && (destination - start) % 7 == 0 && (destination % 8 > start % 8))
                    ||
                    ((destination - start) < 0 && (destination - start) % 9 == 0 && (destination % 8 < start % 8))
                )
                && 
                (this->theSpaces[destination]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor)
               )
                {
                    int currentSpace = start;
                    while (currentSpace < NUM_SPACES 
                            && currentSpace >= 0)
                    {
                        if ((destination - start) % 7 == 0 )
                        {
                            if (destination > start) currentSpace+=7;
                            else currentSpace-=7;
                        }
                        else if ((destination - start) % 9 == 0 )
                        {
                            if (destination > start) currentSpace+=9;
                            else currentSpace-=9;
                        }
                        
                        if (currentSpace!=destination 
                            && this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty)
                        {
                            // if it's trying to cross over a non-empty space
                            return ILLEGAL_MOVE;
                        }
                        
                        if (this->theSpaces[currentSpace]->currentPiece->myColor == this->theSpaces[start]->currentPiece->myColor) return ILLEGAL_MOVE;
                        
                        if (currentSpace == destination)
                        {
                            break;
                        }
                    }
                    return SUCCESS;
                }
        
            else return ILLEGAL_MOVE;
        }

        case (Piece::pieceType::knight):
        {
			if (IsSameTeam(start,destination)) return SAME_TEAM;

            Space lSpaces[8];
            this->theSpaces[start]->GetLSpaces(lSpaces);
            for (size_t i=0; i<8; i++)
            {
                if (destination == lSpaces[i].spaceID)
                {
                    return SUCCESS;
                }
            }
        
            return ILLEGAL_MOVE;
        }
        case (Piece::pieceType::pawn):
        {
            if (std::abs(destination - start) < 7)
                return ILLEGAL_MOVE;

            // if it's a purple pawn
         
            if (this->theSpaces[start]->currentPiece->myColor == Piece::color::purple)
            {
                // if it's going one space
                if (destination == start - 8)
                {
                    if (this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::empty)
                    {
                        if (getRow(destination) == 0)
                        {
                            return PAWN_TRADE;
                        }
                        return SUCCESS;
                    }
                    else return ILLEGAL_MOVE;
                }

                // attacking right, if it's not the far rightmost pawn
                else if ((start + 1) % 8 != 0 && destination == start - 7)
                {
                    // if there's something to take
                    if (this->theSpaces[start - 7]->currentPiece->myType != Piece::pieceType::empty &&
                        this->theSpaces[start - 7]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor &&
                        this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::king)
                    {
                        if (getRow(destination) == 0)
                        {
                            return PAWN_TRADE;
                        }
                        return SUCCESS;
                    }
                    else return ILLEGAL_MOVE;
                }

                // attacking left, if it's not the far leftmost pawn
                else if (start % 8 != 0 && destination == start - 9)
                {
                    // if there's something to take
                    if (this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty &&
                        this->theSpaces[destination]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor &&
                        this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::king)
                    {
                        if (getRow(destination) == 0)
                        {
                            return PAWN_TRADE;
                        }
                        return SUCCESS;
                    }
                    else return ILLEGAL_MOVE;
                }
                //if the starting position is on the front line of pawns
                else if (start >= 48 && start <= 55)
                {
                    // TODO: Implement en passant

                    //if it's going two spaces
                    if (destination == start - 16 && this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::empty)
                    {
                        if (this->theSpaces[start - 8]->currentPiece->myType == Piece::pieceType::empty)
                        {
                            // Set up en passant vector.
                            if (getRow(destination) == 4)
                            {
                                if (this->theSpaces[destination - 1]->currentPiece->myType == Piece::pieceType::pawn
                                    && this->theSpaces[destination - 1]->currentPiece->myColor == Piece::color::orange
                                    && getColumn(destination - 1) != 7)
                                {
                                    outMoveData.enPassantMoves.push_back(std::pair<short, short>(destination - 1, start - 8));
                                }
                                if (this->theSpaces[destination + 1]->currentPiece->myType == Piece::pieceType::pawn
                                    && this->theSpaces[destination + 1]->currentPiece->myColor == Piece::color::orange
                                    && getColumn(destination + 1) != 0)
                                {
                                    outMoveData.enPassantMoves.push_back(std::pair<short, short>(destination + 1, start - 8));
                                }
                            }
                                
                            return SUCCESS;
                        }
                        else return ILLEGAL_MOVE;
                    }
                    else return ILLEGAL_MOVE;

                }
                else return ILLEGAL_MOVE;
                
            }
            //then it's a orange pawn
            else
            {
                if (destination==start+8)
                {
                    if (this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::empty)
                    {
                        if (getRow(destination) == 7)
                        {
                            return PAWN_TRADE;
                        }
                        return SUCCESS;
                    }
                    else return ILLEGAL_MOVE;
                }
                // attacking right, if it's not the far rightmost pawn
                else if (start % 8 !=0 && destination == start+7)
                {
                    // if there's something to take
                    if (this->theSpaces[start + 7]->currentPiece->myType != Piece::pieceType::empty &&
                        this->theSpaces[start + 7]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor &&
                        this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::king)
                    {
                        if (getRow(destination) == 7)
                        {
                            return PAWN_TRADE;
                        }
                        return SUCCESS;
                    }
                    else return ILLEGAL_MOVE;
                }
                
                // attacking left, if it's not the far leftmost pawn
                else if ((start+1)%8 !=0 && destination == start+9)
                {
                    // if there's something to take
                    if (this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty && 
                        this->theSpaces[destination]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor)
                    {
                        if (getRow(destination) == 7)
                        {
                            return PAWN_TRADE;
                        }
                        return SUCCESS;
                    }
                    else return ILLEGAL_MOVE;
                }

                //if the starting position is on the front line of pawns
                else if (start >= 8 && start <=15)
                {
                    // TODO: Implement en passant.

                    //if it's going two spaces
                    if (destination == start+16 && this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::empty)
                    {
                        if (this->theSpaces[start + 8]->currentPiece->myType == Piece::pieceType::empty)
                        {
                            // Set up en passant vector.
                            if (getRow(destination) == 3)
                            {
                                if (this->theSpaces[destination - 1]->currentPiece->myType == Piece::pieceType::pawn
                                    && this->theSpaces[destination - 1]->currentPiece->myColor == Piece::color::purple
                                    && getColumn(destination - 1) != 7)
                                {
                                    outMoveData.enPassantMoves.push_back(std::pair<short, short>(destination - 1, start + 8));
                                }
                                if (this->theSpaces[destination + 1]->currentPiece->myType == Piece::pieceType::pawn
                                    && this->theSpaces[destination + 1]->currentPiece->myColor == Piece::color::purple
                                    && getColumn(destination + 1) != 0)
                                {
                                    outMoveData.enPassantMoves.push_back(std::pair<short, short>(destination + 1, start + 8));
                                }
                            }
                            return SUCCESS;
                        }
                        else return ILLEGAL_MOVE;
                    }
                    else return ILLEGAL_MOVE;
                }
                else return ILLEGAL_MOVE;

            } //end else
        
        case (Piece::pieceType::rook):
        {
            //castling is handled in the king piece move validation
            
            // if they're in the same column
            if ((start % 8) == (destination % 8))
            {
                if (start > destination)
                {
                    int currentSpace = start - 8;
                    while (currentSpace > 0 && currentSpace >= destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace == destination && (
                                this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                            )
                            return ILLEGAL_MOVE;
                        else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace != destination))
                            return ILLEGAL_MOVE;
                        else if (currentSpace == destination) return SUCCESS;
                        else currentSpace -= 8;
                    }
                }
                else
                {
                    int currentSpace = start + 8;
                    while (currentSpace < NUM_SPACES && currentSpace <= destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace == destination && (
                                this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                            )
                            return ILLEGAL_MOVE;
                        else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace != destination))
                            return ILLEGAL_MOVE;
                        else if (currentSpace == destination) return SUCCESS;
                        else currentSpace += 8;

                    }
                }
            }

            // are they in the same row?
            else if (floor(start / 8) == floor(destination / 8))
            {
                if (start > destination)
                {
                    int currentSpace = start - 1;
                    while (currentSpace >= destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace == destination && (
                                this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                            )
                            return ILLEGAL_MOVE;

                        else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace != destination))
                            return ILLEGAL_MOVE;
                        else if (currentSpace == destination) return SUCCESS;
                        else currentSpace -= 1;
                    }
                }
                //destination is greater than start
                else
                {
                    int currentSpace = start + 1;
                    while (currentSpace <= destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace == destination && (
                                this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                            )
                            return ILLEGAL_MOVE;
                        else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                            && (currentSpace != destination))
                            return ILLEGAL_MOVE;
                        else if (currentSpace == destination) return SUCCESS;
                        else currentSpace += 1;

                    }
                }
            }

            else return ILLEGAL_MOVE;
                        
            case Piece::pieceType::king:
            {
                // if he's going vertically
                // this if statement checks for non-empty spaces between start and destination
                if ((start % 8) == (destination % 8))
                {
                    if (start>destination)
                    {
                        // if the king is trying to go more than one space
                        if (start > (destination + 8)) return ILLEGAL_MOVE;
                        
                        int currentSpace = start - 8; //go to the next space in the column
                        while (currentSpace>0 && currentSpace>=destination)
                        {
                            if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                                && (currentSpace == destination && (this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                                                    && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                                )
                                return ILLEGAL_MOVE;
                            else currentSpace -= 8;
                            
                        }
                    }
                    
                    // else destination is greater than start
                    else
                    {
                        // if the king is trying to go more than one space
                        if (start < (destination - 8)) return ILLEGAL_MOVE;
                        
                        int currentSpace = start + 8;
                        while (currentSpace<NUM_SPACES && currentSpace<=destination)
                        {
                            if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                                && (currentSpace == destination && (
                                                                    this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                                                    && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                                )
                                return ILLEGAL_MOVE;
                            else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                                && (currentSpace != destination))
                                return ILLEGAL_MOVE;
                            else currentSpace += 8;
                        }
                    }
                    return SUCCESS;   
                }

                // if he's going horizontally, checks for non-empty spaces
                else if (floor(start/8)==floor(destination/8))
                {
                    // TO DO ADD CASTLING CHECK.

                    if (abs(start-destination)==2)
                    {
                        // Check to make sure the king hasn't moved yet.
                        if (this->theSpaces[start]->currentPiece->hasMoved
                            || this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty)
                        {
                            return ILLEGAL_MOVE;
                        }

                        // Check to make sure the rook hasn't moved yet.
                        short rookForCastle = GetRookForCastle(destination);
                        if (this->theSpaces[rookForCastle]->currentPiece->hasMoved || 
                            this->theSpaces[rookForCastle]->currentPiece->myType != Piece::pieceType::rook ||
                            this->theSpaces[rookForCastle]->currentPiece->myColor != 
                                                            this->theSpaces[start]->currentPiece->myColor)
                            return ILLEGAL_MOVE;


                        // First check if he's castling.
                        if (
                            ((start == 4 && destination == 6)
                            || (start == 4 && destination == 2))
                            
                            || 
                            
                            ((start == 60 && destination == 62)
                            || (start == 60 && destination == 58))
                            )
                        {

                            // See if the king is currently in check -- if so, he can't castle.
                            if (IsInCheck(this->theSpaces[start]->currentPiece->myColor, *this))
                            {
                                return MOVING_INTO_CHECK;
                            }

                            auto loop_interval = (destination > start) ? 1:-1;
                            auto currentSpace = start + loop_interval;
                            while (currentSpace >= destination)
                            {
                                if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty)
                                    return ILLEGAL_MOVE;

                                ChessBoard::Board* out_possible_move_changed_state = new ChessBoard::Board(*this);
                                // Need to propose change on current space because king can't move THRU check.
                                proposeChange(*out_possible_move_changed_state, start, currentSpace);
                                if (IsInCheck(this->theSpaces[start]->currentPiece->myColor, *out_possible_move_changed_state))
                                {
                                    delete out_possible_move_changed_state;
                                    return MOVING_INTO_CHECK;
                                }
                                delete out_possible_move_changed_state;
                                
                                currentSpace = currentSpace + loop_interval;
                            }
                            return CASTLE;
                        }
                    }
                    
                    if (start>destination)
                    {
                        // if the king is trying to go more than one space
                        if (start > (destination + 1)) return ILLEGAL_MOVE;

                        auto currentSpace = start - 1;
                        while (currentSpace >= destination)
                        {
                            if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                                && (currentSpace == destination && (
                                                                    this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                                                    && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                                )
                                return ILLEGAL_MOVE;
                            else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                                && (currentSpace != destination))
                                return ILLEGAL_MOVE;
                            else currentSpace -= 1;
                        }
                    }
                    //destination is greater than start
                    else
                    {
                        // if the king is trying to go more than one space
                        if (start < (destination - 1)) return ILLEGAL_MOVE;
                        
                        int currentSpace = start + 1;
                        while (currentSpace<=destination)
                        {
                            if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                                && (currentSpace == destination && (
                                                                    this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty
                                                                    && this->theSpaces[start]->currentPiece->myColor == this->theSpaces[destination]->currentPiece->myColor))
                                )
                                return ILLEGAL_MOVE;
                            else if (this->theSpaces[currentSpace]->currentPiece->myType != Piece::pieceType::empty
                                && (currentSpace != destination))
                                return ILLEGAL_MOVE;
                            else currentSpace += 1;
                            
                        }
                    }
                    return SUCCESS;
                }
                
                // if he's moving diagonally, checks for non-empty spaces
                
                else if ((((destination - start) % 7 == 0) || ((destination - start) % 9 == 0))
                         && (this->theSpaces[destination]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor))
                {
                    int currentSpace = start;
                    while (currentSpace<NUM_SPACES && currentSpace>=0)
                    {
                        if ((destination - start) % 7 == 0 )
                        {
                            // if the king is trying to go more than one space
                            if (abs(start - destination) > 7) return ILLEGAL_MOVE;
                            
                            if (destination > start) currentSpace+=7;
                            else currentSpace-=7;
                        }
                        else if ((destination - start) % 9 == 0 )
                        {
                            // if the king is trying to go more than one space
                            if (abs(start - destination) > 9) return ILLEGAL_MOVE;
                            
                            if (destination > start) currentSpace+=9;
                            else currentSpace-=9;
                        }
                        
                        if (currentSpace!=destination && this->theSpaces[currentSpace]->currentPiece->myType!=Piece::pieceType::empty)
                        {
                            // if it's trying to cross over a non-empty space
                            return ILLEGAL_MOVE;
                        }
                        
                        if (this->theSpaces[currentSpace]->currentPiece->myColor == this->theSpaces[start]->currentPiece->myColor) return ILLEGAL_MOVE;
                        
                        if (currentSpace == destination)
                        {
                            break;
                        }
                    }
                    return SUCCESS;
                }
                
                else return ILLEGAL_MOVE;
            }
        }
        default:  
            {
                std::cerr << "in default case\n";
                //do nothing
            }
 
        }
            
    }
    
    return SUCCESS;
}

ChessBoard::Piece::color ChessBoard::Board::WhoseMove()
{
	return this->whoseMove;
}


void ChessBoard::Board::StartGame(Piece::color startWhoseMove)
{
	this->whoseMove = startWhoseMove;
}

