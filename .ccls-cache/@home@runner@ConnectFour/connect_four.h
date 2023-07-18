#ifndef CONNECT_FOUR_H
#define CONNECT_FOUR_H

#include <vector>

const int ROWS = 6;
const int COLS = 7;

void printBoard(const std::vector<std::vector<char>>& board);
bool checkWin(const std::vector<std::vector<char>>& board, char player);
int getColumnChoice(char currentPlayer);
bool makeMove(std::vector<std::vector<char>>& board, int col, char currentPlayer);
bool isBoardFull(const std::vector<std::vector<char>>& board);
void playConnectFour();
void DisplayWelcomeMessage();
void DisplayEndingMessaging();
bool playAgainPrompt();
void clearScreen();
void ignoreInput();

#endif // CONNECT_FOUR_H
