/*
 * BoardChecker.h
 *
 *  Created on: Apr 15, 2017
 *      Author: Juan
 */

#include <iostream>
#include <vector>
#include "TicTacToeBoard.h"

using namespace std;

#ifndef BOARDCHECKER_H_
#define BOARDCHECKER_H_

class BoardChecker
{
public:
	BoardChecker(TicTacToeBoard&);
	BoardChecker(TicTacToeBoard&, int);
	~BoardChecker();

	void setBoard(TicTacToeBoard&);
	bool checkForWin(int);
	bool checkForWin(int,int);
	bool checkVertical(int,int,char);
	bool checkHorizontal(int,int,char);
	bool checkDiagonals(int,int,char);
	void getCellInformation(int);
	void getCellInformation(int,int);
	int getConsecutiveVert(int,int);
	int getConsecutiveHori(int,int);
	int getConsecutiveBackDiag(int,int);
	int getConsecutiveFronDiag(int,int);
	void setNumNeededToWin(int);
	int getNumNeededToWin();
private:
	TicTacToeBoard* board;
	int neededToWin;
};


#endif /* BOARDCHECKER_H_ */
