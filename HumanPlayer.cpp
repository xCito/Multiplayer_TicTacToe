/*
 * HumanPlayer.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() : Player()
{
	//cout << "HumanPlayer constructor, default" << endl;
}

HumanPlayer::HumanPlayer(char sym) : Player(sym)
{
	//cout << "HumanPlayer constructor, char" << endl;
}

HumanPlayer::HumanPlayer(std::string n, char sym) : Player(n,sym)
{
	//cout << "HumanPlayer constructor, string/char" << endl;
}

HumanPlayer::~HumanPlayer()
{
	//cout << "HumanPlayer destructor..." <<endl;
}

void HumanPlayer::makeMoveHuman(TicTacToeBoard& board)
{
	int x, y;
	cout << "Human player makemove" << endl;
	do{

		do{
			y = promptUser("Choose Row: ");
			y-=1;
		}while(!inputValidation(y, board.getSize()));

		do{
			x = promptUser("Choose Col: ");
			x-=1;
		}while(!inputValidation(x, board.getSize()));

	}
	while(!board.isCellOpen(x,y));

	board.markCell(x,y,getSymbol());
}

bool HumanPlayer::inputValidation(int coor, int boardSize)
{
	if(coor < boardSize && coor >= 0)
		return true;

	cout << "You are outside of the board's range" <<
			", Try Again..." << endl;
	return false;
}

int HumanPlayer::promptUser(string msg)
{
	int input;
	cout << getName() << msg;
	cin >> input;

	return input;
}

