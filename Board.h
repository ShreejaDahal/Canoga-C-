#pragma once
#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Board {
public:
	Board(int n);

	// constructor
	Board(vector<int>compSquares, vector<int>humanSquares, int size);

	~Board();

	vector<int>covered_squares_human();
	vector<int>covered_squares_computer();
	vector<int>uncovered_squares_human();
	vector<int>uncovered_squares_computer();
	vector<bool>getHumanSquares();
	vector<bool>getCompSquares();
	void cover_human(int);
	void cover_comp(int);
	void uncover_human(int);
	void uncover_comp(int);
	bool isCovered_human();
	bool isCovered_computer();
	bool isUnCovered_computer();
	bool isUnCovered_human();
	int getBoardSize();

private:
	int numOfSquares = 0;
	vector<bool>comp_squares;
	vector<bool>human_squares;
};