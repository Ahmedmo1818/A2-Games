#include <iostream>
#include <vector>
using namespace std;

class Player
{
public:
    char mark;
    Player(char m) : mark(m) {}
};

class Board
{
private:
    vector<vector<char>> grid;

public:
    Board()
    {
        grid = vector<vector<char>>(3, vector<char>(3, ' '));
    }

    void printBoard()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                cout << grid[i][j];
                if (j < 2)
                    cout << "|";
            }
            cout << endl;
            if (i < 2)
                cout << "-----\n";
        }
    }

    bool makeMove(int row, int col, char mark)
    {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' ')
        {
            return false;
        }
        grid[row][col] = mark;
        return true;
    }

    bool checkWin()
    {

        for (int i = 0; i < 3; ++i)
        {
            if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
                return true;
            if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
                return true;
        }

        if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
            return true;
        if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
            return true;

        return false;
    }

    bool isFull()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (grid[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }
};

class Game
{
private:
    Board board;
    Player player1, player2;
    Player *currentPlayer;

public:
    Game() : player1('X'), player2('O'), currentPlayer(&player1) {}

    void play()
    {
        int row, col;
        while (true)
        {
            board.printBoard();
            cout << "Player " << currentPlayer->mark << "'s turn (row and column): ";
            cin >> row >> col;

            if (board.makeMove(row, col, currentPlayer->mark))
            {
                if (board.checkWin())
                {
                    board.printBoard();
                    cout << "Player " << currentPlayer->mark << " loses!\n";
                    break;
                }
                if (board.isFull())
                {
                    board.printBoard();
                    cout << "It's a draw!\n";
                    break;
                }

                currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
            }
            else
            {
                cout << "Invalid move. Try again.\n";
            }
        }
    }
};

int main()
{
    Game game;
    game.play();
    return 0;
}