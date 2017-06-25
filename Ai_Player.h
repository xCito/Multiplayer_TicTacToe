/*
 * Ai_Player.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Player.h"
#include "TicTacToeBoard.h"
#include "BoardChecker.h"

using namespace std;

#ifndef AI_PLAYER_H_
#define AI_PLAYER_H_

struct Threat
{
	int xCoor;
	int yCoor;

	Threat(int x,int y) : xCoor(-1), yCoor(-1)
	{
		xCoor = x;
		yCoor = y;
	}

	void displayThreat()
	{
		cout <<"(" << yCoor+1 << ", "<< xCoor+1 <<")" <<endl;
	}
};

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
	bool makeHardMove(TicTacToeBoard&,int);
	void getOtherSymbolLocations(TicTacToeBoard,vector<int>&);
	bool blockOtherPlayer(TicTacToeBoard&, vector<int>, int);
	bool isBlockPossible(TicTacToeBoard,int,int,int,int&,int&);
	void isThreatVertical(TicTacToeBoard,vector<Threat>&,int,int);
	void isThreatHorizontal(TicTacToeBoard,vector<Threat>&,int,int);
	void isThreatBackDiagonal(TicTacToeBoard,vector<Threat>&,int,int);
	void isThreatFrontDiagonal(TicTacToeBoard,vector<Threat>&,int,int);
	bool alreadyInVector(vector<Threat>, Threat);


private:

};


#endif /* AI_PLAYER_H_ */
