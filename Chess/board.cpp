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

#define NUM_SPACES 64

ChessBoard::Piece::Piece()
{
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
ChessBoard::Space::Space() {    };
    
ChessBoard::Space::~Space()
{
    spaceID = NULL;
}

ChessBoard::Space & ChessBoard::Space::operator= (const Space &mySpace)
{
    this->spaceID = mySpace.spaceID;
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
    
    for (int i=0;i<64;++i)
    {
        //theSpaces[i].InitializeAdjacentSpaces();
        theSpaces[i] = new Space();
        theSpaces[i]->spaceID = i;
        char newLine = '\n';
        if (i%8 != 0) newLine = ' ';
        std::cout <<  newLine << std::setw(4) << theSpaces[i]->spaceID;
    }
    
    std::cout <<  std::endl;
}

// This function is used to print the terminal version of the chess board.
std::string ChessBoard::Board::BlackOrWhite(const int spaceID)
{
    std::string myType; // type of piece, e.g., bishop pawn rook king queen

	// this routine uppercases the strings for any black pieces
    if (theSpaces[spaceID]->currentPiece.myColor == Piece::color::black)
    {
        for (auto &myChar : GetPieceName(theSpaces[spaceID]->currentPiece.myType))
            myType += std::toupper(myChar);
    }
    else myType = GetPieceName(theSpaces[spaceID]->currentPiece.myType);
    
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
       
        std::cout <<  newLine << std::setw(8) << BlackOrWhite(i);
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
        case 0:
            return "empty";
            break;
        case 1:
            return "pawn";
            break;
        case 2:
            return "bishop";
            break;
        case 3:
            return "knight";
            break;
        case 4:
            return "rook";
            break;
        case 5:
            return "king";
            break;
        case 6:
            return "queen";
            break;
        default:
            return "unkonwn";
            break;
            
    }
    
}

ChessBoard::Board::~Board()
{
    if (this->theSpaces!=NULL)
    {
        //free(this->theSpaces);
    }
}

bool ChessBoard::Board::Move(const int start, const int destination)
{
	int returnCode = ValidateMove(start, destination);

    if (returnCode == SUCCESS)
    {
        Piece *tempPiece = new Piece();
        Piece *capturedPiece = new Piece();
        tempPiece->myType = Piece::pieceType::empty;
        *capturedPiece = this->theSpaces[destination]->currentPiece;
        
        std::cout << std::endl << std::to_string(capturedPiece->myType) << std::setw(8) << std::to_string(capturedPiece->myColor);
        
        std::string capturedPieceString = "";
        if (capturedPiece->myType != Piece::pieceType::empty)
        {
            capturedPieceString = "_x" + BlackOrWhite(destination);
        }
        
        this->theSpaces[destination]->currentPiece = this->theSpaces[start]->currentPiece;
        this->theSpaces[destination]->currentPiece.hasMoved = true;
        this->theSpaces[start]->currentPiece = *tempPiece;
        
        this->theMoves.push_back(std::to_string(theMoves.size()) + "_" + std::to_string(this->theSpaces[destination]->currentPiece.myType) + "_" + std::to_string(this->theSpaces[destination]->currentPiece.myColor) + "_" + std::to_string(start)+ "_" + std::to_string(destination) + capturedPieceString);
        
		//switch the move to the other color
		(this->whoseMove == Piece::color::black) ? this->whoseMove = Piece::color::white : this->whoseMove = Piece::color::black;

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
		}
		std::cout << "\n\nBAD MOVE, PUNK: " << errorMessage << "\n\n";
        return false;

    }
}

bool ChessBoard::Board::IsInCheck(Piece::color color_of_king, Board& changedState)
{
    // need to check for opposing team's rooks, queens, kings, bishops, knights, and pawns
    for (int i=0; i < NUM_SPACES; ++i)
    {
        if (this->theSpaces[i]->currentPiece.myColor != color_of_king)
        {
            switch (this->theSpaces[i]->currentPiece.myType)
            {
                case (ChessBoard::Piece::pawn):
                {
                    std::cout << "\n\npawn!\n\n\n"; 
                    break;
                }
                    
                case (ChessBoard::Piece::bishop):
                {
                    std::cout << "\n\nbishop!\n\n\n";
                    break;
                }
                    
                case (ChessBoard::Piece::knight):
                {
                    std::cout << "\n\nknight!\n\n\n";
                    break;
                }
                    
                case (ChessBoard::Piece::rook):
                {
                    std::cout << "\n\nrook!\n\n\n";
                    break;
                }
                    
                case (ChessBoard::Piece::queen):
                {
                    std::cout << "\n\nqueen!\n\n\n";
                    break;
                }
                case (ChessBoard::Piece::king):
                {
                    std::cout << "\n\nking!\n\n\n";
                    break;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::Board::IsSameTeam(int start, int destination)
{
	if (this->theSpaces[destination]->currentPiece.myColor == this->theSpaces[start]->currentPiece.myColor) return false;
	else return true;
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
	if (this->theSpaces[start]->currentPiece.myColor == Piece::color::none)
		return EMPTY_SPACE;

	// if it's not the turn of the color of the piece that's being moved.
	else if (this->theSpaces[start]->currentPiece.myColor != WhoseMove())
		return WRONG_TEAM;

    switch (this->theSpaces[start]->currentPiece.myType)
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
                        if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                            || (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                            )
                            return ILLEGAL_MOVE;
                        else currentSpace -= 8;
                        
                    }
                }
                else
                {
                    int currentSpace = start + 8;
                    while (currentSpace<NUM_SPACES && currentSpace<=destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                            || (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                            )
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
                        if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                            || (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                            )
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
                        if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                            || (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                            )
                            return ILLEGAL_MOVE;
                        else currentSpace += 1;
                        
                    }
                }
                return SUCCESS;
            }
            
            // if she's moving diagonally, checks for non-empty spaces

            else if ((((destination - start) % 7 == 0) || ((destination - start) % 9 == 0)) && (this->theSpaces[destination]->currentPiece.myColor != this->theSpaces[start]->currentPiece.myColor))
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
                    
                    if (currentSpace!=destination && this->theSpaces[currentSpace]->currentPiece.myType!=Piece::pieceType::empty)
                    {
                        // if it's trying to cross over a non-empty space
                        return ILLEGAL_MOVE;
                    }
                    
                    if (this->theSpaces[currentSpace]->currentPiece.myColor == this->theSpaces[start]->currentPiece.myColor) return ILLEGAL_MOVE;
                    
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
            
            if ((((destination - start) % 7 == 0) || ((destination - start) % 9 == 0)) && (this->theSpaces[destination]->currentPiece.myColor != this->theSpaces[start]->currentPiece.myColor))
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
                        
                        if (currentSpace!=destination && this->theSpaces[currentSpace]->currentPiece.myType!=Piece::pieceType::empty)
                        {
                            // if it's trying to cross over a non-empty space
                            return ILLEGAL_MOVE;
                        }
                        
                        if (this->theSpaces[currentSpace]->currentPiece.myColor == this->theSpaces[start]->currentPiece.myColor) return ILLEGAL_MOVE;
                        
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
            // if it's a black pawn
            if (this->theSpaces[start]->currentPiece.myColor == Piece::color::black)
            {
                // if it's going one space
                if (destination==start-8)
                {
                    if (this->theSpaces[destination]->currentPiece.myType == Piece::pieceType::empty) return SUCCESS;
                    else return ILLEGAL_MOVE;
                }
                
                // attacking right, if it's not the far rightmost pawn
                else if ((start+1)%8 !=0 && destination == start-7)
                {
                    // if there's something to take
                    if (this->theSpaces[start-7]->currentPiece.myType != Piece::pieceType::empty && this->theSpaces[start-7]->currentPiece.myColor != this->theSpaces[start]->currentPiece.myColor &&
                        this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::king)
                        return SUCCESS;
                    else return ILLEGAL_MOVE;
                }
                
                // attacking left, if it's not the far leftmost pawn
                else if (start % 8 !=0 && destination == start-9)
                {
                    // if there's something to take
                    if (this->theSpaces[start-9]->currentPiece.myType != Piece::pieceType::empty
                        && this->theSpaces[start-9]->currentPiece.myColor != this->theSpaces[start]->currentPiece.myColor) return SUCCESS;
                    else return ILLEGAL_MOVE;
                }
                //if the starting position is on the front line of pawns
                else if (start >= 48 && start <=55 && this->theSpaces[destination]->currentPiece.myType == Piece::pieceType::empty)
                {                    
                    //if it's going two spaces
                    if (destination == start-16)
                    {
                        if (this->theSpaces[start-8]->currentPiece.myType == Piece::pieceType::empty) return SUCCESS;
                        else return ILLEGAL_MOVE;
                    }
                                      
                }
                
            }
            //then it's a white pawn
            else
            {
                if (destination==start+8)
                {
                    if (this->theSpaces[destination]->currentPiece.myType == Piece::pieceType::empty) return SUCCESS;
                    else return ILLEGAL_MOVE;
                }
                // attacking right, if it's not the far rightmost pawn
                else if (start % 8 !=0 && destination == start+7)
                {
                    // if there's something to take
                    if (this->theSpaces[start+7]->currentPiece.myType != Piece::pieceType::empty) return SUCCESS;
                    else return ILLEGAL_MOVE;
                }
                
                // attacking left, if it's not the far leftmost pawn
                else if ((start+1)%8 !=0 && destination == start+9)
                {
                    // if there's something to take
                    if (this->theSpaces[start+9]->currentPiece.myType != Piece::pieceType::empty && this->theSpaces[start+9]->currentPiece.myColor != this->theSpaces[start]->currentPiece.myColor) return SUCCESS;
                    else return ILLEGAL_MOVE;
                }

                //if the starting position is on the front line of pawns
                else if (start >= 8 && start <=15)
                {
                    //if it's going two spaces
                    if (destination == start+16 && this->theSpaces[destination]->currentPiece.myType == Piece::pieceType::empty)
                    {
                        if (this->theSpaces[start+8]->currentPiece.myType == Piece::pieceType::empty&& this->theSpaces[start+8]->currentPiece.myColor != this->theSpaces[start]->currentPiece.myColor) return SUCCESS;
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
            if ((start % 8) == (destination%8))
            {
                if (start>destination)
                {
                    int currentSpace = start - 8;
                    while (currentSpace>0 && currentSpace>=destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                            || (currentSpace == destination && (
                                        this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                        && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                            )
                            return ILLEGAL_MOVE;
                        else currentSpace -= 8;
                        
                    }
                }
                else
                {
                    int currentSpace = start + 8;
                    while (currentSpace<NUM_SPACES && currentSpace<=destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                            || (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                            )
                            return ILLEGAL_MOVE;
                        else currentSpace += 8;
                        
                    }
                }
            }
            
            // are they in the same row?
            else if (floor(start/8)==floor(destination/8))
            {
                if (start>destination)
                {
                    int currentSpace = start - 1;
                    while (currentSpace >= destination)
                    {
                        if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                            || (currentSpace == destination && (
                                                            this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                            && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                            )
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
                        if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                            || (currentSpace == destination && (
                                                                this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                            )
                            return ILLEGAL_MOVE;
                        else currentSpace += 1;
                        
                    }
                }
            }
            
                        
           case Piece::pieceType::king:
            {
                IsInCheck(this->theSpaces[start]->currentPiece.myColor,*this);
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
                            if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                                || (currentSpace == destination && (this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                    && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
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
                            if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                                || (currentSpace == destination && (
                                                                    this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                    && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                                )
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
                        if (this->theSpaces[start]->currentPiece.hasMoved)
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
                            if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                                || (currentSpace == destination && (
                                                                    this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                    && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                                )
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
                            if (this->theSpaces[currentSpace]->currentPiece.myType != Piece::pieceType::empty
                                || (currentSpace == destination && (
                                                                    this->theSpaces[destination]->currentPiece.myType != Piece::pieceType::empty
                                                                    && this->theSpaces[start]->currentPiece.myColor == this->theSpaces[destination]->currentPiece.myColor))
                                )
                                return ILLEGAL_MOVE;
                            else currentSpace += 1;
                            
                        }
                    }
                    return SUCCESS;
                }
                
                // if he's moving diagonally, checks for non-empty spaces
                
                else if ((((destination - start) % 7 == 0) || ((destination - start) % 9 == 0))
                         && (this->theSpaces[destination]->currentPiece.myColor != this->theSpaces[start]->currentPiece.myColor))
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
                        
                        if (currentSpace!=destination && this->theSpaces[currentSpace]->currentPiece.myType!=Piece::pieceType::empty)
                        {
                            // if it's trying to cross over a non-empty space
                            return ILLEGAL_MOVE;
                        }
                        
                        if (this->theSpaces[currentSpace]->currentPiece.myColor == this->theSpaces[start]->currentPiece.myColor) return ILLEGAL_MOVE;
                        
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
    this->theSpaces[0]->currentPiece = *(new Piece(Piece::pieceType::rook, Piece::color::white));
    this->theSpaces[1]->currentPiece= *(new Piece(Piece::pieceType::knight, Piece::color::white));
    this->theSpaces[2]->currentPiece= *(new Piece(Piece::pieceType::bishop, Piece::color::white));
    this->theSpaces[3]->currentPiece= *(new Piece(Piece::pieceType::queen, Piece::color::white));
    this->theSpaces[4]->currentPiece= *(new Piece(Piece::pieceType::king, Piece::color::white));
    this->theSpaces[5]->currentPiece= *(new Piece(Piece::pieceType::bishop, Piece::color::white));
    this->theSpaces[6]->currentPiece= *(new Piece(Piece::pieceType::knight, Piece::color::white));
    this->theSpaces[7]->currentPiece= *(new Piece(Piece::pieceType::rook, Piece::color::white));
    this->theSpaces[8]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::white));
    this->theSpaces[9]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::white));
    this->theSpaces[10]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::white));
    this->theSpaces[11]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::white));
    this->theSpaces[12]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::white));
    this->theSpaces[13]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::white));
    this->theSpaces[14]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::white));
    this->theSpaces[15]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::white));

    for (size_t i=16;i<48;++i)
    {
        this->theSpaces[i]->currentPiece= *(new Piece(Piece::pieceType::empty, Piece::color::none));
    }
    
    
    this->theSpaces[48]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::black));
    this->theSpaces[49]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::black));
    this->theSpaces[50]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::black));
    this->theSpaces[51]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::black));
    this->theSpaces[52]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::black));
    this->theSpaces[53]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::black));
    this->theSpaces[54]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::black));
    this->theSpaces[55]->currentPiece= *(new Piece(Piece::pieceType::pawn, Piece::color::black));
    this->theSpaces[56]->currentPiece= *(new Piece(Piece::pieceType::rook, Piece::color::black));
    this->theSpaces[57]->currentPiece= *(new Piece(Piece::pieceType::knight, Piece::color::black));
    this->theSpaces[58]->currentPiece= *(new Piece(Piece::pieceType::bishop, Piece::color::black));
    this->theSpaces[59]->currentPiece= *(new Piece(Piece::pieceType::queen, Piece::color::black));
    this->theSpaces[60]->currentPiece= *(new Piece(Piece::pieceType::king, Piece::color::black));
    this->theSpaces[61]->currentPiece= *(new Piece(Piece::pieceType::bishop, Piece::color::black));
    this->theSpaces[62]->currentPiece= *(new Piece(Piece::pieceType::knight, Piece::color::black));
    this->theSpaces[63]->currentPiece= *(new Piece(Piece::pieceType::rook, Piece::color::black));

	this->whoseMove = Piece::color::white;

}

