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

/*
Function Name: getDiceRolls()
Purpose: Get dice rolls
Parameters: 
Return Value: diceRolls
Algorithm:
	1. Return the dice rolls from the file
*/


stack<string>&Round::getdiceRolls() {
	return diceRolls;
}

/*
Function Name: popRolls()
Purpose: Remove the top roll from the dice rolls
Parameters: stack of rolls
Return Value: None
Algorithm:
	1. Use .pop() to remove the top roll entry from the stack
*/

void Round::popRolls(stack<string>&stack) {
	stack.pop();
}

/*
Function Name: getTopRolls()
Purpose: Return the top roll from the dice rolls
Parameters: 
Return Value: roll
Algorithm:
	1. Use .top() to return the top roll entry from the stack
*/


string Round::getTopRolls() {
	stack<string>rolls = getdiceRolls();
	string roll = rolls.top();
	return roll;
}

/*
Function Name: getCurrentPlayer()
Purpose: Return the current player
Parameters: 
Return Value: the current player
Algorithm:
	1. Return the current player
*/

string Round::getCurrentPlayer() {
	return currentPlayer;
}

/*
Function Name: getNextPlayer()
Purpose: Return the next player
Parameters: 
Return Value: the next player
Algorithm:
	1. Return the next player
*/

string Round::getNextPlayer() {
	return nextPlayer;
}

/*
Function Name: getWinnerScore()
Purpose: Return the winner score
Parameters: 
Return Value: the winner score
Algorithm:
	1. Return the next player
*/

int Round::getWinnerScore() {
	return winnerScore;
}


/*
Function Name: getRoundNumber()
Purpose: Return the round number
Parameters: 
Return Value: the round number
Algorithm:
	1. Return the round number
*/

int Round::getRoundNumber() {
	return roundNumber;
}



/*
Function Name: coverables()
Purpose: Return the uncovered squares for each player
Parameters: Board object, player->player name
Return Value: uncovered_squares_human, uncovered_squares_computer
Algorithm:
	1. Return the uncovered squares for human or computer
*/


vector<int> Round::coverables(Board board, string player) {
	if (player == "Human") {
		return board.uncovered_squares_human();
	}
	else {
		return board.uncovered_squares_computer();
	}
}


/*
Function Name: uncoverables()
Purpose: Return the covered squares for each player
Parameters: Board object, player->player name
Return Value: covered_squares_human, covered_squares_computer
Algorithm:
	1. Return the covered squares for human or computer
*/


vector<int>Round::uncoverables(Board board, string player) {
	if (player == "Human") {
		return board.covered_squares_human();
	}
	else {
		return board.covered_squares_computer();
	}
}


/*
Function Name: checkIfWon()
Purpose: Check if either player has won the round
Parameters: Board object
Return Value: True if won, false otherwise
Algorithm:
	1. For each player, check if all their squares are covered, or all of their opponent's squares are uncovered.
	2. A player wins by either covering all their squares or by uncovering all their opponent's squares.
*/


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


/*
Function Name: isHandicapped()
Purpose: Check if handicap is on
Parameters: 
Return Value: return handicapped status
Algorithm:
	1. Return the handicap status
*/


bool Round::isHandicapped() {
	return handicapped;
}


/*
Function Name: setHandicapped()
Purpose: Initialize handicapped status
Parameters: handicapped->status
Return Value: 
Algorithm:
	1. Set handicapped status
*/


void Round::setHandicapped(bool handicapped) {
	this->handicapped = handicapped;
}


/*
Function Name: roundEndHumanScore()
Purpose: to get the scores for human at the end of the round
Parameters: Board object
Return Value: humanScore
Algorithm:
	1. If won by covering all squares, humanScore is the sum total of all uncovered squares of the computer.
	2. If won by uncovering all squares, compScore is the sum total of all covered squares of the human.
*/


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


/*
Function Name: roundEndCompScore()
Purpose: to get the scores for computer at the end of the round
Parameters: Board object
Return Value: compScore
Algorithm:
	1. If won by covering all squares, compScore is the sum total of all uncovered squares of the human.
	2. If won by uncovering all squares, humanScore is the sum total of all covered squares of the computer.
*/


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


/*
Function Name: announceWinner()
Purpose: to announce the winner for the round
Parameters: Player object
Return Value: 
Algorithm:
	1. If compScore is greater than the humanScore, announce the winner and the score for each player.
	2. If humanScore is greater than the compScore, announce the winner and the score for each player.
	3. If both players have equal score, announce it's a tie.

*/


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

/*
Function Name: setWinnerScore()
Purpose: Set winnerScore
Parameters: winnerScore -> the score of the winner
Return Value: None
Algorithm:
	1. Initialize the score of the winner
*/

void Round::setWinnerScore(int winnerScore) {
	this->winnerScore = winnerScore;
}

/*
Function Name: getFirstPlayer()
Purpose: to get the first player
Parameters: 
Return Value: firstPlayer
Algorithm:
	1. Return the firstPlayer of the round
*/


string Round::getFirstPlayer() {
	return firstPlayer;
}

/*
Function Name: ishumanFirstTurn()
Purpose: to check if human is the first player
Parameters: 
Return Value: humanFirstTurn status
Algorithm:
	1. Return the humanFirstTurn status
*/

bool Round:: ishumanFirstTurn() {
	return humanFirstTurn;
}


/*
Function Name: iscomputerFirstTurn()
Purpose: to check if computer is the first player
Parameters: 
Return Value: compFirstTurn status
Algorithm:
	1. Return the compFirstTurn status
*/


bool Round:: iscomputerFirstTurn() {
	return compFirstTurn;

}

/*
Function Name: sethumanFirstTurn()
Purpose: 
Parameters: humanFirstTurn -> human first turn status
Return Value: 
Algorithm:
	1. Initialize the humanFirstTurn status
*/


void Round:: sethumanFirstTurn(bool humanFirstTurn) {
	this->humanFirstTurn = humanFirstTurn;

}

/*
Function Name: setcomputerFirstTurn()
Purpose: 
Parameters: compFirstTurn -> computer first turn status
Return Value: 
Algorithm:
	1. Initialize the compFirstTurn status
*/


void Round:: setcomputerFirstTurn(bool compFirstTurn) {
	this->compFirstTurn = compFirstTurn;
}
/*
Function Name: setFirstPlayer()
Purpose: 
Parameters: FirstPlayer -> first player status
Return Value: 
Algorithm:
	1. Initialize the first player 
*/


void Round::setFirstPlayer(string firstPlayer) {
	this->firstPlayer = firstPlayer;
}

