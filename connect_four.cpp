#include "connect_four.h"
#include <iostream>
#include <limits>
using namespace std;

// Function to print the game board
void printBoard(const std::vector<std::vector<char>>& board) {
  cout << "\n|1|2|3|4|5|6|7|";
  cout << "\n---------------\n";
  for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
          char disc = board[i][j];
          if (disc == 'R') {
              cout << "|" << "\x1b[31m" << disc << "\x1b[0m";
          } else if (disc == 'B') {
              cout << "|" << "\x1b[34m" << disc << "\x1b[0m";
          } else {
              cout << "|" << disc;
          }
      }
      cout << "|\n---------------\n" << endl;
  }
}

// For clearing the input buffer
void ignoreInput() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to check if a player has won
bool checkWin(const std::vector<std::vector<char>>& board, char player) {
  // Check horizontally
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) {
                return true;
            }
        }
    }

  // Check vertically
    for (int i = 0; i < ROWS - 3; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player) {
                return true;
            }
        }
    }

  // Check diagonally (ascending)
    for (int i = 3; i < ROWS; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player) {
                return true;
            }
        }
    }

  // Check diagonally (descending)
    for (int i = 3; i < ROWS; ++i) {
        for (int j = 3; j < COLS; ++j) {
            if (board[i][j] == player && board[i - 1][j - 1] == player && board[i - 2][j - 2] == player && board[i - 3][j - 3] == player) {
                return true;
            }
        }
    }

  return false;
}

// Function to get a valid column choice from the player
int getColumnChoice(char currentPlayer) {
  int col;
    while (true) {
        cout << "Player " << currentPlayer << ", Choose a column (1-7): ";
        if (!(cin >> col)) {
            cout << "Invalid input! Please enter a number between 1 and 7." << endl;
            ignoreInput();
        } else {
            col--; // Convert to 0-based index
            if (col >= 0 && col < COLS) {
                return col;
            } else {
                cout << "Invalid column choice! Try again." << endl;
            }
        }
    }
}

// Function to make a move on the board
bool makeMove(std::vector<std::vector<char>>& board, int col, char currentPlayer) {
  for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            return true;
        }
    }
    return false; // Column is full, move not possible
}

// Function to check if the board is full (tie)
bool isBoardFull(const std::vector<std::vector<char>>& board) {
  for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Function to display the welcome message
void DisplayWelcomeMessage() {
  cout << "----------------------------" << endl;
  cout << "| Welcome to Connect Four! |" << endl;
  cout << "----------------------------" << endl;
  
  cout << endl << "RULES:" << endl;
  cout << "1. Two-player (Red(R) & Blue(B)) game.\n" <<
          "2. Board size is 6 rows & 7 columns.\n" <<
          "3. A player wins if he/she is able to connect 4 dots horizontally, vertically or diagonally.\n" <<
          "4. Draw when the matrix is fully filled." << endl;
  
  cout << endl << "HOW TO PLAY:" << endl;
  cout << "1. Game always start with player - 1 i.e. Red(R)\n" <<
          "2. In each step choose the column in which you want to drop the ball.\n" <<
          "3. Rows will be filled from bottom to top in any column.\n" << endl;
  
  cout << "Player 1: (R) Red, Player 2: (B) Blue" << endl;
}

// Function to display the closing message
void DisplayEndingMessaging() {
  cout << endl;
  cout << "------------------------" << endl;
  cout << "|       Game Ends      |" << endl;
  cout << "|       Thank You      |" << endl;
  cout << "|  See you next time!  |" << endl;
  cout << "------------------------" << endl;
  cout << endl;
}

// Function to prompt the user if they want to play again
bool playAgainPrompt() {
    while (true) {
        cout << "Do you want to play again? (y/n): ";
        char choice;
        cin >> choice;

        ignoreInput();
      
        if (choice == 'y' || choice == 'Y') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        } else {
            cout << "Invalid choice. Please enter 'y' or 'n'." << endl;
        }
    }
}

// Function to clear the output screen
void clearScreen() {
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    system("cls"); // For Windows
#else
    system("clear"); // For Unix-based systems (Linux, macOS)
#endif
}

// Function to start and manage the game loop
void playConnectFour() {
  bool playAgain = true;
  while (playAgain) {
    vector<vector<char>> board(ROWS, vector<char>(COLS, ' ')); // Initialize the game board
    char currentPlayer = 'R'; // Player 'R' (red) starts the game
  
    clearScreen(); // Clear the output screen
  
    DisplayWelcomeMessage();
  
    while (true) {
        printBoard(board);
        
        int col = getColumnChoice(currentPlayer);
  
        // Make the move
        if (!makeMove(board, col, currentPlayer)) {
            cout << "Column is full. Try again." << endl;
            continue;
        }
  
        // Check if the current player wins
        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            cout << "------------------------" << endl;
            cout << "| Player " << currentPlayer << " (" << (currentPlayer == 'R' ? "Red" : "Blue") << ") wins! |" << endl;
            cout << "------------------------" << endl;
            DisplayEndingMessaging();
            break;
        }
  
        // Check for a tie
        if (isBoardFull(board)) {
            printBoard(board);
            cout << "---------------" << endl;
            cout << "| It's a tie! |" << endl;
            cout << "---------------" << endl;
            DisplayEndingMessaging();
            break;
        }

      // Switch to the other player
      currentPlayer = (currentPlayer == 'R') ? 'B' : 'R';
    }
    
      // Ask if the players want to play again
      playAgain = playAgainPrompt();

      if (playAgain) {
          clearScreen(); // Clear the output screen before starting a new game
      }
  }
}
