#include "Round.h"
#include "Player.h"
#include "Board.h"
#include<vector>
#include<iostream>
#include<string>
#include<stack>
using namespace std;

/*
Function Name: Round()
Purpose: Initialize Player object
Parameters:
Return Value: None
Algorithm:
	1. Constructor for Round Class

*/
Round::Round() {}

/*
Function Name: ~Round()
Purpose: De-initialize Round object
Parameters:
Return Value: None
Algorithm:
	1. Constructor for Round Class
*/


Round::~Round() {}


/*
Function Name: setCurrentPlayer()
Purpose: Set current player
Parameters: currentPlayer -> current player
Return Value: None
Algorithm:
	1. Initialize the current player.
*/

void Round::setCurrentPlayer(string currentPlayer) {
	this->currentPlayer = currentPlayer;
}

/*
Function Name: setNextPlayer()
Purpose: Set next player
Parameters: NextPlayer -> next player
Return Value: None
Algorithm:
	1. Initialize the next player.
*/


void Round::setNextPlayer(string nextPlayer) {
	this->nextPlayer = nextPlayer;
}

/*
Function Name: setRoundNumber()
Purpose: Set round number
Parameters: roundNumber -> round number
Return Value: None
Algorithm:
	1. Initialize the round number.
*/


void Round::setRoundNumber(int roundNumber) {
	this->roundNumber = roundNumber;
}

/*
Function Name: setFirstTurn()
Purpose: Set first turn
Parameters: firstTurn -> first Turn
Return Value: None
Algorithm:
	1. Initialize the first turn.
*/


void Round::setFirstTurn(bool firstTurn) {
	this->firstTurn = firstTurn;
}

/*
Function Name: isFirstTurn()
Purpose: Check if it's the first turn
Parameters: 
Return Value: return first turm
Algorithm:
	1. Return the first turn
*/

bool Round::isFirstTurn() {
	return firstTurn;
}

/*
Function Name: setDiceRolls()
Purpose: Set dice rolls
Parameters: diceRolls -> dice rolls from the saved file
Return Value: None
Algorithm:
	1. Initialize the dice rolls from the saved file
*/

void Round::setDiceRolls(stack<string>diceRolls) {
	this->diceRolls = diceRolls;
}

stack<string>&Round::getdiceRolls() {
	return diceRolls;
}

void Round::popRolls(stack<string>&stack) {
	stack.pop();
}

string Round::getTopRolls() {
	stack<string>rolls = getdiceRolls();
	string roll = rolls.top();
	return roll;
}

string Round::getCurrentPlayer() {
	return currentPlayer;
}
string Round::getNextPlayer() {
	return nextPlayer;
}
int Round::getWinnerScore() {
	return winnerScore;
}
int Round::getRoundNumber() {
	return roundNumber;
}
vector<int> Round::coverables(Board board, string player) {
	if (player == "Human") {
		return board.uncovered_squares_human();
	}
	else {
		return board.uncovered_squares_computer();
	}
}
vector<int>Round::uncoverables(Board board, string player) {
	if (player == "Human") {
		return board.covered_squares_human();
	}
	else {
		return board.covered_squares_computer();
	}
}
bool Round::checkIfWon(Board board) {
	bool haveWinner = 0;
		if (getCurrentPlayer() == "Computer") {
			if (board.isCovered_computer() || board.isUnCovered_human()) {
				haveWinner = true;

				if (board.isCovered_computer()) {
					cout << "Computer won by covering all its squares!! " << endl;
				}
				else {
					cout << "Computer won by uncovering all of human's squares!! " << endl;
				}
			}
		}
		else {
			if (board.isCovered_human() || board.isUnCovered_computer()) {
				haveWinner = true;

				if (board.isCovered_human()) {
					cout << "Human won by covering all its squares!! " << endl;
				}
				else {
					cout << "Human won by uncovering all of computer's squares!! " << endl;
				}


			}
		}
		if (haveWinner) {
			return true;
		}
		else {
			return false;
		}
}

bool Round::isHandicapped() {
	return handicapped;
}

void Round::setHandicapped(bool handicapped) {
	this->handicapped = handicapped;
}

int Round::roundEndHumanScore(Board board) {
	int humanScore = 0;

	if (board.isCovered_human()) {
		//human won by covering all its squares
		//in this case, we will calculate the squares of the uncovered ones
		for (int i = 0; i < board.getCompSquares().size(); i++) {
			if (board.getCompSquares()[i] == 0) {
				humanScore += i + 1;
			}
		}
	}

	else if(board.isUnCovered_computer()) {
		//human won by covering all its squares
		//in this case, we will calculate the squares of the uncovered ones
		for (int i = 0; i < board.getHumanSquares().size(); i++) {
			if (board.getHumanSquares()[i] == 1) {
				humanScore += i + 1;
			}
		}
	}

	return humanScore;

}

int Round::roundEndCompScore(Board board) {
	int compScore = 0;

	if (board.isCovered_computer()) {
		//comp won by covering all its squares
		//in this case, we will calculate the squares of the uncovered ones
		for (int i = 0; i < board.getHumanSquares().size(); i++) {
			if (board.getHumanSquares()[i] == 0) {
				compScore += i + 1;
			}
		}
	}
	else if (board.isUnCovered_human()) {
		//human won by covering all its squares
		//in this case, we will calculate the squares of the uncovered ones
		for (int i = 0; i < board.getCompSquares().size(); i++) {
			if (board.getCompSquares()[i] == 1) {
				compScore += i + 1;
			}
		}
	}
	return compScore;
}

void Round::announceWinner(Player player){

	if (player.getCompScore() > player.getHumanScore()) {
		cout << "The winner of the game is Computer " << endl;
		cout << "Computer Score: " << player.getCompScore() << endl;
		cout << "Human Score:    " << player.getHumanScore() << endl;
		setWinnerScore(player.getCompScore());
	}
	else if (player.getHumanScore() > player.getCompScore()) {
		cout << "The winner of the game is Human " << endl;
		cout << "Computer Score: " << player.getCompScore() << endl;
		cout << "Human Score:    " << player.getHumanScore() << endl;
		setWinnerScore(player.getCompScore());

	}
	else {
		cout << "The game is a tie. " << endl;
		cout << "Computer Score: " << player.getCompScore() << endl;
		cout << "Human Score:    " << player.getHumanScore() << endl;
	}
}

void Round::setWinnerScore(int winnerScore) {
	this->winnerScore = winnerScore;
}

string Round::getFirstPlayer() {
	return firstPlayer;
}

bool Round:: ishumanFirstTurn() {
	return humanFirstTurn;
}
bool Round:: iscomputerFirstTurn() {
	return compFirstTurn;

}
void Round:: sethumanFirstTurn(bool humanFirstTurn) {
	this->humanFirstTurn = humanFirstTurn;

}
void Round:: setcomputerFirstTurn(bool compFirstTurn) {
	this->compFirstTurn = compFirstTurn;
}

void Round::setFirstPlayer(string firstPlayer) {
	this->firstPlayer = firstPlayer;
}

