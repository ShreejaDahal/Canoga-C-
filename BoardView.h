#pragma once
#pragma once
#include"Board.h"
#include"Player.h"
#include"Round.h"
#include<iostream>

class BoardView {
public:
	BoardView();
	~BoardView();
	void viewCompBoard(Board board, Player player, Round round);
	void viewHumanBoard(Board board, Player player, Round round);
};