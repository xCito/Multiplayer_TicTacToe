/*
 * Player.cpp
 * Base Class
 *  Created on: Apr 13, 2017
 *      Author: Juan
 */

#include "Player.h"

Player::Player()
{
	symbol = '!';
	human = false;
	//cout << "Player constructor, Default" << endl;
}

Player::Player(char sym)
{
	symbol = sym;
	human = false;
	//cout << "Player constructor, char" << endl;
}

Player::Player(string n, char sym)
{
	name = n;
	symbol = sym;
	human = false;
	//cout << "Player constructor, string/char" << endl;
}

Player::~Player()
{
	//cout << "Player destructor..." <<endl;
}

char Player::getSymbol() const
{
	return symbol;
}

void Player::setSymbol(char sym)
{
	symbol = sym;
}

string Player::getName() const
{
	return name;
}

void Player::setName(string n)
{
	name = n;
}

bool Player::isPlayerHuman() const
{
	return human;
}

void Player::setAsHuman(bool value)
{
	human = value;
}
