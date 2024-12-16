#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

vector<int> newnum(2, -1);

// tick_tack_to4x4Board Class
template <typename T>
class tick_tack_to4x4Board : public Board<T>
{
private:
    vector<vector<T>> board;

public:
    tick_tack_to4x4Board()
    {
        board = {
            {'O', 'X', 'O', 'X'},
            {'.', '.', '.', '.'},
            {'.', '.', '.', '.'},
            {'X', 'O', 'X', 'O'}};
    }

    bool update_board(int new_x, int new_y, T symbol) override

    {
        new_x = newnum[0];
        new_y = newnum[1];
        // Validate move: within bounds and cell is empty
        if (new_x < 0 || new_x >= 4 || new_y < 0 || new_y >= 4 || board[new_x][new_y] != '.' || board[newnum[2]][newnum[3]] != symbol)
        {
            cout << "invalid input please enter the postion of you symbol and new valid postion" << endl;
            return false;
        }
        board[new_x][new_y] = symbol;
        board[newnum[2]][newnum[3]] = '.';
        newnum.clear();
        return true;
    }

    void display_board() override
    {
        for (const auto &row : board)
        {
            for (const auto &cell : row)
            {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }

    bool is_win() override
    {
        // Check rows
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j <= 1; ++j)
            {
                if (board[i][j] != '.' && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
                    return true;
            }
        }

        // Check columns
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j <= 1; ++j)
            {
                if (board[j][i] != '.' && board[j][i] == board[j + 1][i] && board[j][i] == board[j + 2][i])
                    return true;
            }
        }

        // Check diagonals
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 1; ++j)
            {
                if (board[i][j] != '.' && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2])
                    return true;

                if (board[i][3 - j] != '.' && board[i][3 - j] == board[i + 1][2 - j] && board[i][3 - j] == board[i + 2][1 - j])
                    return true;
            }
        }
        return false;
    }

    bool is_draw() override
    {
        // Check for empty cells
        for (const auto &row : board)
        {
            for (const auto &cell : row)
            {
                if (cell == '.')
                    return false;
            }
        }
        return !is_win();
    }

    bool game_is_over() override
    {
        return is_win() || is_draw();
    }
};

// tick_tack_to4x4Player Class
template <typename T>
class tick_tack_to4x4Player : public Player<T>
{
public:
    tick_tack_to4x4Player(string name, T symbol) : Player<T>(name, symbol) {}
    void getmove(int &x, int &y) override
    {
        cout << this->getname() << ", enter the current row and column of your token (1-4): ";
        cin >> x >> y;

        cout << this->getname() << ", enter the new row and column (1-4): ";
        cin >> newnum[0] >> newnum[1];
        --newnum[0];
        --newnum[1];

        newnum[2] = x - 1;
        newnum[3] = y - 1;
    }
};

// Four_in_a_row_Random_Player Class
template <typename T>
class tick_tack_to4x4_Random_Player : public RandomPlayer<T>
{
public:
    tick_tack_to4x4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int &x, int &y)
    {
        x = rand() % 4;
        y = rand() % 4;
        newnum[0] = rand() % 4;
        newnum[1] = rand() % 4;
        newnum[2] = x;
        newnum[3] = y;
    }
};

int main()
{
    Player<char> *players[2];
    tick_tack_to4x4Board<char> *board = new tick_tack_to4x4Board<char>();
    string name1, name2;
    int choice;
    cout << "Welcome to 4 x 4 Tic-Tac-Toe!\n";
    // Set up Player 1
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;
    if (choice == 1)
    {
        players[0] = new tick_tack_to4x4Player<char>(name1, 'X');
    }
    else if (choice == 2)
    {
        players[0] = new tick_tack_to4x4_Random_Player<char>('X');
    }

    // Set up Player 2
    cout << "Enter Player 2 name: ";
    cin >> name2;
    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;
    if (choice == 1)
    {
        players[1] = new tick_tack_to4x4Player<char>(name2, 'O');
    }
    else if (choice == 2)
    {
        players[1] = new tick_tack_to4x4_Random_Player<char>('O');
    }

    // Run the game
    GameManager<char> game(board, players);
    game.run();

    // Clean up
    delete board;
    delete players[0];
    delete players[1];

    return 0;
}
