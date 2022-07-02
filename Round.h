#pragma once
#pragma once
#include<iostream>
#include<string>
#include"Board.h"
#include"Player.h"
#include<stack>
using namespace std;

class Round {

public:
	Round();
	~Round();

	void setCurrentPlayer(string);
	void setNextPlayer(string);
	void setWinnerScore(int);
	void setRoundNumber(int);

	string getCurrentPlayer();
	string getNextPlayer();
	int getWinnerScore();
	int getRoundNumber();
	vector<int>coverables(Board board, string player);
	vector<int>uncoverables(Board board, string player);
	bool checkIfWon(Board board);
	void setFirstTurn(bool firstTurn);
	bool isFirstTurn();
	void setDiceRolls(stack<string>diceRolls);
	stack<string>&getdiceRolls();
	string getTopRolls();
	bool isHandicapped();
	void setHandicapped(bool handicapped);
	int roundEndCompScore(Board board);
	int roundEndHumanScore(Board board);
	void announceWinner(Player player);
	void setFirstPlayer(string player);
	string getFirstPlayer();
	void popRolls(stack<string>& stack);
	bool ishumanFirstTurn();
	bool iscomputerFirstTurn();
	void sethumanFirstTurn(bool humanFirstTurn);
	void setcomputerFirstTurn(bool compFirstTurn);

private:
	string currentPlayer;
	string nextPlayer;
	int winnerScore = 0;
	int roundNumber = 1;
	bool firstTurn = true;
	stack<string>diceRolls;
	bool handicapped = false;
	bool humanFirstTurn = true;
	bool compFirstTurn = false;
	string firstPlayer;
};