/*
 * Ai_Player.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */

#include "Ai_Player.h"

Ai_Player::Ai_Player() : Player()
{
	//cout << "Ai_Player constructor, default" << endl;
}

Ai_Player::Ai_Player(char sym) : Player(sym)
{
	//cout << "Ai_Player constructor, char" << endl;
}

Ai_Player::Ai_Player(std::string n, char sym) : Player(n, sym)
{
	//cout << "Ai_Player constructor, string/char" << endl;
}

Ai_Player::~Ai_Player()
{
	//cout << "Ai_Player destructor..." <<endl;
}

void Ai_Player::makeMoveAI(TicTacToeBoard& board, int difficulty)
{
	cout << "Ai, make move" << endl;

	if(difficulty==0)
		makeEasyMove(board);
	else
		makeHardMove(board);

}
void Ai_Player::makeEasyMove(TicTacToeBoard& board)
{
	cout << "Ai, easy move: Random Choice" << endl;
	board.markRandomEmptyCell(getSymbol());
}
void Ai_Player::makeHardMove(TicTacToeBoard& board)
{
	cout << "Ai, hard move: Strategic Choice" << endl;
}
