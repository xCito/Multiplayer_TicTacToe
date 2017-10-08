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

void Ai_Player::makeMoveAI(TicTacToeBoard& board, int consecutive)
{
	cout << this->getName() << endl;
	int choice = rand() % 10;
	if(choice <= 2)
	{
		cout << "Going for a random Move" <<endl;
		makeEasyMove(board);
	}else
	{
		cout << "Going for a Defensive Move" <<endl;
		if(!makeHardMove(board, consecutive))
			{
			cout << "failed...."<< endl;
			makeEasyMove(board);
			}

	}

}

/*
 * Randomly chooses a cell on the TicTacToe board to mark
 * with its symbol.
 */
void Ai_Player::makeEasyMove(TicTacToeBoard& board)
{
	cout << "Ai, easy move: Random Choice" << endl;
	board.markRandomEmptyCell(getSymbol());
}

/*
 * Strategically chooses a cell on the TicTacToe board to mark
 * with its symbol.
 */
bool Ai_Player::makeHardMove(TicTacToeBoard& board, int neededToWin)
{
	// Block Procedure

	int threatCell, threatLevel;
	bool mustBlock = false;
	int winDir = -1;				//-1-HARMLESS, 0-vert, 1-hori, 2-diaBack, 3-diaFron
	int curCell;
	int size = board.getSize();
	vector<int> otherSymCell;

	getOtherSymbolLocations(board, otherSymCell);
	return blockOtherPlayer(board,otherSymCell, neededToWin);
}

/*
 * Gets the cell number of all 'Symbols' of the other players.
 * The cell numbers are stored into an vector.
 * @param  board - The TicTacToe board from where all opponents symbols will be stored.
 * @param  others - Collection cell numbers (location) of opponent symbols.
*/
void Ai_Player::getOtherSymbolLocations(TicTacToeBoard board,vector<int> &others)
{
	int size = board.getSize();
	char AiSym = getSymbol();

	for(int i=0; i<(size*size); ++i)
	{
		char curSym = board.getSymAtCell(i);
		//cout << curSym << ", ";					<--- DEBUG COMMENT
		if(curSym != AiSym && curSym != ' ')
		{
			others.push_back(i);
		}
	}
	cout <<endl;
}

/*
 * Attempts to block other players if theyre one-away from winning.
 * @param  board		- The TicTacToe board
 * @param  others		- Collection of cell numbers that are checked for close-to-winning.
 * @param  neededToWin  - Number of consecutive symbols needed to win.
 *
 */
bool Ai_Player::blockOtherPlayer(TicTacToeBoard& board,vector<int> others,int neededToWin)
{
	BoardChecker check(board);

	int size = board.getSize();
	vector<Threat> threat;
	int curCell, threatLevel;
	bool threatFound = false;

	// Iterate through list of opponent symbols on the board.
	for(int i=0, len = others.size(); i<len; i++)
	{
		curCell = others.at(i);			// current cell being monitored.
		int x = curCell%size;			// get X&Y coordinates of the cell.
		int y = curCell/size;

		threatLevel = check.getConsecutiveVert(x, y);
		if(threatLevel == neededToWin-1)		// Are they n-1 away from getting n?
		{
			//cout << "Possible Vertical Threat..." <<endl;
			isThreatVertical(board,threat,x,y);
		}

		threatLevel = check.getConsecutiveHori(curCell%size, curCell/size);
		if(threatLevel == neededToWin-1)
		{
			//cout << "Possible Horizontal Threat" <<endl;
			isThreatHorizontal(board,threat,x,y);
		}

		threatLevel = check.getConsecutiveBackDiag(curCell%size, curCell/size);
		if(threatLevel == neededToWin-1)
		{
			//cout << "Possible Back dia Threat" <<endl;
			isThreatBackDiagonal(board,threat,x,y);
		}

		threatLevel = check.getConsecutiveFronDiag(curCell%size, curCell/size);
		if(threatLevel == neededToWin-1)
		{
			//cout << "Possible Front Diag Threat" <<endl;
			isThreatFrontDiagonal(board,threat,x,y);
		}


	}
	/*
	for(int i=0; i<threat.size(); ++i)
	{
		cout << "--->";
		threat.at(i).displayThreat();
	}
	 */
	if(threat.empty())
		return false;

	Threat randomBlock = threat.at(rand()% threat.size());
	cout << "BLOCK -->" << board.getSymAtCell(randomBlock.xCoor, randomBlock.yCoor) << "at ("
				<< randomBlock.yCoor<<", " << randomBlock.xCoor << ") "<<endl;
	board.markCell(randomBlock.xCoor, randomBlock.yCoor, getSymbol());
	cout << "Ai, hard move: Strategic Choice" << endl;

	return true;
}

/*
 * Checks if symbol on TicTacToe board is a real threat VERTICALLY.
 *
 * @param  b - The tictactoe board
 * @param
 * @param
 * @param
 * @returns False - If symbol is already blocked.
 * 			      - If winning spots is out of bounds of Board.
 * 			True  - If There's an open cell that AI can use to block.
 */
void Ai_Player::isThreatVertical(TicTacToeBoard b, vector<Threat>& threats, int x, int y)
{
	char curSym = b.getSymAtCell(x,y);
	bool wasThreat = false;
	int shift = 0;
	while(true)
	{
		//Check Down
		if(b.getSymAtCell(x,y+shift) == curSym)
		{
			//cout << "\t"<< b.getSymAtCell(x,y+shift) << " was found, continue v" <<endl;
			shift++;
			continue;
		}
		else if(b.getSymAtCell(x, y+shift) == ' ')
		{
			if(!alreadyInVector(threats,Threat(x,y+shift)))
				threats.push_back(Threat(x,y+shift));
			//cout << "Spot open DOWN" <<endl;
			wasThreat = true;
			break;
		}
		break;
	}

	shift = 0;
	while(true)
	{
		//Check Up
		if(b.getSymAtCell(x,y-shift) == curSym)
		{
			//cout << "\t"<< b.getSymAtCell(x,y-shift) << " was found, continue ^" <<endl;
			shift++;
			continue;
		}
		else if(b.getSymAtCell(x, y-shift) == ' ')
		{
			if(!alreadyInVector(threats,Threat(x,y-shift)))
				threats.push_back(Threat(x,y-shift));
			//cout << "Spot open TOP" <<endl;
			break;
		}
		else
			break;
	}

	//cout << "False Alarm..." << endl;
}

void Ai_Player::isThreatHorizontal(TicTacToeBoard b, vector<Threat>& threats, int x, int y)
{
	char curSym = b.getSymAtCell(x,y);
	int shift = 0;
	while(true)
	{
		//Check Right
		if(b.getSymAtCell(x+shift,y) == curSym)
		{
			//cout << "\t"<< b.getSymAtCell(x+shift,y) << " was found, continue >" <<endl;
			shift++;
			continue;
		}
		else if(b.getSymAtCell(x+shift, y) == ' ')
		{
			if(!alreadyInVector(threats,Threat(x+shift,y)))
				threats.push_back(Threat(x+shift, y));
			//cout << "Spot open RIGHT" <<endl;
			//return true;
			break;
		}
		else
			break;
	}

	shift = 0;

	while(true)
	{
		//Check Left
		if(b.getSymAtCell(x-shift,y) == curSym)
		{
			//cout << "\t"<< b.getSymAtCell(x-shift,y) << " was found, continue <" <<endl;
			shift++;
			continue;
		}

		else if(b.getSymAtCell(x-shift, y) == ' ')
		{
			if(!alreadyInVector(threats,Threat(x-shift,y)))
				threats.push_back(Threat(x-shift,y));
			//cout << "Spot open LEFT" <<endl;
			break;
		}

		break;
	}

	//cout << "False Alarm..." << endl;
}

void Ai_Player::isThreatBackDiagonal(TicTacToeBoard b,vector<Threat>& threats,int x,int y)
{
	char curSym = b.getSymAtCell(x,y);
	int shift = 0;
	while(true)
	{
		//Check BotRight
		if(b.getSymAtCell(x+shift,y+shift) == curSym)
		{
			//cout << "\t"<< b.getSymAtCell(x+shift,y+shift) << " was found, continue \\v>" <<endl;
			shift++;
			continue;
		}

		else if(b.getSymAtCell(x+shift, y+shift) == ' ')
		{
			if(!alreadyInVector(threats,Threat(x+shift,y+shift)))
				threats.push_back(Threat(x+shift, y+shift));
			//cout << "Spot open BOT RIGHT" <<endl;
			//return true;
			break;
		}
		else
			break;
	}

	shift = 0;

	while(true)
	{
		//Check TopLeft
		if(b.getSymAtCell(x-shift,y-shift) == curSym)
		{
			//cout << "\t"<< b.getSymAtCell(x-shift,y-shift) << " was found, continue \\ ^<" <<endl;
			shift++;
			continue;
		}

		else if(b.getSymAtCell(x-shift, y-shift) == ' ')
		{
			if(!alreadyInVector(threats,Threat(x-shift,y-shift)))
				threats.push_back(Threat(x-shift, y-shift));
			//cout << "Spot open TOP LEFT" <<endl;
			break;
		}
		else
			break;
	}

	//cout << "False Alarm..." << endl;
}

void Ai_Player::isThreatFrontDiagonal(TicTacToeBoard b,vector<Threat>& threats,int x,int y)
{
	char curSym = b.getSymAtCell(x,y);
	int shift = 0;

	while(true)
	{
		//Check BotLeft
		if(b.getSymAtCell(x-shift,y+shift) == curSym)
		{
			//cout << "\t"<< b.getSymAtCell(x-shift,y+shift) << " was found, continue /v<" <<endl;
			shift++;
			continue;
		}

		else if(b.getSymAtCell(x-shift, y+shift) == ' ')
		{
			if(!alreadyInVector(threats,Threat(x-shift,y+shift)))
				threats.push_back(Threat(x-shift, y+shift));
			//cout << "Spot open BOT LEFT" <<endl;
			break;
		}
		else
			break;
	}
	while(true)
	{
		//Check Top-Right
		if(b.getSymAtCell(x+shift,y-shift) == curSym)
		{
			//cout << "\t"<< b.getSymAtCell(x+shift,y-shift) << " was found, continue /^>" <<endl;
			shift++;
			continue;
		}
		else if(b.getSymAtCell(x+shift, y-shift) == ' ')
		{
			if(!alreadyInVector(threats,Threat(x-shift,y-shift)))
				threats.push_back(Threat(x-shift, y-shift));
			//cout << "Spot open TOP RIGHT" <<endl;
			break;
		}
		else
			break;
	}

	//cout << "False Alarm..." << endl;
}

bool Ai_Player::alreadyInVector(vector<Threat> threats, Threat t)
{
	for(int i=0, len = threats.size(); i<len; ++i)
		if(threats.at(i).xCoor == t.xCoor && threats.at(i).yCoor == t.yCoor)
			return true;

	return false;
}
