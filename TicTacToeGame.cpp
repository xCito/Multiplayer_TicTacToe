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

int getIntInput(string);

int getNumberOfPlayer()
{
	return getIntInput("Enter number of players: ");
}

int getNumberOfHuman()
{
	return getIntInput("How many Human players: ");
}

int getIntInput(string msg)
{
	int input;
	cout << msg;
	cin >> input;
	cin.clear();
	cin.ignore(50, '\n');

	return input;
}
string getStringInput(string msg)
{
	string input;
	cout << msg;
	cin >> input;
	cin.clear();
	cin.ignore(50, '\n');

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
	string input;

	for(int i=0; i<numHuman; i++)
	{
		string msg = "Choose symbol for Human Player " + std::to_string(i+1) + ": ";
		input = getStringInput(msg);
		players.push_back(new HumanPlayer("Human Player " + std::to_string(i+1),input[0]));
		players.back()->setAsHuman(true);
	}

	for(int i=0; i<numPlayers-numHuman; i++)
	{
		string msg = "Choose symbol for AI player " + std::to_string(i+1) + ": ";
		input = getStringInput(msg);
		players.push_back(new Ai_Player("AI Player " + std::to_string(i+1),input[0]));
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


