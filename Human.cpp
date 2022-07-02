#include"Human.h"
#include"Board.h"
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

/*
Function Name: ~Human()
Purpose: Initialize Human object
Parameters: None
Return Value: None
Algorithm:
    1. Deconstruct Human Object

*/

Human::Human() {}

/*
Function Name: ~Human()
Purpose: De-initialize Human object
Parameters: None
Return Value: None
Algorithm:
    1. Deconstruct Human Object

*/

Human::~Human() {}

/*
Function Name: roll_dice()
Purpose: Generate random numbers to be used as dice rolls for human player
Parameters: None
Return Value: None
Algorithm:
    Use srand() function to generate random numbers
*/

int Human::roll_dice() {
    srand(time(0));
    int number;
    static int flag = 1;
    if (flag == 1) {
        flag = 0;
    }
    number = rand() % 6 + 1;

    return number;
};

/*

Function Name: canthrowOneDice
Purpose: To decide if computer wants to throw one die or two dice
Parameters: Board object
Return Value: Return true if one die, false otherwise
Algorithm:
    1) If all the squares from 7 to n are covered for computer squares, throw one die, throw two dice otherwise
*/

bool Human::canThrowOneDie(Board board) {

    bool oneDie = false;

    for (int i = 6; i < board.covered_squares_human().size(); i++) {
        if (board.covered_squares_human()[i] == 0) {
            oneDie == false;
        }
    }

    if (oneDie == false) {
        return false;
    }
    else {
        return true;
    }
}



