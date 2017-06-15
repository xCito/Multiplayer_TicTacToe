/*
 * TicTacToeBoard.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#ifndef TICTACTOEBOARD_H_
#define TICTACTOEBOARD_H_

class TicTacToeBoard
{
public:
	TicTacToeBoard();		// Constructor Default
	TicTacToeBoard(int);	// Constructor, int			(num of players if >=2)
	~TicTacToeBoard();

	bool markCell(int, int, char);
	bool markCell(int,char);
	void createNewBoard();
	bool isFull();
	void displayBoard();
	bool isCellOpen(int,int);
	bool isCellValid(int,int);
	int markRandomEmptyCell(char);
	int getRandomEmptyCell();
	int getLastCellMarked();
	char getSymAtCell(int cellNum);
	char getSymAtCell(int x, int y);
	vector< vector<char> > getBoard();
	int getSize();

private:
	int size;
	vector< vector<char> > board;
	vector<int> blankSpaces;
	int lastCellMarked;
	void createBoard(int);
};



#endif /* TICTACTOEBOARD_H_ */
