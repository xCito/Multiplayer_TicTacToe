/*
 * TicTacToeGame.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Juan
 */

#include <iostream>
#include <string>

#include "Player.h"
#include "HumanPlayer.h"
#include "Ai_Player.h"
#include "TicTacToeBoard.h"
#include "BoardChecker.h"

using namespace std;

int getNumberOfPlayer()
{
	int input;
	cout << "Enter number of players: ";
	cin >> input;

	return input;
}

int getNumberOfHuman()
{
	int input;
	cout << "How many Human players: ";
	cin >> input;

	return input;
}

void setPlayerSymbol(char sym)
{

}

int main()
{
	vector<Player*> players;
	int numPlayers = getNumberOfPlayer();
	int numHuman = getNumberOfHuman();

	cout << "You're X;"<<endl;
	players.push_back(new HumanPlayer('X'));
	players.at(0)->setAsHuman(true);

	for(int i=0; i<numPlayers-1; ++i)
	{
		string input;
		cout << "Choose symbol for other player: ";
		cin >>input;

		players.push_back(new Ai_Player(input[0]));
	}

	TicTacToeBoard board(numPlayers);
	BoardChecker checker(board,3);
	board.displayBoard();

	int turn=0;
	bool win = false;
	Player *master;

	while(!board.isFull() && !win)
	{
		master = players[turn%numPlayers];
		master->makeMove(board,0);
		board.displayBoard();

		win = checker.checkForWin(board.getLastCellMarked());
		if(win)
			break;


		cout << endl;

		turn++;
	}

	if(win)
	{
		(master->isPlayerHuman())? cout << "Human": cout << "AI ";
		cout << "Player "<< (turn%numPlayers)+1 <<" won" <<endl;
	}
	else
		cout << "It's a Tie!" << endl;

	cout << "GameOver..." <<endl;
	return 0;
}


