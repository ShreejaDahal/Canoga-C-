#include "Board.h"
#include <iostream>
#include <vector>
#include <string>

/*
Function Name: Board()
Purpose: Initialize board object and the number of squares for each player
Parameters: compSquares -> computer squares, humanSquares-> human squares, size -> number of squares
Return Value: None
Algorithm:
	1. Fill in values for uncovered squares and for covered squares

*/

Board::Board(vector<int>compSquares, vector<int>humanSquares, int size) {

	numOfSquares = size;
	for (int i = 0; i < size; i++) {
		comp_squares.push_back(compSquares[i]);
		human_squares.push_back(humanSquares[i]);
	}
}

/*
Function Name: Board()
Purpose: Initialize board object and the number of squares for each player
Parameters: compSquares -> computer squares, humanSquares-> human squares, size -> number of squares
Return Value: None
Algorithm:
	1. Fill 0's for uncovered squares and 1's for covered squares
*/

Board::Board(int n) {
	numOfSquares = n;
	for (int i = 0; i < n; i++) {
		comp_squares.push_back(0);
		human_squares.push_back(0);
	}
}

/*
Function Name: ~Board()
Purpose: De-initialize Board object
Parameters: None
Return Value: None
Algorithm:
	1. Deconstruct Board Object

*/
Board::~Board() {}

int Board::getBoardSize() {
	return numOfSquares;
}

/*
Function Name: covered_squares_human()
Purpose: Get all the covered squares for human player
Parameters: 
Return Value: covered squares
Algorithm:
	1. Create a list of squares that are covered for human

*/

vector<int> Board::covered_squares_human() {

	vector<int>covered_squares = {};
	for (int i = 0; i < getBoardSize(); i++) {
		if (human_squares[i] == 1) {
			covered_squares.push_back(i + 1);
		}
	}
	return covered_squares;
}
/*
Function Name: covered_squares_computer()
Purpose: Get all the covered squares for computer player
Parameters:
Return Value: covered squares
Algorithm:
	1. Create a list of squares that are covered for computer

*/
vector<int>Board::covered_squares_computer() {
	vector<int>covered_squares = {};
	for (int i = 0; i < getBoardSize(); i++) {
		if (comp_squares[i] == 1) {
			covered_squares.push_back(i + 1);
		}
	}
	return covered_squares;
}

/*
Function Name: uncovered_squares_human()
Purpose: Get all the uncovered squares for human player
Parameters:
Return Value: uncovered squares
Algorithm:
	1. Create a list of squares that are uncovered for human

*/

vector<int> Board::uncovered_squares_human() {

	vector<int>uncovered_squares = {};
	for (int i = 0; i < getBoardSize(); i++) {
		if (human_squares[i] == 0) {

			uncovered_squares.push_back(i + 1);
		}
	}
	return uncovered_squares;
}

/*
Function Name: uncovered_squares_computer()
Purpose: Get all the uncovered squares for computer player
Parameters:
Return Value: uncovered squares
Algorithm:
	1. Create a list of squares that are uncovered for computer
*/

vector<int> Board::uncovered_squares_computer() {

	vector<int>uncovered_squares = {};
	for (int i = 0; i < getBoardSize(); i++) {
		if (comp_squares[i] == 0) {
			uncovered_squares.push_back(i + 1);
		}
	}
	return uncovered_squares;
}

bool Board::isCovered_human() {
	bool res = true;
	for (int i = 0; i < getBoardSize(); i++) {
		if (human_squares[i] == 0) {
			res = false;
		}
	}

	if (res == false) {
		return false;
	}
	else {
		return true;
	}

}

bool Board::isCovered_computer() {
	bool res = true;
	for (int i = 0; i < getBoardSize(); i++) {
		if (comp_squares[i] == 0) {
			res = false;;
		}
	}
	if (res == false) {
		return false;
	}
	else {
		return true;
	}

}

bool Board::isUnCovered_human() {
	bool res = true;
	for (int i = 0; i < getBoardSize(); i++) {
		if (human_squares[i] == 1) {
			res= false;
		}
	}
	if (res == false) {
		return false;
	}
	else {
		return true;
	}
}

bool Board::isUnCovered_computer() {
	bool res = true;
	for (int i = 0; i < getBoardSize(); i++) {
		if (comp_squares[i] == 1) {
			res = false;
		}
	}
	if (res == false) {
		return false;
	}
	else {
		return true;
	}
}

void Board::cover_human(int sum) {
	cout << "Human covered " << sum << endl;
	human_squares[sum - 1] = 1;
}
void Board::cover_comp(int sum) {
	cout << "Computer covered " << sum << endl;
	comp_squares[sum - 1] = 1;
}

void Board::uncover_human(int sum) {
	cout << "Computer uncovered " << sum << endl;
	human_squares[sum - 1] = 0;
}
void Board::uncover_comp(int sum) {
	cout << "Human uncovered " << sum << endl;
	comp_squares[sum - 1] = 0;
}

vector<bool> Board::getHumanSquares() {
	return human_squares;
}

vector<bool>Board::getCompSquares() {
	return comp_squares;
}

