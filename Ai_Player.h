/*
 * Ai_Player.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */

#include <iostream>
#include <string>
#include "Player.h"
#include "TicTacToeBoard.h"

using namespace std;

#ifndef AI_PLAYER_H_
#define AI_PLAYER_H_

class Ai_Player : public Player
{
public:
	Ai_Player();
	Ai_Player(char);
	Ai_Player(string);
	Ai_Player(string,char);
	~Ai_Player();

	void makeMoveAI(TicTacToeBoard&, int);
	void makeEasyMove(TicTacToeBoard&);
	void makeHardMove(TicTacToeBoard&);
private:

};



#endif /* AI_PLAYER_H_ */
