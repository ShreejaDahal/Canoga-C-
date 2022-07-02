#pragma once
#pragma once
#include<iostream>
#include"Board.h"
#include<vector>
using namespace std;

class Human {
public:
	Human();
	~Human();
	int roll_dice();
	bool canThrowOneDie(Board board);
};