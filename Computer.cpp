#include"Computer.h"
#include"Round.h"
#include"Board.h"
#include"BoardView.h"
#include<algorithm>
#include<iostream>
using namespace std;


/*
Function Name: Computer()
Purpose: Initialize Computer object
Parameters:
Return Value: None
Algorithm:
	1. Constructor for Computer Class

*/

Computer::Computer() {}

/*
Function Name: ~Computer()
Purpose: De-initialize Computer object
Parameters: None
Return Value: None
Algorithm:
	1. Deconstruct Computer Object

*/

Computer::~Computer() {}

/*
Function Name: roll
Purpose: Generate random numbers to be used as dice rolls for computer player
Parameters: None
Return Value: None
Algorithm:
	Use srand() function to generate random numbers
*/


int Computer::roll() {
	srand(time(0));
	int number;
	static int flag = 1;
	if (flag == 1) {
		flag = 0;
	}
	number = rand() % 6 + 1;
	return number;
}

/*
Function Name : toCoverOrUncover
Purpose : To decide whether to cover or uncover
Parameters : Board object, Round object, hrlp -> true/false based on whether the user asked for help
Return Value : true for cover, false otherwise
Algorithm :
1) If the opponent has more uncovered squares than self covered, cover own squares
2) If the opponent has more covered squares than self uncovered, uncover their squares
3) If the number of self covered squares equal the number of opponent's uncovered,
choose the side that gives more number of squares
*/

bool Computer::toCoverOrUncover(Board board, Round round, string help) {
	vector<int>coveredSquaresSelf;
	vector<int> uncoveredSquaresSelf;
	vector<int> coveredSquaresOpp;
	vector<int> uncoveredSquaresOpp;
	if (round.getCurrentPlayer() == "Computer") {
		coveredSquaresSelf = board.covered_squares_computer();
		uncoveredSquaresSelf = board.uncovered_squares_computer();

		coveredSquaresOpp = board.covered_squares_human();
		uncoveredSquaresOpp = board.uncovered_squares_human();
	}
	else if (round.getCurrentPlayer() == "Human") {
		coveredSquaresSelf = board.covered_squares_human();
		uncoveredSquaresSelf = board.uncovered_squares_human();

		coveredSquaresOpp = board.covered_squares_computer();
		uncoveredSquaresOpp = board.uncovered_squares_computer();
	}
	if (uncoveredSquaresOpp.size() <= 3 && uncoveredSquaresSelf.size() > 3) {
		cout << "Uncovering will minimize opponent's chances of winning. " << endl;
		return false;
	}
	if (coveredSquaresOpp.size() > uncoveredSquaresSelf.size()) {
		cout << "To maximize the number of covered squares and help the player win." << endl;
		return true;
	}

	else if (uncoveredSquaresOpp.size() > coveredSquaresSelf.size()) {
		cout << "Opponent has more uncovered squares. So, uncovering more squares will help win the game." << endl;
		return false;
	}
	
	else {
		int maxSquare = 1;
			for (int i = 0; i < coveredSquaresSelf.size(); i++) {
				if (coveredSquaresSelf[i] > maxSquare) {
					maxSquare = coveredSquaresSelf[i];
					//return true;
				}
			}
			//cout << "Uncovering will maximize opponent's uncovered squares and get more score." << endl;
			for (int i = 0; i < uncoveredSquaresOpp.size(); i++) {
				if (uncoveredSquaresOpp[i] > maxSquare) {
					return false;
				}
			}
		cout << "Covering will maximize the number of one's covered squares and minimize opponent's score." << endl;
		return true;
	}
}
/*
Function Name : getBestMove
Purpose : Get the best move
Parameters : squares_moves
Return Value : Return the best move
Algorithm :
1) Compare all the possible movesand return the move that has the highest number

*/

vector<int>Computer::getBestMove(vector<vector<int>>coverOptions, vector<vector<int>>uncoverOptions, Board board, Round round, BoardView boardDisplay, string help) {
	vector<int>moves = {};

	if (coverOptions.size() >= 1 && uncoverOptions.size() >= 1) {
		// if both cover and uncover options are available, find the best move
		if (toCoverOrUncover(board, round, help)) {
			if (help == "yes") {
				cout << "Suggestion to cover ";
			}
			moves = makeAMove(coverOptions, true, board, round, boardDisplay);
		}
		else {
			if (help == "yes") {
				cout << "Suggestion to uncover ";
			}
			moves = makeAMove(uncoverOptions, false, board, round, boardDisplay);
		}
	}

	else if (coverOptions.size() > 0 && uncoverOptions.size() <= 0) {
		// if only cover options is available, cover
		cout << " As there are no squares available for uncover, " << endl;
		moves = makeAMove(coverOptions, true, board, round, boardDisplay);
		if (help == "yes") {
			cout << "Suggestion to cover ";
		}
	}
	else if (uncoverOptions.size() > 0 && coverOptions.size() <= 0) {
		// if only uncover options is avaibale, uncover
		cout << " As there are no squares available for cover, " << endl;
		if (help == "yes") {
			cout << "Suggestion to uncover ";
		}
		moves = makeAMove(uncoverOptions, false, board, round, boardDisplay);
	}

	return moves;
}
/*

Function Name: makeAMove
Purpose: Computer either makes a move or suggests a move
Parameters: cover_squares_available, uncover_squares_available, hint
Return Value: Return the best move, to_cover_or_to_uncover, and the hint message
Algorithm:
	1) Determines which move optimizes the chances of winning and makes the move
	2) If hint is True, suggests the player to make a move that optimizes the chances of winning

*/

vector<int>Computer::makeAMove(vector<vector<int>>moves, bool covOrUncov, Board board, Round round, BoardView boardDisplay) {
	vector<int>bestMove = {};
	int maxSquare = 1;
	//BoardView boardDisplay;

	for (auto i = 0; i < moves.size(); i++) {
		for (auto j = 0; j < moves[i].size(); j++) {
			if (moves[i][j] > maxSquare) {
				maxSquare = moves[i][j];
				//cout << maxSquare << endl;
				bestMove = moves[i];

			}
			else if (moves[i][j] == maxSquare) {
				if (moves[i].size() < bestMove.size()) {
					bestMove = moves[i];
				}
			}
		}
	}
	return bestMove;
}

/*

Function Name: throwOneDice
Purpose: To decide if computer wants to throw one die or two dice
Parameters: Board object
Return Value: Return true if one die, false otherwise
Algorithm:
	1) If all the squares from 7 to n are covered for computer squares, throw one die, throw two dice otherwise
*/

bool Computer::throwOneDie(Board board) {

	bool oneDie = false;
	for (int i = 6; i < board.covered_squares_computer().size(); i++) {
		if (board.covered_squares_computer()[i] == 0) {
			oneDie = false;
		}
	}

	if (oneDie == false) {
		cout << "Computer decided to throw two dice. " << endl;
	}
	else {
		cout << "Computer decided to throw one die as all its 7 to n are covered " << endl;

	}
	return oneDie;
}
