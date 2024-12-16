#ifndef Four_in_a_row
#define Four_in_a_row

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for rand()

using namespace std;

// Four_in_a_row_Board Class
template <typename T>
class Four_in_a_row_Board : public Board<T> {
private:
    vector<vector<T>> board;
    const int rows = 6;
    const int cols = 7;
public:
    Four_in_a_row_Board() {
        board = vector<vector<T>>(rows, vector<T>(cols, ' ')); 
    }

    bool update_board(int col, int, T symbol) {
        if (col < 0 || col >= cols) return false; 
        for (int row = rows - 1; row >= 0; --row) {
            if (board[row][col] == ' ') {
                board[row][col] = symbol;
                return true;
            }
        }
        return false; 
    }

    void display_board() {
        for (const auto& row : board) {
            for (const auto& cell : row) {
                cout << "| " << cell << " ";
            }
            cout << "|\n";
        }
        cout << "-----------------------------\n";
        cout << "  1   2   3   4   5   6   7\n";
    }

    bool is_win() {
        // Check horizontal, vertical, and diagonal conditions
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                T symbol = board[r][c];
                if (symbol == ' ') continue;

                // Horizontal
                if (c + 3 < cols &&
                    board[r][c] == symbol &&
                    board[r][c + 1] == symbol &&
                    board[r][c + 2] == symbol &&
                    board[r][c + 3] == symbol)
                    return true;

                // Vertical
                if (r + 3 < rows &&
                    board[r][c] == symbol &&
                    board[r + 1][c] == symbol &&
                    board[r + 2][c] == symbol &&
                    board[r + 3][c] == symbol)
                    return true;

                // Diagonal (down-right)
                if (r + 3 < rows && c + 3 < cols &&
                    board[r][c] == symbol &&
                    board[r + 1][c + 1] == symbol &&
                    board[r + 2][c + 2] == symbol &&
                    board[r + 3][c + 3] == symbol)
                    return true;

                // Diagonal (up-right)
                if (r - 3 >= 0 && c + 3 < cols &&
                    board[r][c] == symbol &&
                    board[r - 1][c + 1] == symbol &&
                    board[r - 2][c + 2] == symbol &&
                    board[r - 3][c + 3] == symbol)
                    return true;
            }
        }
        return false;
    }

    bool is_draw() {
        for (int c = 0; c < cols; ++c) {
            if (board[0][c] == ' ') return false;
        }
        return true;
    }

    bool game_is_over() {
        return is_win() || is_draw();
    }
};




template <typename T>
class Four_in_a_row_Player : public Player<T> {
public:
    Four_in_a_row_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& col, int&) override { 
        cout << this->getname() << ", enter a column (1-7): "; 
        cin >> col;
        col -= 1; 
    }
};


// Four_in_a_row_Random_Player Class
template <typename T>
class Four_in_a_row_Random_Player : public RandomPlayer<T> {
public:
    Four_in_a_row_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int& col, int&) {
        col = rand() % 7; // Random column
    }
};

#endif
