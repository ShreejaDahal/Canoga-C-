#pragma once
#pragma once
#pragma once
#include"Board.h"
#include"BoardView.h"
#include"Round.h"
#include"Human.h"
#include"Player.h"
#include"Round.h"
#include"Board.h"
#include"Human.h"
#include"Computer.h"
#include"Round.h"
#include"BoardView.h"
#include"Player.h"
#include<iostream>
#include<vector>
#include<stack>

class Game {

public:
	Game();
	void startNewGame();
	void startGame(Board board, Round round, Player player, Computer computer, Human human, BoardView boardDisplayoard, bool resume);
	void compPlaysNow(Board board, Round round, Player player, Computer computer, Human human, BoardView boardDisplay, bool resume);
	void startNewRound(string firstTurn, string winner, int winningScore, int humanScore, int compScore, stack<string>, int roundNum);
	int roll();
	void resumeGame();
	vector<int>getSquaresFromFile(string filename, string player);
	int getScoresFromFile(string filename, string player);
	string getTurnsFromFile(string filename, string turn);
	stack<string>getDiceRolls(string fileName);
	vector<int>getRolls(Round round);
	void saveGame(Board board, Round round, Player player);

	~Game();
};