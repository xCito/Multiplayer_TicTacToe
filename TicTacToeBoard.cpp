/*
 * TicTacToeBoard.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */

#include "TicTacToeBoard.h"

/*
 * CONSTRUCTOR DEFAULT
 * 		Sets the size of the TicTacToe board to 3x3
 *   	by default AND generates it.
 */
TicTacToeBoard::TicTacToeBoard()
{
	size = 3;
	createBoard(size);
}

/*
 * CONSTRUCTOR OVERLOADED,
 *	 	Sets the size of the TicTacToe board depending on
 *	 	the number of players. Always generated an odd number
 *	 	size board.
 */
TicTacToeBoard::TicTacToeBoard(int numPlayers)
{
	size = (2*numPlayers) -1;	// <--Odd number formula

	if(size==1)					// To prevent 1x1 TTT boards
		size = 3;
	createBoard(size);
}

/*
 * DESTRUCTOR,
 */
TicTacToeBoard::~TicTacToeBoard()
{
	//cout << "TicTacToeBoard destructor" << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////

/*
 * Creates a vector of vectors of type char to symbolize
 * as the TTT board. Fills the vector 'blankSpaces' with int from
 * 0 to (size*2)-1   [EX: 3x3 TTT would have 0 to 8 in 'blankSpaces'].
 * Later to be used for determining which cells/spaces are empty.
 *
 * @param size - determines number of vectors that will be pushed
 * 				 and number of elems per pushed vector.
 */
void TicTacToeBoard::createBoard(int size)
{
	srand(time(0));

	for(int i=0; i<size; ++i)
		board.push_back(vector<char>(size, ' '));

	for(int i=0; i<size*size; ++i)
	{
		blankSpaces.push_back(i);
	}
	random_shuffle(blankSpaces.begin(),blankSpaces.end());
}

/*
 * Determines whether the TTT board is full by checking the number
 * of OpenCells/BlankSpaces left. If there are no OpenCells/BlankSpaces
 * left, the board is full.
 */
bool TicTacToeBoard::isFull()
{
	if(blankSpaces.size() == 0)
		return true;
	return false;
}

/*
 * Resets the TTT board's values. The contents of the TTT board is erased.
 * The vector containing OpenCell/BlankSpaces is erased. The values will be
 * reinitialized from the funcion 'createBoard()'
 */
void TicTacToeBoard::createNewBoard()
{
	board.clear();
	blankSpaces.clear();
	createBoard(size);
}

/*
 * Checks if a specific cell/space is available.
 * Also handles out of bounds values and negative values
 * to avoid checking a non existing cell/space.
 *
 * @return - TRUE if within board range and cell is open
 * 		   - FALSE if coordinate is out side board range and
 * 		           another sym is in cell.
 */
bool TicTacToeBoard::isCellOpen(int x, int y)
{
	char symbol;

	if(!isCellValid(x,y))		// If OUTSIDE of TTT board range
		return false;							//  space is not open

	symbol = board.at(y).at(x);
												// If the symbol at the chosen cell position
	if(symbol != ' ')							//  is not a space char, cell is not open
	{
		cout << "Space is closed" <<endl;
		return false;
	}

	return true;								// if code gets to here, condition is met for open space
}


/*
 * Checks if the x,y coordinates are within TTT board range.
 * @ return - TRUE if within range
 * 			- FALSE if outside of range
 */
bool TicTacToeBoard::isCellValid(int x, int y)
{
	if(x>=size || y>=size || x < 0|| y < 0)		// If OUTSIDE of TTT board range
			return false;
	return true;
}

/*
 * Prints to the console a visual representation of
 * a TTT board, with its marked values.
 */
void TicTacToeBoard::displayBoard()
{
	string threeSpaces = "   ";
	string twoSpaces = "  ";
	char vertLine = '|', horiLine = '-';

	cout << "    ";
	for(int i=0; i<size; ++i)
		cout << (i+1) << threeSpaces;
	cout << endl<<endl;

	for(int i=0, rows = board.size(); i<rows; ++i)
	{
		cout << (i+1) << twoSpaces;									// Print row number
		for(int j=0, loop2 = board.at(i).size(); j<loop2; ++j) 		// Print row content & vertical lines
		{
			cout << " " << board.at(i).at(j) << " ";				// Print content of that space
			if(j!=loop2-1)											// Print Vertical Line/ Divider
				cout << vertLine;        								// if not last column
		}

		cout <<endl;												// Move to next line...

		if(i==rows-1)                                           // On last iteration, Dont print
			continue;                                           // another horizonal line.

	   cout << threeSpaces;
		for(int k=0, numRowLines = (size*4)-1; k<numRowLines; k++)           // Print horizontal lines
			cout << horiLine;
		cout <<endl;												// Move to next row...

	}
	cout << endl;
}

/*
 * FOR USERS,
 * 		Enters a coordinate to mark the cell with their symbol [EX: 'x' or 'o']
 * 		Before marking the cell, the coordinates are checked by 'isSpaceOpen()'
 * 		function. The taken cell is then removed from the vector of 'blankSpaces'.
 *
 *	@ return - TRUE is returned if marking of the cell was
 * 	 		   successful.
 *
 * 	 		 - FALSE is returned if cell wasnt marked due to being
 * 	 		   not in the range of the board, negative x&y values, or
 * 	 		   cell isnt available and is occupied.*
 */
bool TicTacToeBoard::markCell(int x, int y, char sym)
{
	bool spotAvailable;
	spotAvailable = isCellOpen(x,y);

	int cellNum = (y*size)+x;			// FORMULA: retrieves cellNum from X & Y coor.
	if(spotAvailable)
	{
		board.at(y).at(x) = sym;
		blankSpaces.erase(
				std::remove(blankSpaces.begin(), blankSpaces.end(), cellNum), blankSpaces.end());

		lastCellMarked = cellNum;
		return true;
	}
	return false;
}

/*
 * FOR AI/COMPUTER,
 * 		Enters a CELL to mark with the symbol [EX: 'x' or 'o']
 * 		Before marking the cell, the coordinates are checked by 'isSpaceOpen()'
 * 		function. The taken cell is then removed from the vector of 'blankSpaces'.
 * 	@ return - TRUE is returned if marking of the cell was
 * 	 		   successful.
 *
 * 	 		 - FALSE is returned if cell wasnt marked due to being
 * 	 		   not in the range of the board, negative x&y values, or
 * 	 		   cell isnt available and is occupied.
 */
bool TicTacToeBoard::markCell(int cellNum, char sym)
{
	int x, y;
	x = cellNum % size;			//	FORMULA: retrieves X coor from cell num
	y = cellNum / size;			//  	 	 retrieves Y coor from cell num

	bool spotAvailable;
	spotAvailable = isCellOpen(x,y);

	if(spotAvailable)
	{
		board.at(y).at(x) = sym;		// Sets the symbol at the cell/space
		blankSpaces.erase(				// Remves the cell the was taken up from list of blankspaces
				std::remove(blankSpaces.begin(), blankSpaces.end(), cellNum), blankSpaces.end());

		lastCellMarked = cellNum;

		return true;
	}
	return false;
}

/*
 * Self-Explanatory
 * @returns - randomCell that was randomly chosen
 *  		  OR
 *  		  -1 if TTT board is full w/ no more empty cells
 */
int TicTacToeBoard::markRandomEmptyCell(char sym)
{
	if(blankSpaces.size() == 0)
	{
		cout << "board is full" << endl;
		return -1;
	}

	int randomCell = blankSpaces.back();	// Gets an open cell from shuffle list
	blankSpaces.pop_back();					// Removes from list of open cells
	markCell(randomCell, sym);				// Marks the retrieved open cell w/ sym

	return randomCell;
}

/*
 * Self-Explanatory
 * @returns - randomCell that was randomly chosen
 *  		  OR
 *  		  -1 if TTT board is full w/ no more empty cells
 */
int TicTacToeBoard::getRandomEmptyCell()
{
	if(blankSpaces.size() == 0)
	{
		cout << "board is full" << endl;
		return -1;
	}
	random_shuffle(blankSpaces.begin(), blankSpaces.end());	// Shuffles the list of open cells
	int randomCell = blankSpaces.back();					// Peeks to the last item in that list

	return randomCell;								// Returns that value
}

int TicTacToeBoard::getSize()
{
	return size;
}

/*
 * Returns the cell that was last marked on
 * the TicTacToe board.
 */
int TicTacToeBoard::getLastCellMarked()
{
	return lastCellMarked;
}

/*
 * Returns the char occupying a specific cell
 * @returns - The char in the specific cell.
 * 			- '?' question mark if cell Num not on board.
 */
char TicTacToeBoard::getSymAtCell(int cellNum)
{
	int x = cellNum%size;
	int y = cellNum/size;

	if(isCellValid(x,y))
		return board.at(y).at(x);

	return '?';
}

/*
 * Returns the char occupying a specific x & y coor.
 * @returns - The char in the specific cell.
 * 			- '?' question mark if x & y is not on board.
 */
char TicTacToeBoard::getSymAtCell(int x, int y)
{
	if(isCellValid(x,y))
		return board.at(y).at(x);

	return '?';
}









