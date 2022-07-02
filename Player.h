#pragma once
#pragma once
#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Player {

public:
	Player();

	// constructor

	~Player();
	int getSum();
	int getHumanScore();
	int getCompScore();
	void setCompScore(int);
	void setHumanScore(int);
	vector<vector<int>>threeSum(vector<int>num, int target);
	vector<vector<int>>findPairs(vector<int>A, int target);
	vector<int>findFours(int target);
	vector <vector<int>>getAllOptions(vector<int>single, vector<vector<int>>findPairs, vector<vector<int>>threeSum, vector<int>findFours);


private:
	int compScore = 0;
	int humanScore = 0;
	int totalHumanScore;
	int totalCompScore;
	int totalSum;
};