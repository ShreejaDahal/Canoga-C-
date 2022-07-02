#include "Board.h"
#include "BoardView.h"
#include "Player.h"
#include"Round.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*
Function Name: BoardView()
Purpose: Initialize BoardView object
Parameters: 
Return Value: None
Algorithm:
	1. Constructor for BoardView Class

*/

BoardView::BoardView() {}


/*
Function Name: ~BoardView()
Purpose: De-initialize Board object
Parameters: None
Return Value: None
Algorithm:
	1. Deconstruct BoardView Object

*/

BoardView::~BoardView() {}

/*
Function Name: viewCompBoard()
Purpose: View the computer player's board
Parameters: Board object, Round object, Player object
Return Value: None
Algorithm:
	1. Display Computer's score
	2. Display the round number
	3. Display covered and uncovered squares

*/


void BoardView::viewCompBoard(Board board, Player player, Round round) {
	cout << "=================COMPUTER BOARD======================" << endl;
	cout << "=================SCORE: " <<  player.getCompScore() <<"===========================" << endl;
	cout << "=================ROUND: " << round.getRoundNumber() <<"============================" << endl;


	for (int i = 0; i < board.getBoardSize(); i++) {
		if (board.getCompSquares()[i] == 1) {
			cout << "X | ";
		}
		else {
			cout << " " << i + 1 << " | ";

		}
	}

	cout << endl;
	cout << "====================================================="<< endl;
	cout << endl;
}

/*
Function Name: viewHumanBoard()
Purpose: View the human player's board
Parameters: Board object, Round object, Player object
Return Value: None
Algorithm:
	1. Display Human's score
	2. Display the round number
	3. Display covered and uncovered squares
*/

void BoardView::viewHumanBoard(Board board, Player player, Round round) {
	cout << "=================COMPUTER BOARD======================" << endl;
	cout << "=================SCORE: " << player.getHumanScore() << "===========================" << endl;
	cout << "=================ROUND: " << round.getRoundNumber() << "============================" << endl;

	for (int i = 0; i < board.getBoardSize(); i++) {
		if (board.getHumanSquares()[i] == 1) {
			cout << "X | ";
		}
		else {
			cout << " " << i + 1 << " | ";

		}
	}
	cout << endl;
	cout << "=====================================================" << endl;
	cout << endl;
}