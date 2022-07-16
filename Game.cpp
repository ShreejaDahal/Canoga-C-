#include "Game.h"
#include "BoardView.h"
#include "Board.h"
#include"Round.h"
#include"Player.h"
#include"Computer.h"
#include"Human.h"
#include <iostream>
#include <string>
#include<ctime>
#include <algorithm>
#include<map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include<chrono>
#include<vector>
#include<thread>
#include<cmath>
#include<stack>
using namespace std;

/*
Function Name: Game
Purpose: Initialize a Game class
Parameters: None
Return Value: None
Algorithm:
	Give the user an option to choose to whether resume an old game or start a new one.
	Start a game as per the chosen option.
*/

Game::Game() {
	string gameInput;

	do {
		cout << "----------WELCOME TO THE CANOGA GAME-------------" << endl;
		cout << "How do you want to play the game? Resume an old game or start a new one? Enter 'r' to resume or 'n' to new." << endl;
		cin >> gameInput;

		if (gameInput == "n") {
			startNewGame();
		}
		else if (gameInput == "r") {
			resumeGame();
		}
	} while (gameInput != "n" && gameInput != "r");

}

/*
Function Name: ~Game()
Purpose: De-initialize Game object
Parameters: None
Return Value: None
Algorithm:
	1. Deconstruct Game Object
*/

Game::~Game() {}

/*
Function Name: roll
Purpose: Generate random numbers to be used as dice
Parameters: None
Return Value: None
Algorithm:
	Use srand() function to generate random numbers
*/

int Game::roll() {
	srand(time(0));
	int number;
	static int flag = 1;
	if (flag == 1) {
		flag = 0;
	}
	number = rand() % 6 + 1;
	return number;
}

/*
Function Name: startGame()
Purpose: To make moves for the human player for a new game
Parameters: Board object, Round object, Player object,Computer object, Human object, BoardView object
Return Value: None
Algorithm:
	1. Human rolls.(Either one or two based on the number of squares covered)
	2. Chooses whether they want to cover their own squares or uncover their opponents.
	3. Chooses their choices of squares
	4. Validates user's input
	5. Check whether human covered all their squares or uncovered all of computer's squares
	6. If either one of the above is true, declare the winner.
	7. If not, and if no moves available, computer gets the next turn.
*/

void Game::startGame(Board board, Round round, Player player, Computer computer, Human human, BoardView boardDisplay, bool resume) {

	int die1 = 0;
	int die2 = 0;
	string coverOrUncover = "";
	int choice = 0;
	vector<int>choices = {};
	int total = 0;
	bool valid = 0; // 1 is valid, 0 is invalid;
	string currentPlayer = round.getCurrentPlayer();
	string nextPlayer = round.getNextPlayer();
	int numOfChoices = 0;
	string roll;
	bool movesAvailable = 1;
	string play_again = " ";
	string help;
	vector<int>suggestedMove;
	bool vectorHasScore = false;

	//boardDisplay.viewHumanBoard(board, player, round);
	//boardDisplay.viewCompBoard(board, player, round);


	if (currentPlayer == "Human") {
		while (movesAvailable != 0 && currentPlayer == "Human") {
			valid = 0;
			int sum = 0;
			total = 0;
			vector<int>rolls;
			string numOfDie = "";
			while (roll != "r" || total == 0) {
				//cout << human.canThrowOneDie(board) << endl;
				if (human.canThrowOneDie(board) && round.getdiceRolls().size() <= 0) {
					while (numOfDie != "1" && numOfDie != "2") {
						cout << "Do you want to throw one die or two dice. Enter 1 for 1 die or 2 for 2 dice, or s to save the game for later " << endl;
						cin >> numOfDie;
						if (numOfDie == "1") {
							die1 = human.roll_dice();
							total = die1;
							roll = "r";
							cout << "Human rolled  " << die1 << ". The total is " << total << endl;

						}
						else if (numOfDie == "2") {
							die1 = human.roll_dice();
							die2 = human.roll_dice();
							total = die1 + die2;
							roll = "r";
							cout << "Human rolled  " << die1 << " and " << die2 << " The total is " << total << endl;

						}
						else if (roll == "s") {
							saveGame(board, round, player);
						}
						else {
							cout << "[WARNING] Invalid input" << endl;
						}
					}
				}
				else {
					cout << "Enter r to roll or s to save the game for later. " << endl;
					cin >> roll;
					if (roll == "r") {
						if (round.getdiceRolls().size() > 0) {
							rolls = getRolls(round);
							die1 = rolls[0];
							die2 = rolls[1];
							total = die1 + die2;
							round.getdiceRolls().pop();
							total = die1 + die2;
							cout << "Human rolled  " << die1 << " and " << die2 << " The total is " << total << endl;
						}
						else {
							if (human.canThrowOneDie(board)) {
								while (numOfDie != "1" && numOfDie != "2") {
									cout << "Do you want to throw one die or two dice. Enter 1 for 1 die or 2 for 2 dice. " << endl;
									cin >> numOfDie;
									if (numOfDie == "1") {
										die1 = human.roll_dice();
										total = die1;
										cout << "Human rolled  " << die1 << ". The total is " << total << endl;

									}
									else if (numOfDie == "2") {
										die1 = human.roll_dice();
										die2 = human.roll_dice();
										total = die1 + die2;
										cout << "Human rolled  " << die1 << " and " << die2 << " The total is " << total << endl;

									}
									else {
										cout << "[WARNING] You can only choose 1 die or 2 dice." << endl;
									}
								}
							}
							else {
								die1 = human.roll_dice();
								die2 = human.roll_dice();
								total = die1 + die2;
								cout << "Human rolled  " << die1 << " and " << die2 << " The total is " << total << endl;

							}
						}
					}
					else if (roll == "s") {
						saveGame(board, round, player);
					}
					else {
						cout << "[WARNING] Invalid input" << endl;
					}
				}
			}
			bool isCoverable;
			bool isunCoverable;

			vector<int>coverables = board.uncovered_squares_human();
			vector<int>uncoverables = board.covered_squares_computer();

			if (round.ishumanFirstTurn()) {
				vector <int> ::iterator itr;
				for (int i = 0; i < uncoverables.size(); i++) {
					if (uncoverables[i] == round.getWinnerScore()) {
						vectorHasScore = true;
						break;
					}
				}
				if (vectorHasScore) {
					itr = find(uncoverables.begin(), uncoverables.end(), round.getWinnerScore());
					uncoverables.erase(itr);
				}
			}

			/*
			cout << "Human Coverables are: " << endl;
			for (int i = 0; i < coverables.size(); i++) {
				cout << coverables[i] << " ";
			}
			cout << endl;
			cout << "Human Uncoverables are: " << endl;
			for (int i = 0; i < uncoverables.size(); i++) {
				cout << uncoverables[i] << " ";
			}
			cout << endl;
			*/

			vector<vector<int>>coverable_options;
			vector<vector<int>>uncoverable_options;
			vector<int>hasFour_coverables;
			vector<int>hasFour_uncoverables;


			if (total <= 2) {
				if (board.getHumanSquares()[total - 1] == 1) {
					isCoverable = false;
				}
				else {
					isCoverable = true;
					coverable_options.push_back({ total });
					//cout << "Your coverable option is: " << "( " << total << " ) " << endl;
				}

				if (board.getCompSquares()[total - 1] == 0) {
					isunCoverable = false;
				}
				else {
					isunCoverable = true;
					uncoverable_options.push_back({ total });
					//cout << "Your uncoverable option is: " << "( " << total << " ) " << endl;
				}

			}
			else {
				bool isSingleCoverable = false;
				bool isSingleunCoverable = false;
				vector<int>singleCover;
				vector<int>singleUncover;
				if (total <= board.getBoardSize()) {
					if (board.getHumanSquares()[total - 1] == 1) {
						isSingleCoverable = false;
					}
					else {
						isSingleCoverable = true;
						singleCover.push_back({ total });

					}

					if (board.getCompSquares()[total - 1] == 0) {
						isSingleunCoverable = false;
					}
					else {
						if (round.ishumanFirstTurn() == false) {
							isSingleunCoverable = true;
							singleUncover.push_back({ total });
						}
					}
				}
				if (total == 10 || total == 11 || total == 12) {
					vector<int>numbers = player.findFours(total);
					bool containsCov = includes(coverables.begin(), coverables.end(), numbers.begin(), numbers.end());
					if (containsCov) {
						hasFour_coverables = numbers;
					}
					bool containsUnCov = includes(uncoverables.begin(), uncoverables.end(), numbers.begin(), numbers.end());
					if (containsUnCov) {
						hasFour_uncoverables = numbers;
					}
				}
				vector<vector<int>>hasPairs_coverables = player.findPairs(coverables, total);
				vector<vector<int>>hasThree_coverables = player.threeSum(coverables, total);
				vector<vector<int>>hasPairs_uncoverables = player.findPairs(uncoverables, total);
				vector<vector<int>>hasThree_uncoverables = player.threeSum(uncoverables, total);


				if (hasPairs_coverables.size() > 0 || hasThree_coverables.size() > 0 || isSingleCoverable || hasFour_coverables.size() > 0) {
					isCoverable = 1;
					coverable_options = player.getAllOptions(singleCover, hasPairs_coverables, hasThree_coverables, hasFour_coverables);
				}

				else {
					isCoverable = 0;
				}
				if (hasPairs_uncoverables.size() > 0 || hasThree_uncoverables.size() > 0 || isSingleunCoverable || hasFour_uncoverables.size() > 0) {
					isunCoverable = 1;
					uncoverable_options = player.getAllOptions(singleUncover, hasPairs_uncoverables, hasThree_uncoverables, hasFour_uncoverables);
				}
				else {
					isunCoverable = 0;
				}

				/*
				cout << "Your cover options are: " << endl;
				for (int i = 0; i < coverable_options.size(); i++) {
					if (coverable_options[i].size() != 0) {
						cout << "(";
						if (coverable_options[i].size() == 1) {
							cout << total << " ) ";
						}
						else {
							for (int j = 0; j < coverable_options[i].size(); j++) {
								cout << coverable_options[i][j] << " ";
							}
							cout << "), ";
						}
					}
				}
				cout << endl;
				cout << "Your uncover options are: " << endl;
				for (int i = 0; i < uncoverable_options.size(); i++) {
					if (uncoverable_options[i].size() != 0) {
						cout << "(";
						if (uncoverable_options[i].size() == 1) {
							cout << total << " )";
						}
						else {
							for (int j = 0; j < uncoverable_options[i].size(); j++) {
								cout << uncoverable_options[i][j] << " ";
							}
							cout << "),  ";
						}
					}
				}
				cout << endl;
				*/
			}
			if (isCoverable || isunCoverable) {
				movesAvailable = 1;
				bool checkIfOptionAvailable = 0;

				while (checkIfOptionAvailable != 1) {
					cout << "Select cover or uncover.Enter c to cover, u to uncover. Or enter h to get help " << endl;
					cin >> coverOrUncover;
					if (coverOrUncover == "c" || coverOrUncover == "u") {
						if (coverOrUncover == "c" && coverable_options.size() == 0) {
							checkIfOptionAvailable = 0;
							cout << "[WARNING] No coverable options available at this time! " << endl;
						}
						else if (coverOrUncover == "u" && uncoverable_options.size() == 0) {
							checkIfOptionAvailable = 0;
							cout << "[WARNING] No uncoverable options available at this time! " << endl;
						}
						else {
							checkIfOptionAvailable = 1;
						}
					}
					else if (coverOrUncover == "h") {
						checkIfOptionAvailable = 0;
						//bool covOrunCov = computer.toCoverOrUncover(board, round);
						suggestedMove = computer.getBestMove(coverable_options, uncoverable_options, board, round, boardDisplay, "yes");
						for (int i = 0; i < suggestedMove.size(); i++) {
							cout << suggestedMove[i] << " ";
						}
						cout << endl;

					}
				}
				while (sum != total && valid != 1) {
					cout << "Choose your square. " << endl;
					while (!(cin >> choice)) {
						cin.clear();
						cin.ignore();
						cout << "[ERROR] Choose your square" << endl;
					}
					numOfChoices += 1;
					if (choice > board.getBoardSize()) {
						valid = 0;
					}
					else {
						// Validating the user input
						if (coverOrUncover == "c") {
							if ((board.getHumanSquares()[choice - 1] == 1)) {
								cout << " That is an invalid move. You can only cover squares that are not covered.Clearning all squares. ";
								valid = 0;
								sum = 0;
								numOfChoices = 0;
								choices.clear();
							}
							else if (board.getHumanSquares()[choice - 1] == 0) {
								sum += choice;
								choices.push_back(choice);
							}
						}
						else if (coverOrUncover == "u") {
							if ((board.getCompSquares()[choice - 1] == 0)) {
								cout << " That is an invalid move. You can only uncover squares that are already covered. Clearning all squares. ";
								valid = 0;
								sum = 0;
								numOfChoices = 0;
								choices.clear();

							}
							else {
								sum += choice;
								choices.push_back(choice);
							}
						}
					}
					if (sum == total && numOfChoices < 4) {
						if (coverOrUncover == "c") {
							cout << "-----Human is covering its choices of squares------" << endl;
							for (auto& it : choices) {
								board.cover_human(it);
							}
						}
						else {
							if (round.isFirstTurn() == false) {
								cout << "-----Human is uncovering opponent's squares------" << endl;
								for (auto& it : choices) {
									board.uncover_comp(it);
								}
							}
						}
						boardDisplay.viewHumanBoard(board, player, round);
						boardDisplay.viewCompBoard(board, player, round);
						choices.clear();
						if (round.isFirstTurn() == false) {
							if (round.checkIfWon(board)) {
								round.setWinnerScore(round.roundEndHumanScore(board));
								player.setHumanScore(round.roundEndHumanScore(board) + player.getHumanScore());
								boardDisplay.viewHumanBoard(board, player, round);
								boardDisplay.viewCompBoard(board, player, round);
								cout << "Current score is : "
									"Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << endl;
								cout << "Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								while (play_again != "y" && play_again != "n") {
									cin.clear();
									cin.ignore();
									cout << " Play again? Hit y for Yes, n for No" << endl;
									cin >> play_again;

									if (play_again == "y" || play_again == "n") {
										break;
									}
								}
								if (play_again == "y") {
									startNewRound(round.getFirstPlayer(), "Human", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
								}
								else {
									round.announceWinner(player);
									system("pause");
									exit(0);
								}
							}
						}
						else if (round.isFirstTurn() == true) {
							if (board.isCovered_human()) {

								cout << "Human won by covering all its squares. Current score is: '"
									"Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << endl;
								cout << "Play again> Hit 1 for Yes, 0 for No " << endl;
								cin >> play_again;
								while (play_again != "y" && play_again != "n") {
									cin.clear();
									cin.ignore();
									cout << "Play again? Hit y for Yes, n for No" << endl;
									cin >> play_again;

									if (play_again == "y" || play_again == "n") {
										break;
									}
								}
								round.setWinnerScore(round.roundEndHumanScore(board));
								player.setHumanScore(round.roundEndHumanScore(board) + player.getHumanScore());
								boardDisplay.viewHumanBoard(board, player, round);
								boardDisplay.viewCompBoard(board, player, round);
								system("pause");
								if (play_again == "y") {
									startNewRound(round.getFirstPlayer(), "Human", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
								}
								else {
									round.announceWinner(player);
									system("pause");
									exit(0);
								}
							}
						}
						numOfChoices = 0;
					}
					else if (sum > total) {
						sum = 0;
						cout << "[WARNING] The sum total of choices is greater than the total pips. Clearing all chosen squares. " << endl;
						numOfChoices = 0;
						choices.clear();

					}
					else if ( sum < total && numOfChoices > 3) {
						sum = 0;
						cout << "[WARNING] You can only choose up to four squares.Clearing all chosen squares. " << endl;
						numOfChoices = 0;
						choices.clear();
					}
					else {
						valid = 0;
					}
				}
			}
			else {
				movesAvailable = 0;
				cout << "No more moves available.Changing the players now. " << endl;
				if (round.isFirstTurn() == false) {
					if (round.checkIfWon(board)) {
						cout << "Current score is: '"
							"Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << endl;
						cout << "Play again? Hit 1 for Yes, 0 for No " << endl;
						cin >> play_again;
						while (play_again != "y" && play_again != "n") {
							cin.clear();
							cin.ignore();
							cout << " Play again? Hit y for Yes, n for No" << endl;
							cin >> play_again;

							if (play_again == "y" || play_again == "n") {
								break;
							}
						}
						round.setWinnerScore(round.roundEndHumanScore(board));
						player.setHumanScore(round.roundEndHumanScore(board) + player.getHumanScore());
						boardDisplay.viewHumanBoard(board, player, round);
						boardDisplay.viewCompBoard(board, player, round);
						if (play_again == "y") {
							startNewRound(round.getFirstPlayer(), "Human", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
						}
						else {
							round.announceWinner(player);
							system("pause");
							exit(0);
						}
					}
				}
				round.sethumanFirstTurn(false);
				round.setFirstTurn(false);
				round.setCurrentPlayer("Computer");
				round.setNextPlayer("Human");
			}
		}
	}
	compPlaysNow(board, round, player, computer, human, boardDisplay, resume);
}
/*
Function Name: compPlaysNow()
Purpose: To make moves for the computer player for a new game
Parameters: Board object, Round object, Player object,Computer object, Human object, BoardView object
Return Value: None
Algorithm:
	1. Computer rolls.(Either one or two based on the number of squares covered)
	2. Chooses whether they want to cover their own squares or uncover their opponents.
	3. Chooses their choices of squares
	4. Validates user's input
	5. Check whether computer covered all their squares or uncovered all of human's squares
	6. If either one of the above is true, declare the winner.
	7. If not, and if no moves available, human gets the next turn.
*/

void Game::compPlaysNow(Board board, Round round, Player player, Computer computer, Human human, BoardView boardDisplay, bool resume) {

	int die1 = 0;
	int die2 = 0;
	bool coverOrUncover;
	vector<int>choices = {};
	int total = 0;
	string currentPlayer = round.getCurrentPlayer();
	string nextPlayer = round.getNextPlayer();
	bool movesAvailable = 1;
	vector<int>move;
	string play_again = "";
	vector<int>rolls;
	string continueGame = "";

	//boardDisplay.viewHumanBoard(board, player, round);
	//boardDisplay.viewCompBoard(board, player, round);


	if (currentPlayer == "Computer") {
		while (movesAvailable != 0 && currentPlayer == "Computer") {
			total = 0;
			while (total == 0 || continueGame != "y") {
				cout << "Do you want to continue the game? Hit y if Yes or n if you want to save the game for later" << endl;
				cin >> continueGame;
				if (continueGame == "n") {
					saveGame(board, round, player);
				}
				else if (continueGame == "y") {
					if (round.getdiceRolls().size() > 0) {
						rolls = getRolls(round);
						die1 = rolls[0];
						die2 = rolls[1];
						total = die1 + die2;
						round.getdiceRolls().pop();
						cout << " Computer rolled  " << die1 << " and " << die2 << endl;
						cout << " The total is " << total << endl;
					}
					else {
						if (computer.throwOneDie(board)) {
							die1 = human.roll_dice();
							cout << " Computer rolled  " << die1 << endl;
							total = die1;
							cout << " The total is " << total << endl;
						}
						else {
							die1 = human.roll_dice();
							die2 = human.roll_dice();
							total = die1 + die2;
							cout << " Computer rolled  " << die1 << " and " << die2 << endl;
							cout << " The total is " << total << endl;
						}
					}
				}
				else {
					cout << "[WARNING] Invalid Input. Try again. " << endl;
				}
			}


			bool isCoverable;
			bool isunCoverable;
			bool vectorHasScore = false;

			vector<int>coverables = board.uncovered_squares_computer();
			vector<int>uncoverables = board.covered_squares_human();

			if (round.iscomputerFirstTurn()) {
				vector <int> ::iterator itr;
				for (int i = 0; i < uncoverables.size(); i++) {
					if (uncoverables[i] == round.getWinnerScore()) {
						vectorHasScore = true;
						break;
					}
				}
				if (vectorHasScore) {
					itr = find(uncoverables.begin(), uncoverables.end(), round.getWinnerScore());
					uncoverables.erase(itr);
				}
			}
			vector<vector<int>>coverable_options;
			vector<vector<int>>uncoverable_options;

			/*
			cout << "Computer's coverables are : " << endl;
			for (int i = 0; i < coverables.size(); i++) {
				cout << coverables[i] << " ";
			}
			cout << endl;

			cout << "Computer's uncoverables are : " << endl;
			for (int i = 0; i < uncoverables.size(); i++) {
				cout << uncoverables[i] << " ";
			}
			cout << endl;

			*/
			if (total <= 2) {
				if (board.getCompSquares()[total - 1] == 1) {
					isCoverable = false;
				}
				else {
					isCoverable = true;
				}

				if (board.getHumanSquares()[total - 1] == 0) {
					isunCoverable = false;
				}
				else {
					isunCoverable = true;
				}

				if (isCoverable && isunCoverable == false) {
					board.cover_comp(total);
					boardDisplay.viewHumanBoard(board, player, round);
					boardDisplay.viewCompBoard(board, player, round);

					if (round.isFirstTurn() == false) {
						if (round.checkIfWon(board)) {
							cout << "Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << " Play again? Hit y for Yes, n for No" << endl;
							cin >> play_again;
							round.setWinnerScore(round.roundEndCompScore(board));
							player.setCompScore(round.roundEndCompScore(board) + player.getCompScore());
							boardDisplay.viewHumanBoard(board, player, round);
							boardDisplay.viewCompBoard(board, player, round);
							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
					else if (round.isFirstTurn() == true) {
						if (board.isCovered_computer()) {
							cout << "Computer won by covering all its squares. Current score is: "
								"Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << " Play again? Hit y for Yes, n for No" << endl;
							cin >> play_again;
							while (play_again != "y" && play_again != "n") {
								cin.clear();
								cin.ignore();
								cout << " Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								if (play_again == "y" || play_again == "n") {
									break;
								}
							}

							round.setWinnerScore(round.roundEndCompScore(board));
							player.setCompScore(round.roundEndCompScore(board) + player.getCompScore());
							boardDisplay.viewHumanBoard(board, player, round);
							boardDisplay.viewCompBoard(board, player, round);
							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
				}
				else if (isunCoverable && isCoverable == false) {
					board.uncover_human(total);
					boardDisplay.viewHumanBoard(board, player, round);
					boardDisplay.viewCompBoard(board, player, round);
					if (round.isFirstTurn() == false) {
						if (round.checkIfWon(board)) {
							cout << "Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << " Play again? Hit y for Yes, n for No" << endl;
							cin >> play_again;
							while (play_again != "y" && play_again != "n") {
								cin.clear();
								cin.ignore();
								cout << " Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								if (play_again == "y" || play_again == "n") {
									break;
								}
							}
							round.setWinnerScore(round.roundEndCompScore(board));
							player.setCompScore(round.roundEndCompScore(board) + player.getCompScore());
							boardDisplay.viewHumanBoard(board, player, round);
							boardDisplay.viewCompBoard(board, player, round);
							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
				}
				else if (isCoverable || isunCoverable) {
					bool covOrunCov = computer.toCoverOrUncover(board, round, "no");
					if (covOrunCov) {
						board.cover_comp(total);
					}
					else {
						if (round.isFirstTurn() == false) {
							board.uncover_human(total);
						}
					}
					boardDisplay.viewHumanBoard(board, player, round);
					boardDisplay.viewCompBoard(board, player, round);

					if (round.isFirstTurn() == false) {
						if (round.checkIfWon(board)) {
							cout << "Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << " Play again? Hit y for Yes, n for No" << endl;
							cin >> play_again;
							while (play_again != "y" && play_again != "n") {
								cin.clear();
								cin.ignore();
								cout << "Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								if (play_again == "y" || play_again == "n") {
									break;
								}
							}
							round.setWinnerScore(round.roundEndCompScore(board));
							player.setCompScore(round.roundEndCompScore(board) + player.getCompScore());
							boardDisplay.viewHumanBoard(board, player, round);
							boardDisplay.viewCompBoard(board, player, round);
							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
					else if (round.isFirstTurn() == true) {
						if (board.isCovered_computer()) {
							cout << "Computer won by covering all its squares. Current score is: "
								"Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << " Play again? Hit y for Yes, n for No" << endl;

							cin >> play_again;
							while (play_again != "y" && play_again != "n") {
								cin.clear();
								cin.ignore();
								cout << " Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								if (play_again == "y" || play_again == "n") {
									break;
								}
							}
							round.setWinnerScore(round.roundEndCompScore(board));
							player.setCompScore(round.roundEndCompScore(board) + player.getCompScore());
							boardDisplay.viewHumanBoard(board, player, round);
							boardDisplay.viewCompBoard(board, player, round);
							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);

							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
				}
				else {
					movesAvailable = 0;
					cout << "No more moves available.Changing the players now. " << endl;
					if (round.isFirstTurn() == false) {
						if (round.checkIfWon(board)) {
							cout << "Computer: " << round.roundEndCompScore(board) << " Human : " << round.roundEndHumanScore(board) << " Play again ? Hit y for Yes, n for No" << endl;
							cin >> play_again;
							while (play_again != "y" && play_again != "n") {
								cin.clear();
								cin.ignore();
								cout << " Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								if (play_again == "y" || play_again == "n") {
									break;
								}
							}
							round.setWinnerScore(round.roundEndCompScore(board));
							player.setHumanScore(round.roundEndCompScore(board) + player.getCompScore());
							boardDisplay.viewHumanBoard(board, player, round);
							boardDisplay.viewCompBoard(board, player, round);

							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
					round.sethumanFirstTurn(false);
					round.setFirstTurn(false);
					round.setCurrentPlayer("Human");
					round.setNextPlayer("Computer");
				}
			}
			else {
				bool isSingleCoverable = false;
				bool isSingleunCoverable = false;
				vector<int>singleCover;
				vector<int>singleUncover;
				vector<int>hasFour_coverables;
				vector<int>hasFour_uncoverables;

				if (total <= board.getBoardSize()) {
					if (board.getCompSquares()[total - 1] == 1) {
						isSingleCoverable = false;
					}
					else {
						isSingleCoverable = true;
						singleCover.push_back(total);
					}
					if (board.getHumanSquares()[total - 1] == 0) {
						isSingleunCoverable = false;
					}
					else {
						isSingleunCoverable = true;
						if (round.ishumanFirstTurn() == false) {
							isSingleunCoverable = true;
							singleUncover.push_back({ total });
						}
					}
				}
				if (total == 10 || total == 11 || total == 12) {
					vector<int>numbers = player.findFours(total);
					bool containsCov = includes(coverables.begin(), coverables.end(), numbers.begin(), numbers.end());
					if (containsCov) {
						hasFour_coverables = numbers;
					}
					bool containsUnCov = includes(uncoverables.begin(), uncoverables.end(), numbers.begin(), numbers.end());
					if (containsUnCov) {
						hasFour_uncoverables = numbers;
					}
				}
				vector<vector<int>>hasPairs_coverables = player.findPairs(coverables, total);
				vector<vector<int>>hasThree_coverables = player.threeSum(coverables, total);
				vector<vector<int>>hasPairs_uncoverables = player.findPairs(uncoverables, total);
				vector<vector<int>>hasThree_uncoverables = player.threeSum(uncoverables, total);

				if (hasPairs_coverables.size() > 0 || hasThree_coverables.size() > 0 || isSingleCoverable || hasFour_coverables.size() > 0) {
					isCoverable = 1;
					coverable_options = player.getAllOptions(singleCover, hasPairs_coverables, hasThree_coverables, hasFour_coverables);
				}

				else {
					isCoverable = 0;
				}
				if (hasPairs_uncoverables.size() > 0 || hasThree_uncoverables.size() > 0 || isSingleunCoverable || hasFour_uncoverables.size() > 0) {
					isunCoverable = 1;
					uncoverable_options = player.getAllOptions(singleUncover, hasPairs_uncoverables, hasThree_uncoverables, hasFour_uncoverables);
				}
				else {
					isunCoverable = 0;
				}

				if (isCoverable || isunCoverable) {
					movesAvailable = 1;
					bool covOrunCov = false;
					//bool covOrunCov = computer.toCoverOrUncover(board, round, "no");
					if (coverable_options.size() > 0 && uncoverable_options.size() <= 0) {
						// if only cover options is available, cover
						covOrunCov = true;
					}
					else if (uncoverable_options.size() > 0 && coverable_options.size() <= 0) {
						// if only uncover options is avaibale, uncover
						covOrunCov = false;
					}
					else {
						covOrunCov = computer.toCoverOrUncover(board, round, "yes");
					}
					move = computer.getBestMove(coverable_options, uncoverable_options, board, round, boardDisplay, "no");

					for (int i = 0; i < move.size(); i++) {
						if (covOrunCov) {
							board.cover_comp(move[i]);
						}
						else {
							board.uncover_human(move[i]);

						}
					}
					boardDisplay.viewHumanBoard(board, player, round);
					boardDisplay.viewCompBoard(board, player, round);
					if (round.isFirstTurn() == false) {
						if (round.checkIfWon(board)) {
							cout << "Current score is : "
								"Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << endl;
							round.setWinnerScore(round.roundEndCompScore(board));
							player.setCompScore(round.roundEndCompScore(board) + player.getCompScore());
							boardDisplay.viewHumanBoard(board, player, round);
							boardDisplay.viewCompBoard(board, player, round);
							cout << "Play again? Hit y for Yes or n for No" << endl;
							cin >> play_again;
							while (play_again != "y" && play_again != "n") {
								cin.clear();
								cin.ignore();
								cout << " Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								if (play_again == "y" || play_again == "n") {
									break;
								}
							}
							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
					else if (round.isFirstTurn() == true) {
						if (board.isCovered_computer()) {
							cout << "Current score is : "
								"Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << endl;
							cout << "Play again? Hit y for Yes or n for No" << endl;
							cin >> play_again;
							round.setWinnerScore(round.roundEndCompScore(board));
							player.setCompScore(round.roundEndCompScore(board) + player.getCompScore());
							boardDisplay.viewHumanBoard(board, player, round);
							boardDisplay.viewCompBoard(board, player, round);
							while (play_again != "y" && play_again != "n") {
								cin.clear();
								cin.ignore();
								cout << " Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								if (play_again == "y" || play_again == "n") {
									break;
								}
							}
							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
					system("pause");
				}
				else {
					movesAvailable = 0;
					if (round.isFirstTurn() == false) {
						if (round.checkIfWon(board)) {
							cout << "Current score is : "
								"Computer: " << round.roundEndCompScore(board) << " Human: " << round.roundEndHumanScore(board) << endl;
							cout << "Play again? Hit y for Yes or n for No" << endl;
							cin >> play_again;
							while (play_again != "y" && play_again != "n") {
								cin.clear();
								cin.ignore();
								cout << " Play again? Hit y for Yes, n for No" << endl;
								cin >> play_again;

								if (play_again == "y" || play_again == "n") {
									break;
								}
							}
							round.setWinnerScore(round.roundEndCompScore(board));
							player.setCompScore(round.roundEndCompScore(board) + player.getCompScore());
							if (play_again == "y") {
								startNewRound(round.getFirstPlayer(), "Computer", round.getWinnerScore(), player.getHumanScore(), player.getCompScore(), round.getdiceRolls(), round.getRoundNumber() + 1);
							}
							else {
								round.announceWinner(player);
								system("pause");
								exit(0);
							}
						}
					}
					round.setFirstTurn(false);
					round.setcomputerFirstTurn(false);
					cout << "No more moves available. Changing the players now! " << endl;
					round.setCurrentPlayer("Human");
					round.setNextPlayer("Computer");
				}
			}
		}
	}
	startGame(board, round, player, computer, human, boardDisplay, resume);
}
/*
Function Name: startNewGame()
Purpose: To begin a new game, roll dice to see who gets to play the first turn
Parameters: None
Return Value: None
Algorithm:
	1. Choose the number of squares between 9 and 11
	2. Human rolls and then computer rolls
	3. The player that rolls  the highest wins, if equal, they roll again.
	4. The player that rolls the highest plays the first turn.
*/

void Game::startNewGame() {
	string numOfSquares = "";

	while (numOfSquares != "9" && numOfSquares != "10" && numOfSquares != "11") {
		try {
			cout << "Type the number of squares between 9 and 11: " << endl;
			cin >> numOfSquares;
		}
		catch (const char* msg) {
			cout << msg << endl;
		}
	}

	Board board(stoi(numOfSquares));
	BoardView boardDisplay;
	Round round;
	Computer computer;
	Human human;
	Player player;


	boardDisplay.viewHumanBoard(board, player, round);
	boardDisplay.viewCompBoard(board, player, round);
	string roll_dice = "";
	int humanScore = 0;
	int compScore = 0;
	int die1 = 0;
	int die2 = 0;
	bool resume = false;
	cout << "The first turn will be decided by the initial roll. " << endl;

	do {
		while (roll_dice != "r") {
			cout << "Enter r to roll: " << endl;
			cin >> roll_dice;
			if (roll_dice == "r") {
				die1 = roll();
				die2 = roll();
			}
		}
		humanScore = die1 + die2;
		cout << "The human rolled " << die1 << " and " << die2 << endl;
		cout << "The computer is rolling..... " << endl;
		system("pause");
		die1 = roll();
		die2 = roll();
		compScore = die1 + die2;

		cout << "The computer rolled " << die1 << " and " << die2 << endl;

		cout << "The human scored " << humanScore << endl;
		cout << "The computer scored " << compScore << endl;

		if (compScore == humanScore) {
			cout << "It's a tie. Lets roll again!!" << endl;

		}
		else if (compScore > humanScore) {
			cout << "Computer scored higher and will start the game. " << endl;
			round.setFirstPlayer("Computer");
			round.setCurrentPlayer("Computer");
			round.setNextPlayer("Human");
		}
		else {
			cout << "Human scored higher and will start the game. " << endl;
			round.setFirstPlayer("Human");
			round.setCurrentPlayer("Human");
			round.setNextPlayer("Computer");
		}

	} while (compScore == humanScore);

	round.setFirstTurn(true);
	if (round.getCurrentPlayer() == "Human") {
		startGame(board, round, player, computer, human, boardDisplay, resume);
	}
	else if (round.getCurrentPlayer() == "Computer") {
		compPlaysNow(board, round, player, computer, human, boardDisplay, resume);
	}
}

/*
Function Name: getSquaresFromFile()
Purpose: Extract squares from files for a specific player
Parameters: filename -> name of the file, player -> player name
Return Value: None
Algorithm:
	1. Parse the lines from the file and extract the squares for each player
*/

vector<int> Game::getSquaresFromFile(string filename, string player) {

	vector<string> lines;
	ifstream input_file(filename);
	string line;

	if (!input_file.is_open()) {
		cerr << "Could not open the file - '"
			<< filename << "'" << endl;
		exit(0);
	}

	while (getline(input_file, line)) {
		lines.push_back(line);
	}

	char ch = ':';
	size_t pos_comp = lines[1].find(ch);
	size_t pos_hum = lines[5].find(ch);

	string computerSquares = " ";
	string humSquares = " ";
	vector<int>compSquares;
	vector<int>humanSquares;

	if (pos_comp != std::string::npos) {
		computerSquares = lines[1].substr(pos_comp + 1);
	}

	for (int i = 0; i < computerSquares.length(); i++) {
		if (computerSquares[i] == '*') {
			compSquares.push_back(1);
		}
		else if (isdigit(computerSquares[i]) && computerSquares[i] != '0') {
			compSquares.push_back(0);
		}

	}

	if (pos_hum != std::string::npos) {
		humSquares = lines[5].substr(pos_hum + 1);
	}

	for (int i = 0; i < humSquares.length(); i++) {

		if (humSquares[i] == '*') {
			humanSquares.push_back(1);
		}
		else if (isdigit(humSquares[i]) && humSquares[i] != '0') {
			humanSquares.push_back(0);
		}
	}
	input_file.close();
	if (player == "computer") {
		return compSquares;
	}
	else {
		return humanSquares;
	}
}
/*
Function Name: getScoresFromFile()
Purpose: Extract scores from files for a specific player
Parameters: filename -> name of the file, player -> player name
Return Value: None
Algorithm:
	1. Parse the lines from the file and extract the scores for each player
*/

int Game::getScoresFromFile(string filename, string player) {

	vector<string> lines;
	string line;

	ifstream input_file(filename);
	if (!input_file.is_open()) {
		cerr << "Could not open the file - '"
			<< filename << "'" << endl;
		return 1;
	}

	while (getline(input_file, line)) {
		lines.push_back(line);
	}

	char ch = ':';
	size_t pos_comp = lines[2].find(ch);
	size_t pos_hum = lines[6].find(ch);

	string computerScore = " ";
	string humanScore = " ";

	if (pos_comp != std::string::npos)
	{
		computerScore = lines[2].substr(pos_comp + 1);

	}

	if (pos_hum != std::string::npos)
	{
		humanScore = lines[6].substr(pos_hum + 1);
	}


	input_file.close();
	if (player == "computer") {
		return stoi(computerScore);
	}
	else {
		return stoi(humanScore);
	}
	return 0;
}

/*
Function Name: getTurnsFromFile()
Purpose: Extract turns from files for a specific player
Parameters: filename -> name of the file, turn -> first turn or current turn
Return Value: None
Algorithm:
	1. Parse the lines from the file and extract the first turn and the current turn
*/


string Game::getTurnsFromFile(string filename, string turn) {

	vector<string> lines;
	string line;

	ifstream input_file(filename);
	if (!input_file.is_open()) {
		cerr << "Could not open the file - '"
			<< filename << "'" << endl;
		exit(0);
	}

	while (getline(input_file, line)) {
		lines.push_back(line);
	}

	char ch = ':';
	size_t pos_first = lines[8].find(ch);
	size_t pos_current = lines[9].find(ch);

	string firstTurn = " ";
	string currentTurn = " ";

	if (pos_first != std::string::npos)
	{
		firstTurn = lines[8].substr(pos_first + 2);
	}

	if (pos_current != std::string::npos)
	{
		currentTurn = lines[9].substr(pos_current + 2);
	}

	input_file.close();

	if (turn == "first") {
		return firstTurn;
	}
	else {
		return currentTurn;
	}
}
/*
Function Name: getDiceRolls()
Purpose: Extract dice rolls from files
Parameters: filename -> name of the file
Return Value: None
Algorithm:
	1. Parse the lines from the file and extract the dice rolls
*/


stack<string> Game::getDiceRolls(string filename) {
	vector<string> lines;
	string line;
	stack<string> stack;


	ifstream input_file(filename);
	if (!input_file.is_open()) {
		cerr << "Could not open the file - '"
			<< filename << "'" << endl;
		exit(0);
	}

	while (getline(input_file, line)) {
		lines.push_back(line);
	}

	for (int i = lines.size() - 1; i > 11; i--) {
		stack.push(lines[i]);
	}

	return stack;
}
/*
Function Name: getRolls()
Purpose: Extract the top most roll information from the list of dice rolls
Parameters: Round object
Return Value: Return the roll information
Algorithm:
	1. Set the top most roll information and return it
*/

vector<int>Game::getRolls(Round round) {

	string getTopRolls = round.getTopRolls();
	stack<string>diceRolls = round.getdiceRolls();
	string die1;
	string die2;
	int die_1;
	int die_2;

	vector<string>dice = {};
	vector<int>dice_final = {};

	for (int i = 0; i < getTopRolls.length(); i++) {
		if (isdigit(getTopRolls[i])) {
			die1 = getTopRolls[i];
			dice.push_back(die1);
		}
	}

	die_1 = stoi(dice[0]);
	die_2 = stoi(dice[1]);
	dice_final.push_back(die_1);
	dice_final.push_back(die_2);

	return dice_final;
}
/*
Function Name: resumeGame()
Purpose: To resume a saved game
Parameters: None
Return Value: None
Algorithm:
	1. Ask the user to select the file name.
	2. Based on the information on the file, initialize the objects and resume game
*/

void Game::resumeGame() {

	string fileNum = "";
	Round round;
	BoardView boardDisplay;
	Computer computer;
	Human human;
	Player player;
	string fileName;
	bool resume = true;
	bool validFileName = false;
	vector<string>savedFiles = {};


	/* Getting the filenames*/

	fstream files;
	files.open("fileNames.txt", ios::in); //open a file to perform read operation using file object
	if (files.is_open()) {   //checking whether the file is open
		string file;
		while (getline(files, file)) { //read data from file object and put it into string.
			savedFiles.push_back(file); //print the data of the string
		}
		files.close(); //close the file object.
	}

	while (validFileName == false) {
		cout << "Choose your option: " << endl;
		cout << "Type: " << endl;
		for (int i = 0; i < savedFiles.size(); i++) {
			cout << i + 1 << " to open " << savedFiles[i] << endl;
		}

		cin >> fileNum;
		bool isNum = true;

		for (char const& c : fileNum) {
			if (isdigit(c) == 0) {
				isNum = false;
			}
		}

		if (isNum) {

			if (stoi(fileNum) <= savedFiles.size()) {
				fileName = savedFiles[stoi(fileNum) - 1];
				validFileName = true;
			}
			else {
				validFileName = false;
			}
		}
	}
	vector<int>humanSquares = getSquaresFromFile(fileName, "human");
	vector<int>computerSquares = getSquaresFromFile(fileName, "computer");

	round.setCurrentPlayer(getTurnsFromFile(fileName, "current"));
	player.setCompScore(getScoresFromFile(fileName, "computer"));
	player.setHumanScore(getScoresFromFile(fileName, "human"));
	Board board(computerSquares, humanSquares, humanSquares.size());
	round.setDiceRolls(getDiceRolls(fileName));

	boardDisplay.viewHumanBoard(board, player, round);
	boardDisplay.viewCompBoard(board, player, round);

	round.setFirstTurn(false);
	round.setcomputerFirstTurn(false);
	round.sethumanFirstTurn(false);
	round.setFirstPlayer(getTurnsFromFile(fileName, "first"));

	cout << "First Player is: " << round.getFirstPlayer() << endl;
	cout << "Current Player is: " << round.getCurrentPlayer() << endl;

	if (round.getCurrentPlayer() == "Computer") {
		compPlaysNow(board, round, player, computer, human, boardDisplay, resume);
	}
	else if (round.getCurrentPlayer() == "Human") {
		startGame(board, round, player, computer, human, boardDisplay, resume);
	}
}

/*
Function Name: startNewRound()
Purpose: If the user wants to play again, after a succesful round, roll dice to see who gets to play the first turn
Parameters: None
Return Value: None
Algorithm:
	1. Choose the number of squares between 9 and 11
	2. Human rolls and then computer rolls
	3. The player that rolls  the highest wins, if equal, they roll again.
	4. The player that rolls the highest plays the first turn.
*/

void Game::startNewRound(string firstTurn, string winner, int winningScore, int humanScore, int compScore, stack<string>diceRolls, int roundNum) {
	string numOfSquares = "";

	while (numOfSquares != "9" && numOfSquares != "10" && numOfSquares != "11") {
		cout << "Type the number of squares between 9 and 11: " << endl;
		cin >> numOfSquares;
	}

	Board board(stoi(numOfSquares));
	BoardView boardDisplay;
	Round round;
	round.setRoundNumber(roundNum);
	round.setDiceRolls(diceRolls);
	Computer computer;
	Human human;
	Player player;

	int temp = winningScore;
	int newNum = stoi(numOfSquares) + 1;

	while (newNum > 9) {
		newNum = 0;
		while (temp != 0) {
			newNum += temp % 10;
			temp = temp / 10;
		}
		temp = newNum;
	}

	winningScore = newNum;
	round.setWinnerScore(winningScore);
	cout << "The first turn was taken by: " << firstTurn << endl;
	cout << "The winner was : " << winner << endl;

	if (firstTurn == "Human" && winner == "Human") {
		cout << "Computer has an advantage. " << endl;
		board.cover_comp(winningScore);
	}
	else if (firstTurn == "Human" && winner == "Computer") {
		cout << "Computer has an advantage. " << endl;
		board.cover_comp(winningScore);
	}
	else if (firstTurn == "Computer" && winner == "Computer") {
		cout << "Human has an advantage. " << endl;
		board.cover_human(winningScore);
	}
	else if (firstTurn == "Computer" && winner == "Human") {
		cout << "Human has an advantage. " << endl;
		board.cover_human(winningScore);
	}

	player.setCompScore(compScore);
	player.setHumanScore(humanScore);
	round.setHandicapped(true);
	boardDisplay.viewHumanBoard(board, player, round);
	boardDisplay.viewCompBoard(board, player, round);
	round.setFirstTurn(true);

	string roll_dice = "";
	int die1 = 0;
	int die2 = 0;
	bool resume = false;
	int total = 0;
	vector<int>rolls;
	compScore = 0;
	humanScore = 0;
	cout << "The first turn will be decided by the initial roll. " << endl;

	do {
		int diceTotals = round.getdiceRolls().size();
		total = 0;
		roll_dice = "a";
		while (total == 0 && roll_dice != "r") {
			cout << "Enter r to roll: " << endl;
			cin >> roll_dice;
			if (diceTotals > 0) {
				rolls = getRolls(round);
				die1 = rolls[0];
				die2 = rolls[1];
				total = die1 + die2;
				round.getdiceRolls().pop();
				//cout << "New dicerolls size is: " << round.getdiceRolls().size() << endl;
			}
			else {
				die1 = human.roll_dice();
				die2 = human.roll_dice();
				total = die1 + die2;
			}
		}
		humanScore = die1 + die2;
		cout << "The human rolled " << die1 << " and " << die2 << endl;

		cout << "The computer is rolling..... " << endl;
		system("pause");
		if (diceTotals > 0) {
			rolls = getRolls(round);
			die1 = rolls[0];
			die2 = rolls[1];
			total = die1 + die2;
			round.getdiceRolls().pop();
			//cout << "New dicerolls size is: " << round.getdiceRolls().size() << endl;
		}
		else {
			die1 = human.roll_dice();
			die2 = human.roll_dice();
			total = die1 + die2;
		}
		compScore = die1 + die2;

		cout << "The computer rolled " << die1 << " and " << die2 << endl;

		cout << "The human scored " << humanScore << endl;
		cout << "The computer scored " << compScore << endl;

		if (compScore == humanScore) {
			cout << "It's a tie. Lets roll again!!" << endl;

		}
		else if (compScore > humanScore) {
			cout << "Computer scored higher and will start the game. " << endl;
			round.setFirstPlayer("Computer");
			round.setcomputerFirstTurn(true);
			round.setCurrentPlayer("Computer");
			round.setNextPlayer("Human");
		}
		else {
			cout << "Human scored higher and will start the game. " << endl;
			round.setFirstPlayer("Human");
			round.sethumanFirstTurn(true);
			round.setCurrentPlayer("Human");
			round.setNextPlayer("Computer");
		}

	} while (compScore == humanScore);

	round.setFirstTurn(true);
	if (round.getCurrentPlayer() == "Human") {
		startGame(board, round, player, computer, human, boardDisplay, resume);
	}
	else if (round.getCurrentPlayer() == "Computer") {
		compPlaysNow(board, round, player, computer, human, boardDisplay, resume);
	}
}

/*
Function Name: saveGame()
Purpose: Save the state of the game in a text file
Parameters: Board object, Round object, Player object
Return Value: None
Algorithm:
	1. Save the squares for each player
	2. Save the scores for each player
	3. Save the first player and the current player name.
*/

void Game::saveGame(Board board, Round round, Player player) {

	string filename;
	cout << "Enter the filename " << endl;
	cin >> filename;

	fstream newFile;
	newFile.open("fileNames.txt", ios_base::app | ios_base::in);
	if (newFile.is_open())
	{
		newFile << "\n" << filename << ".txt";
		newFile.close();
	}

	ofstream fout(filename + ".txt");
	if (!fout) {
		cout << "Could not open file. " << endl;
		exit(0);
	}
	fout << "Computer: " << endl;
	fout << "   Squares: ";
	for (int i = 0; i < board.getBoardSize(); i++) {
		if (board.getCompSquares()[i] == 0) {
			fout << "*" << " ";
		}
		else {
			fout << i + 1 << " ";

		}
	}
	fout << endl;

	fout << "   Score: " << player.getCompScore() << endl << endl;

	fout << "Human: " << endl;
	fout << "   Squares: ";
	for (int i = 0; i < board.getBoardSize(); i++) {
		if (board.getHumanSquares()[i] == 0) {
			fout << "*" << " ";
		}
		else {
			fout << i + 1 << " ";

		}
	}
	fout << endl;

	fout << "   Score: " << player.getHumanScore() << endl;

	fout << endl;


	fout << "First Turn: " << round.getFirstPlayer() << " " << endl;
	fout << "Next Turn: " << round.getCurrentPlayer() << endl;
	system("pause");
	exit(0);
}
