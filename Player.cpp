#include "Player.h"
#include<algorithm>
#include <iostream>
#include <vector>


/*
Function Name: Player()
Purpose: Initialize Player object
Parameters:
Return Value: None
Algorithm:
	1. Constructor for Player Class

*/


Player::Player(){}


/*
Function Name: ~Player()
Purpose: Initialize Player object
Parameters:
Return Value: None
Algorithm:
	1. Constructor for Player Class

*/

Player::~Player(){}

/*
Function Name: getHumanScore()
Purpose: Get human score
Parameters:
Return Value: humanScore
Algorithm:
	1. Return the human Score.
*/


int Player::getHumanScore() {
	return humanScore;
}

/*
Function Name: getCompScore()
Purpose: Get computer score
Parameters:
Return Value: compScore
Algorithm:
	1. Return the computer Score.
*/

int Player::getCompScore() {
	return compScore;
}

/*
Function Name: setCompScore()
Purpose: Set computer score
Parameters: compScore -> Computer Score
Return Value: None
Algorithm:
	1. Initialize the computer Score.
*/


void Player::setCompScore(int compScore) {
	this->compScore = compScore;
}


/*
Function Name: setHumanScore()
Purpose: Set humna score
Parameters: humanScore -> Human Score
Return Value: None
Algorithm:
	1. Initialize the human Score.
*/

void Player::setHumanScore(int humanScore) {
	this->humanScore = humanScore;
}

/*
Function Name: threeSum()
Purpose: Generate a vector of all the 3 elements that add up to the target
Parameters: num -> vector that holds all the numbers, target->target number
Return Value: vector with all the 3 elements that add up to the target
Algorithm:
	1. Use of three for loop techniques to generate 3 numbers that add up to a target
*/


vector<vector<int>>Player::threeSum(vector<int>num, int target) {
	vector<vector<int>>result;
	sort(num.begin(), num.end());
	for (int i = 0; i < num.size(); i++) {
		int j = i + 1;
		int k = num.size() - 1;
		while (j < k) {
			int sum = num[i] + num[j] + num[k];
			if (sum == target) {
				vector<int>triple(3);
				triple[0] = num[i];
				triple[1] = num[j];
				triple[2] = num[k];
				result.push_back(triple);
				j++;
				k--;
			}
			else if (sum > target) {
				k--;
			}
			else if (sum < target) {
				j++;
			}
		}
	}
	vector<vector <int> >rs(result.begin(), result.end());
	return rs;
}

/*
Function Name: findPairs()
Purpose: Generate a vector of all the 2 elements that add up to the target
Parameters: A -> vector that holds all the numbers, target->target number
Return Value: vector with all the 2 elements that add up to the target
Algorithm:
	1. Use of 2 for loop techniques to generate 2 numbers that add up to a target
*/


vector<vector<int>>Player::findPairs(vector<int>A, int target) {
	vector<vector<int>>result;
	for (int i = 0; i < A.size(); i++) {
		for (int j = i + 1; j < A.size(); j++) {
			if (A[i] + A[j] == target) {
				vector<int>pair(2);
				pair[0] = A[i];
				pair[1] = A[j];
				result.push_back(pair);
			}
		}
	}
	return result;
}

/*
Function Name: findFours()
Purpose: Return a vector of 4 numbers that add up to the target
Parameters: target->target number
Return Value: vector of 4 numbers that add up to the target
Algorithm:
	1. If the target is 10, return {1,2,3,4}
	2. If the target is 11, return {1,2,3,5}
	3. If the target is 12, return {1,2,3,6}
*/


vector<int>Player::findFours(int target) {

	if (target == 10) {
		vector<int>result = { 1,2,3,4 };
		return result;
	}
	else if (target == 11) {
		vector<int>result = { 1,2,3,5 };
		return result;
	}
	else if (target == 12) {
		vector<int>result = { 1,2,3,6 };
		return result;
	}
}


/*
Function Name: getAllOptions()
Purpose: Merge all the coverables/uncoverable options in one single vector
Parameters: single -> vector with one element, findPairs -> vectors with combinations of two, threeSum -> vectors with combinations of three, findFours -> vector with combination of 4
Return Value: vector of all the possible combinations
Algorithm:
	1. In an empty vector, push back all the possible combinations
*/


vector <vector<int>>Player::getAllOptions(vector<int>single, vector<vector<int>>findPairs, vector<vector<int>>threeSum, vector<int>findFours) {

	vector<vector<int>>options;
	for (int i = 0; i < findPairs.size(); i++) {
		options.push_back(findPairs[i]);
	}

	for (int i = 0; i < threeSum.size(); i++) {
		options.push_back(threeSum[i]);
	}

	if (findFours.size() > 0) {
		options.push_back(findFours);
	}
	if (single.size() == 1) {
		options.push_back(single);
	}

	return options;
}