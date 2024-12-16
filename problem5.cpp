#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For rand()
#include <algorithm>

using namespace std;

vector<int> Validnumbers_player = {1, 2, 3, 4, 5, 6, 7, 8, 9};
vector<int> numbers_player;

// Numerical_Tic_Tac_Toe_Board Class
class Numerical_Tic_Tac_Toe_Board
{
private:
    vector<vector<int>> board;
    const int rows = 3;
    const int cols = 3;

public:
    Numerical_Tic_Tac_Toe_Board()
    {
        board = vector<vector<int>>(rows, vector<int>(cols, 0)); // Initialize board with 0
    }

    bool update_board(int col, int row, int number, char symbol)
    {
        // Validate position
        if (col < 0 || col >= cols || row < 0 || row >= rows || board[row][col] != 0)
            return false;

        // Validate number
        auto it = find(Validnumbers_player.begin(), Validnumbers_player.end(), number);
        if (it == Validnumbers_player.end())
            return false;

        // Ensure odd/even matching
        if ((symbol == 'X' && number % 2 == 0) || (symbol == 'O' && number % 2 != 0))
            return false;

        // Place the number on the board
        board[row][col] = number;
        Validnumbers_player.erase(it); // Remove number from valid list
        return true;
    }

    void display_board()
    {
        cout << "   |  1   2   3  " << endl;
        cout << "---+-------------" << endl;
        for (int i = 0; i < rows; ++i)
        {
            cout << " " << i + 1 << " | ";
            for (int j = 0; j < cols; ++j)
            {
                if (board[i][j] == 0)
                    cout << "   ";
                else
                    cout << " " << board[i][j] << " ";
                if (j < cols - 1)
                    cout << "|";
            }
            cout << endl;
            if (i < rows - 1)
                cout << "   |---+---+---" << endl;
        }
        cout << endl;
    }

    bool is_win()
    {
        // Check rows, columns, and diagonals for sum = 15
        for (int i = 0; i < rows; ++i)
        {
            if (board[i][0] + board[i][1] + board[i][2] == 15)
                return true;
        }
        for (int j = 0; j < cols; ++j)
        {
            if (board[0][j] + board[1][j] + board[2][j] == 15)
                return true;
        }
        if (board[0][0] + board[1][1] + board[2][2] == 15 || board[0][2] + board[1][1] + board[2][0] == 15)
            return true;
        return false;
    }

    bool is_draw()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (board[i][j] == 0)
                    return false;
            }
        }
        return true;
    }

    bool game_is_over()
    {
        return is_win() || is_draw();
    }
};

// Four_in_a_row_Player Class
class Four_in_a_row_Player
{
private:
    string name;
    char symbol;

public:
    Four_in_a_row_Player(string name, char symbol) : name(name), symbol(symbol) {}

    string get_name() { return name; }
    char get_symbol() { return symbol; }

    void get_move(int &col, int &row, int &number)
    {
        cout << name << " (" << symbol << "), enter your move (row column number): ";
        cin >> row >> col >> number;
        col -= 1; // Adjust to 0-based index
        row -= 1; // Adjust to 0-based index
    }
};

int main()
{
    Numerical_Tic_Tac_Toe_Board board;
    Four_in_a_row_Player player1("Player 1", 'X');
    Four_in_a_row_Player player2("Player 2", 'O');

    Four_in_a_row_Player *players[2] = {&player1, &player2};
    int current_player = 0;

    cout << "Welcome to Numerical Tic-Tac-Toe!\n";
    board.display_board();

    while (!board.game_is_over())
    {
        int col, row, number;
        players[current_player]->get_move(col, row, number);

        if (board.update_board(col, row, number, players[current_player]->get_symbol()))
        {
            board.display_board();
            if (board.is_win())
            {
                cout << players[current_player]->get_name() << " wins!\n";
                break;
            }
            current_player = 1 - current_player; // Switch player
        }
        else
        {
            cout << "Invalid move. Try again.\n";
        }
    }

    if (board.is_draw() && !board.is_win())
    {
        cout << "It's a draw!\n";
    }

    return 0;
}
