#pragma once
#pragma once
#include<iostream>
#include"Round.h"
#include"Board.h"
#include"BoardView.h"
#include<vector>
using namespace std;

class Computer {
public:
	Computer();
	~Computer();
	int roll();
	bool toCoverOrUncover(Board board, Round round, string help);
	vector<int>getBestMove(vector<vector<int>>coverOptions, vector<vector<int>>uncoverOptions, Board board, Round round, BoardView boardDisplay, string help);
	vector<int>makeAMove(vector<vector<int>>moves, bool covOrUncov, Board board, Round round, BoardView boardDisplay);
	vector<vector<int>>threeSum(vector<int>& num, int target);
	vector<vector<int>>findPairs(vector<int>A, int target);
	vector<int>findFours(int target);
	vector <vector<int>>getAllOptions(vector<int>single, vector<vector<int>>findPairs, vector<vector<int>>threeSum, vector<int>findFours);
	bool throwOneDie(Board board);

};