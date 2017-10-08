/*
 * TicTacToeGame.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Juan
 */

#include <iostream>
#include <string>
#include <ctype.h>
#include <cmath>

#include "Player.h"
#include "HumanPlayer.h"
#include "Ai_Player.h"
#include "TicTacToeBoard.h"
#include "BoardChecker.h"

using namespace std;

int getIntInput(string);

int getNumberOfPlayer()
{
	int num = getIntInput("Enter number of players: ");
	while(num < 1)
	{
		cout << "Invalid input..." <<endl;
		num = getIntInput("Enter number of players: ");
	}

	return num;
}

int getNumberOfHuman(int numPlayers)
{
	int num = getIntInput("How many Human players: ");
	//cout << num <<endl;
	while(num < 0 || num > numPlayers)
	{
		cout << "Invalid number of Human players..." <<endl;
		num = getIntInput("How many Human players: ");
		cout << "-->" << num <<endl;
	}

	return num;
}

int getIntInput(string msg)
{
	int input;
	cout << msg;
	bool valid = cin >> input;
	cin.clear();
	cin.ignore(50, '\n');

	if(!valid)
		input = getIntInput(msg);

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
bool isValidSymbol(vector<Player*> otherPlayers, char sym)
{
	for(unsigned int i=0; i<otherPlayers.size(); i++)
	{
		if(otherPlayers.at(i)->getSymbol() == sym)
			return false;
	}
	return true;
}

char userSymbolChoice(vector<Player*> otherPlayers, string msg)
{
	char input = getStringInput(msg)[0];

	if(isalpha(input))
		input = toupper(input);

	while(!isValidSymbol(otherPlayers, input))
	{
		cout << "'" << input << "' is Taken, try again..." <<endl;
		input = userSymbolChoice(otherPlayers, msg);
	}

	return input;
}

int main()
{
	vector<Player*> players;
	int numPlayers = getNumberOfPlayer();
	int numHuman = getNumberOfHuman(numPlayers);
	int consec = 3; 						// <-- CHANGE THIS determines how many in a row is needed to win.
	cout << "** " << consec <<" in a row is needed to win **" <<endl;
	string input;

	// Adding human players to the line up
	for(int i=0; i<numHuman; i++)
	{
		string msg = "Choose symbol/character/number for Human Player " + std::to_string(i+1) + ": ";
		input = userSymbolChoice(players, msg);
		players.push_back(new HumanPlayer("Human Player " + std::to_string(i+1),input[0]));
		players.back()->setAsHuman(true);
	}

	// Adding AI players to the line up
	for(int i=0; i<numPlayers-numHuman; i++)
	{
		string msg = "Choose symbol for AI player " + std::to_string(i+1) + ": ";
		input = userSymbolChoice(players, msg);
		players.push_back(new Ai_Player("AI Player " + std::to_string(i+1),input[0]));
	}

	TicTacToeBoard board(numPlayers);
	BoardChecker checker(board, consec);
	board.displayBoard();

	int turn= rand()%numPlayers;
	bool win = false;
	Player *master;

	while(!board.isFull() && !win)
	{
		for(int i=0; i<20;i++)
			cout << "/\\";
		cout <<endl;

		master = players[turn%numPlayers];
		master->makeMove(board,consec);
		board.displayBoard();

		checker.getCellInformation(board.getLastCellMarked()%board.getSize(),

				board.getLastCellMarked()/board.getSize() );
		win = checker.checkForWin(board.getLastCellMarked());
		if(win)
			break;


		cout << endl;

		turn++;
	}

	if(win)
		cout << master->getName() << " Wins! (" <<
				master->getSymbol()<< ")" << endl;
	else
		cout << "It's a Tie!" << endl;

	cout << "GameOver..." <<endl;
	return 0;
}


