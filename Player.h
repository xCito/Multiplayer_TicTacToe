/*
 * Player.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */

#include <iostream>
#include <string>
#include "TicTacToeBoard.h"

using namespace std;

#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
	Player();				// Constructor Default
	Player(char);			// Constructor Overloaded
	Player(string, char);	// Constructor Overloaded
	virtual ~Player();				// Destructor

	char getSymbol() const;	// Accessor methods
	string getName() const;
	bool isPlayerHuman() const;

	void setName(string);	// Mutator methods
	void setSymbol(char);
	void setAsHuman(bool);

	virtual void makeMove(TicTacToeBoard& b, int x)
	{
		if(isPlayerHuman())
		{
			//cout << "player is human" << endl;
			makeMoveHuman(b);
		}
		else
		{
			//cout << "player is AI" <<endl;
			makeMoveAI(b, x);
		}
	}

	virtual void makeMoveHuman(TicTacToeBoard&){
		//cout << "no arg, Player Class" << endl;
	}

	virtual void makeMoveAI(TicTacToeBoard&, int diff)
	{
		//cout << "Arg, Player Class" << endl;
	}

private:
	char symbol;			// The data member
	string name;
	bool human;
};



#endif /* PLAYER_H_ */
