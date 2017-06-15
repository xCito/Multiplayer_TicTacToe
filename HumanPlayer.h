/*
 * HumanPlayer.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */
#include <iostream>
#include <string>
#include "Player.h"
#include "TicTacToeBoard.h"

using namespace std;

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

class HumanPlayer: public Player
{
public:
	HumanPlayer();					// Constructor Default
	HumanPlayer(char);				// Constructor Overloaded, char
	HumanPlayer(string, char);		// Constructor Overloaded, string/char
	~HumanPlayer();					// Destructor

	void makeMoveHuman(TicTacToeBoard&);
	bool inputValidation(int coor, int boardSize);
	int promptUser(string msg);

private:

};



#endif /* HUMANPLAYER_H_ */
