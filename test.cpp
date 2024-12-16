#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include "BoardGame_Classes.h"

using namespace std;

// Numerical Tic Tac Toe Board Class
class Numerical_Tic_Tac_Toe_Board : public Board<int> {
private:
    set<int> valid_numbers_player1;
    set<int> valid_numbers_player2;
    map<string, set<pair<int, int>>> player_moves;

public:
    Numerical_Tic_Tac_Toe_Board() {
        rows = 3;
        columns = 3;
        board = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new int[columns];
            fill(board[i], board[i] + columns, 0);
        }
        n_moves = 0;

        // Initialize valid numbers for Player 1 and Player 2
        for (int i = 1; i <= 9; i += 2) valid_numbers_player1.insert(i); // Odd numbers for Player 1
        for (int i = 2; i <= 8; i += 2) valid_numbers_player2.insert(i); // Even numbers for Player 2/Computer
    }

    ~Numerical_Tic_Tac_Toe_Board() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    set<int> getValidNumbersForPlayer1() const {
        return valid_numbers_player1;
    }

    set<int> getValidNumbersForPlayer2() const {
        return valid_numbers_player2;
    }

    void display_board() override {
        cout << "   |  1   2   3  " << endl;
        cout << "---+-------------" << endl;

        for (int i = 0; i < rows; ++i) {
            cout << " " << i + 1 << " | ";
            for (int j = 0; j < columns; ++j) {
                cout << (board[i][j] == 0 ? " " : to_string(board[i][j])) << " ";
                if (j < columns - 1) cout << "| ";
            }
            cout << endl;
            if (i < rows - 1) cout << "   |---+---+---" << endl;
        }
        cout << endl;
    }

    bool update_board(int x, int y, int number) override {
        x -= 1;
        y -= 1;
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == 0) {
            board[x][y] = number;
            n_moves++;
            return true;
        }
        return false;
    }

    bool update_board(int x, int y, int number, const string& player_name) {
        if (update_board(x, y, number)) {
            player_moves[player_name].insert({x, y});
            return true;
        }
        return false;
    }

    bool is_sum_15(const vector<pair<int, int>>& positions) {
        int sum = 0;
        for (auto& pos : positions) {
            sum += board[pos.first][pos.second];
        }
        return sum == 15;
    }

    bool check_line(const vector<pair<int, int>>& positions, const string& player_name) {
        for (auto& pos : positions) {
            if (board[pos.first][pos.second] == 0) {
                return false;
            }
        }
        return is_sum_15(positions);
    }

    bool is_win(const string& player_name) {
        vector<vector<pair<int, int>>> lines = {
            {{0, 0}, {0, 1}, {0, 2}}, 
            {{1, 0}, {1, 1}, {1, 2}}, 
            {{2, 0}, {2, 1}, {2, 2}}, 
            {{0, 0}, {1, 0}, {2, 0}}, 
            {{0, 1}, {1, 1}, {2, 1}}, 
            {{0, 2}, {1, 2}, {2, 2}}, 
            {{0, 0}, {1, 1}, {2, 2}}, 
            {{0, 2}, {1, 1}, {2, 0}}
        };

        for (auto& line : lines) {
            if (check_line(line, player_name)) return true;
        }
        return false;
    }

    bool is_win() override {
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over(const string& player_name) {
        return is_win(player_name) || is_draw();
    }

    bool game_is_over() override {
        return false;
    }
};

// Numerical Player Class
class Numerical_Player : public Player<int> {
private:
    int number;
    set<int> used_numbers;
    set<int> valid_numbers;

public:
    Numerical_Player(string n, set<int> valid_nums) : Player<int>(n, 0), number(0), valid_numbers(valid_nums) {}

    void getmove(int& x, int& y) override {
        while (true) {
            cout << this->name << ", enter your move (row column): ";
            cin >> x >> y;
            cout << "Enter number (choose from available numbers): ";
            cin >> number;

            if (valid_numbers.count(number) && used_numbers.count(number) == 0) {
                used_numbers.insert(number);
                break;
            } else {
                cout << "Invalid number or number already used. Please try again." << endl;
            }
        }
    }

    int getSymbol() const {
        return number;
    }
};

// Main Function
int main() {
    Numerical_Tic_Tac_Toe_Board board;
    Player<int>* players[2];


    
        players[0] = new Numerical_Player("Player 1", board.getValidNumbersForPlayer1());
        players[1] = new Numerical_Player("Player 2", board.getValidNumbersForPlayer2());
    

    int current_player = 0;

    while (true) {
        board.display_board();

        int x = 0, y = 0;
        players[current_player]->getmove(x, y);

        int number = dynamic_cast<Numerical_Player*>(players[current_player])->getSymbol();
        string player_name = players[current_player]->getname();

        if (board.update_board(x, y, number, player_name)) {
            if (board.is_win(player_name)) {
                board.display_board();
                cout << player_name << " wins!" << endl;
                break;
            } else if (board.is_draw()) {
                board.display_board();
                cout << "It's a draw!" << endl;
                break;
            }
            current_player = 1 - current_player;
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }

    delete players[0];
    delete players[1];

}