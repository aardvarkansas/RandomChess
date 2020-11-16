//
//  board.cpp
//  Chess
//
//  Created by User on 1/8/17.
//  Copyright (c) 2017 User. All rights reserved.
//

#include "board.h"
#include <iomanip>
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
    //currentPiece = new Piece();
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
    std::cout << "initializing board";
    
    for (auto i=0;i<NUM_SPACES;++i)
    {
        //theSpaces[i].InitializeAdjacentSpaces();
        theSpaces[i] = new Space();
        theSpaces[i]->spaceID = i;
        char newLine = '\n';
        if (i%8 != 0) newLine = ' ';
        std::cout <<  newLine << std::setw(4) << theSpaces[i]->spaceID;
    }
    
    std::cout <<  std::endl;


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
		std::cout << newLine << std::setw(4) << theSpaces[i]->spaceID;
	}

	std::cout << std::endl;

    for (int i=0;i<64;++i)
    {
        //theSpaces[i].InitializeAdjacentSpaces();
        theSpaces[i]->spaceID = i;
        char newLine = '\n';
        if (i%8 != 0) newLine = ' ';
       
        std::cout <<  newLine << std::setw(8) << PurpleOrOrange(i);
    }
}

void ChessBoard::Board::PrintMoves()
{
    int i(0);
    for (std::string theMove : this->theMoves)
    {
        i++;
        std::cout << "Move #" << std::to_string(i) << " " << theMove << "\n";
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

bool ChessBoard::Board::Move(const int start, const int destination)
{
	int returnCode = ValidateMove(start, destination);

    if (returnCode == SUCCESS)
    {
        std::cout << std::endl << std::to_string((int)this->theSpaces[destination]->currentPiece->myType) << std::setw(8) << std::to_string((int)this->theSpaces[destination]->currentPiece->myColor);

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
        
        this->theMoves.push_back(std::to_string(theMoves.size()) + "_" + std::to_string((int)this->theSpaces[destination]->currentPiece->myType) + "_" + std::to_string((int)this->theSpaces[destination]->currentPiece->myColor) + "_" + std::to_string(start)+ "_" + std::to_string(destination) + capturedPieceString);
        
		//switch the move to the other color
		(this->whoseMove == Piece::color::purple) ? this->whoseMove = Piece::color::orange : this->whoseMove = Piece::color::purple;

        if (IsInCheck(this->whoseMove, *this))
            std::cout << "\n\n Your king is in check!!!\n\n";

        return true;
    }
    
	else
    {
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
		}
		std::cout << "\n\nBAD MOVE, PUNK: " << errorMessage << "\n\n";
        return false;

    }
}

bool ChessBoard::Board::IsInCheck(Piece::color king_color, ChessBoard::Board &changedState)
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
                        && changedState.theSpaces[kingSpaceId]->currentPiece->myColor != Piece::color::orange)
                    { 
                        std::cout << "\n\norange pawn!\n\n\n";
                        if (i - 7 == kingSpaceId || i - 9 == kingSpaceId)
                        {
                            std::cout << "\n\nKing is in check\n\n";
                            is_in_check = true;
                        }

                    }
                    else if (changedState.theSpaces[kingSpaceId]->currentPiece->myColor == Piece::color::orange)
                    {
                        if (i + 7 == kingSpaceId || i + 9 == kingSpaceId)
                        {
                            std::cout << "\n\nKing is in check\n\n";
                            is_in_check = true;
                        }
                        std::cout << "\n\npurple pawn!\n\n\n";
                    }
                     
                    break;
                }
                    
                case (ChessBoard::Piece::pieceType::bishop):
                {
                    std::cout << "\n\nbishop!\n\n\n";
                    break;
                }
                    
                case (ChessBoard::Piece::pieceType::knight):
                {
                    std::cout << "\n\nknight!\n\n\n";

                    Space lSpaces[8];
                    this->theSpaces[i]->GetLSpaces(lSpaces);
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
                    std::cout << "\n\nrook!\n\n\n";
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
                    if ((i - kingSpaceId) % 7 == 0)
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 7; min_space < max_space; min_space += 7)
                        {
                            if (theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
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
                    if ((i - kingSpaceId) % 9 == 0)
                    {
                        // check to see if there are any pieces in between
                        for (min_space += 9; min_space < max_space; min_space += 9)
                        {
                            if (theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
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
                            if (theSpaces[min_space]->currentPiece->myType != Piece::pieceType::empty)
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

                    std::cout << "\n\nqueen!\n\n\n";
                    break;
                }
                case (ChessBoard::Piece::pieceType::king):
                {
                    std::cout << "\n\nking!\n\n\n";
                    break;
                }
            }
        }
        if (is_in_check == true)
        {
            std::cout << "\n\n!!!king in check!!!!\n\n\n";
            return true;
        }
    }
    return false;
}

bool ChessBoard::Board::IsSameTeam(int start, int destination)
{
	if (this->theSpaces[destination]->currentPiece->myColor == this->theSpaces[start]->currentPiece->myColor) return false;
	else return true;
}

ChessBoard::Board& ChessBoard::Board::proposeChange(ChessBoard::Board &changedState, const int start, const int destination)
{

    changedState.theSpaces[destination]->currentPiece->myColor = changedState.theSpaces[start]->currentPiece->myColor;
    changedState.theSpaces[destination]->currentPiece->myType = changedState.theSpaces[start]->currentPiece->myType;
    changedState.theSpaces[destination]->currentPiece->hasMoved = true;
    changedState.theSpaces[start]->currentPiece->hasMoved = true;
    changedState.theSpaces[start]->currentPiece->myColor = Piece::color::none;
    changedState.theSpaces[start]->currentPiece->myType = Piece::pieceType::empty;


    return changedState;
}
int ChessBoard::Board::ValidateMove(const int start, const int destination)
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
			if (!IsSameTeam(start,destination)) return SAME_TEAM;

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
                    if (this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::empty) return SUCCESS;
                    else return ILLEGAL_MOVE;
                }

                // attacking right, if it's not the far rightmost pawn
                else if ((start + 1) % 8 != 0 && destination == start - 7)
                {
                    // if there's something to take
                    if (this->theSpaces[start - 7]->currentPiece->myType != Piece::pieceType::empty &&
                        this->theSpaces[start - 7]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor &&
                        this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::king)
                        return SUCCESS;
                    else return ILLEGAL_MOVE;
                }

                // attacking left, if it's not the far leftmost pawn
                else if (start % 8 != 0 && destination == start - 9)
                {
                    // if there's something to take
                    if (this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty &&
                        this->theSpaces[destination]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor &&
                        this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::king)
                        return SUCCESS;
                    else return ILLEGAL_MOVE;
                }
                //if the starting position is on the front line of pawns
                else if (start >= 48 && start <= 55)
                {
                    //if it's going two spaces
                    if (destination == start - 16 && this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::empty)
                    {
                        if (this->theSpaces[start - 8]->currentPiece->myType == Piece::pieceType::empty)
                            return SUCCESS;
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
                    if (this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::empty) return SUCCESS;
                    else return ILLEGAL_MOVE;
                }
                // attacking right, if it's not the far rightmost pawn
                else if (start % 8 !=0 && destination == start+7)
                {
                    // if there's something to take
                    if (this->theSpaces[start+7]->currentPiece->myType != Piece::pieceType::empty &&
                        this->theSpaces[start + 7]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor &&
                        this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::king)
                        return SUCCESS;
                    else return ILLEGAL_MOVE;
                }
                
                // attacking left, if it's not the far leftmost pawn
                else if ((start+1)%8 !=0 && destination == start+9)
                {
                    // if there's something to take
                    if (this->theSpaces[destination]->currentPiece->myType != Piece::pieceType::empty && 
                        this->theSpaces[destination]->currentPiece->myColor != this->theSpaces[start]->currentPiece->myColor)
                        return SUCCESS;
                    else return ILLEGAL_MOVE;
                }

                //if the starting position is on the front line of pawns
                else if (start >= 8 && start <=15)
                {
                    //if it's going two spaces
                    if (destination == start+16 && this->theSpaces[destination]->currentPiece->myType == Piece::pieceType::empty)
                    {
                        if (this->theSpaces[start+8]->currentPiece->myType == Piece::pieceType::empty) 
                            return SUCCESS;
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
                        else currentSpace += 1;



                    }
                }
            }

            else return ILLEGAL_MOVE;
            
                        
           case Piece::pieceType::king:
            {
                // if he's going vertically
                // this if statement checks for non-empty spaces between start and destination
                if ((start % 8) == (destination%8))
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
                        if (this->theSpaces[start]->currentPiece->hasMoved)
                        {
                            return ILLEGAL_MOVE;
                        }
                        
                        else if (start>destination)
                        {
                            //for (int i=start;i>getEndOfRow(start
                        }
                        
                        else
                        {
                            
                        }
                    }
                    
                                    
                    if (start>destination)
                    {
                        // if the king is trying to go more than one space
                        if (start > (destination + 1)) return ILLEGAL_MOVE;

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
                std::cout << "in default case\n";
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


void ChessBoard::Board::StartGame()
{
	this->whoseMove = Piece::color::orange;
}

