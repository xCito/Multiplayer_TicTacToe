/*
 * BoardChecker.cpp
 *
 *  Created on: Apr 15, 2017
 *      Author: Juan
 */

#include "BoardChecker.h"

/*
 * CONSTRUCTOR
 * 		@param TicTacToeBoard - TTT board object class.
 */
BoardChecker::BoardChecker(TicTacToeBoard& b)
{
	board = &b;
	neededToWin = 3;
}


/*
 * CONSTRUCTOR
 * 	@param TicTacToeBoard - TTT board object class.
 * 	@param num - The number of symbols in a row/col/diag
 * 				 needed to win.
 */
BoardChecker::BoardChecker(TicTacToeBoard& b, int num)
{
	board = &b;
	neededToWin = num;
}


/*
 * DESTRUCTOR,
 */
BoardChecker::~BoardChecker(){

}

//////////////////////////////////////////////////////////////////////

/*
 * Checks the lastly placed symbol on the TTT board to
 * see if its neighboring symbols connects to meet the
 * number of needed symbols in a row/col/diag to win.
 *
 * @param - the cellNum to a specific spot on the TTT board.
 * @return - TRUE if # of symbols needed to be connected is met
 * 			 FALSE if # of symbols needed to be connected is not met.
 */
bool BoardChecker::checkForWin(int cellNum)
{
	int size = board->getSize();
	int x = cellNum%size;
	int y = cellNum/size;
	char symbol = board->getSymAtCell(cellNum);

	//cout << "Checking for '" << symbol << "' symbol"<<endl;

	bool v = checkVertical(x,y,symbol);
	bool h = checkHorizontal(x,y,symbol);
	bool d = checkDiagonals(x,y,symbol);
	if(v|| h ||d)
		return true;
	return false;
}

/*
 * Checks the lastly placed symbol on the TTT board to
 * see if its neighboring symbols connects to meet the
 * number of needed symbols in a row/col/diag to win.
 *
 * @param x - The x coordinate (col) of specific cell.
 * @param y - The y coordinate (row) of specific cell.
 * @return  - TRUE if # of symbols needed to be connected is met
 * 			  FALSE if # of symbols needed to be connected is not met.
 */
bool BoardChecker::checkForWin(int x, int y)
{
	char symbol = board->getSymAtCell(x,y);
	cout << "Checking for '" << symbol << "' symbol"<<endl;
	bool v = checkVertical(x,y,symbol);
	bool h = checkHorizontal(x,y,symbol);
	bool d = checkDiagonals(x,y,symbol);
	if(v|| h ||d)
		return true;
	return false;
}

/*
 * VERTICAL CHECK,
 * 		Checks to the left and right of the specific cell to find multiple
 * 		symbols of the same char. Once the symbol to the
 * 		right or left is not the same as the specific cell, loop breaks and
 * 		continues down.
 * 	@param x   - The x(col) coordinate of specific cell
 * 	@param y   - The y(row) coordinate of specific cell
 * 	@param sym - The symbol/char of specific cell.
 */
bool BoardChecker::checkVertical(int x, int y, char sym)
{
	int consecutive = 0;
	int checkDistance = neededToWin;
	char currentSym;

// CHECK DOWN
	for(int i=0; i<checkDistance; ++i)			// Checks current below and below
	{
		currentSym = board->getSymAtCell(x,y+i);
		if(sym != currentSym)
			break;
		++consecutive;
	}

// CHECK UP
	for(int i=1; i<checkDistance; ++i)			// Checks above current cell
	{
		currentSym = board->getSymAtCell(x,y-i);
		if(sym != currentSym)
			break;
		++consecutive;
	}

	if(consecutive >= neededToWin)
		return true;

	return false;
}

/*
 * HORIZONTAL CHECK,
 * 		Checks above and below the specific cell to find multiple
 * 		dsymbols of the same char. Once the symbol to the
 * 		top or bottom of the specific cell is not the same, loop breaks and
 * 		continues down.
 * 	@param x   - The x(col) coordinate of specific cell
 * 	@param y   - The y(row) coordinate of specific cell
 * 	@param sym - The symbol/char of specific cell.
 */
bool BoardChecker::checkHorizontal(int x, int y, char sym)
{
	int consecutive = 0;
	int checkDistance = neededToWin;
	char currentSym;

// CHECK RIGHT
	for(int i=0; i<checkDistance; ++i)				// Checks current cell and to the right
	{
		currentSym = board->getSymAtCell(x+i,y);
		if(sym != currentSym)
			break;
		++consecutive;
	}

// CHECK LEFT
	for(int i=1; i<checkDistance; ++i)				// Checks to the right of current cell
	{
		currentSym = board->getSymAtCell(x-i,y);
		if(sym != currentSym)
			break;
		++consecutive;
	}

	if(consecutive >= neededToWin)
		return true;

	return false;
}

/*
 * DIAGONAL CHECKS,
 * 		Checks from top-left to bottom-right and top-right to bottom-left
 *		of the specific cell to find multiple symbols of the same char.
 *		Once the symbol to the top or bottom of the specific cell is not
 *		the same, loop breaks and continues down.
 * 	@param x   - The x(col) coordinate of specific cell
 * 	@param y   - The y(row) coordinate of specific cell
 * 	@param sym - The symbol/char of specific cell.
 */
bool BoardChecker::checkDiagonals(int x, int y, char sym)
{
	int consecutive = 0;
	int checkDistance = neededToWin;
	char currentSym;

// CHECK BOTTOM-RIGHT
	for(int i=0; i<checkDistance; ++i){
		currentSym = board->getSymAtCell(x+i,y+i);

		if(sym != currentSym)
			break;
		++consecutive;
	}

// CHECK TOP-LEFT
	for(int i=1; i<checkDistance; ++i){
		currentSym = board->getSymAtCell(x-i,y-i);

		if(sym != currentSym)
			break;
		++consecutive;
	}


	if(consecutive >= neededToWin)
			return true;
	consecutive = 0;						// RESET CONSECUTIVE COUNT

// CHECK TOP-RIGHT
	for(int i=0; i<checkDistance; ++i){
		currentSym = board->getSymAtCell(x+i,y-i);

		if(sym != currentSym)
			break;
		++consecutive;
	}

// CHECK BOTTOM-LEFT
	for(int i=1; i<checkDistance; ++i){			// Forward slash Diagonal
		currentSym = board->getSymAtCell(x-i,y+i);

		if(sym != currentSym)
			break;
		++consecutive;
	}

	if(consecutive >= neededToWin)
		return true;

return false;
}

/*
 * To apply a new board for when a new game is started.
 * @param TicTacToeBoard& - The TTT board that will be reviewed.
 */
void BoardChecker::setBoard(TicTacToeBoard& b)
{
	board = &b;
}

/*
 * Change the number number of symbols needed to be
 * consecutive in a row/col/diag
 * To EXPERIMENT with...
 * @param num - number of sym needed to win.
 */
void BoardChecker::setNumNeededToWin(int num)
{
	neededToWin = num;
}
