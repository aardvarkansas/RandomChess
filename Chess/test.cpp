#include "test.h"
#include "board.h"


test::test()
{
	
}

bool test::instantiate_piece()
{
	ChessBoard::Piece myPiece;
	myPiece.myType = ChessBoard::Piece::pieceType::pawn;

	return true;
}

bool test::adjacent_spaces()
{
	ChessBoard::Board myBoard;
	short adjacentSpaces[8];


	myBoard.theSpaces[62]->GetAdjacentSpaces(adjacentSpaces);

	// operator overload
	ChessBoard::Space mySpace = *myBoard.theSpaces[11];

	std::cout << "adj spaces: " << sizeof(adjacentSpaces) << std::endl;
	std::cout << "int: " << sizeof(int) << std::endl;
	std::cout << "char: " << sizeof(char) << std::endl;
	std::cout << "bool: " << sizeof(bool) << std::endl;
	std::cout << "adj spaces[2]: " << sizeof(adjacentSpaces[2]) << std::endl;

	for (size_t i = 0; i<8; ++i)
	{
		std::cout << std::endl << adjacentSpaces[i];
	}

	return true;

}


test::~test()
{
}
