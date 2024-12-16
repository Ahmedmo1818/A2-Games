#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class SmallBoard
{
private:
    char grid[3][3];
    char winner;
    bool isFull;

public:
    SmallBoard() : winner(' '), isFull(false)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                grid[i][j] = ' ';
    }

    bool playMove(int row, int col, char player)
    {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' ' || winner != ' ')
        {
            return false;
        }
        grid[row][col] = player;
        checkWinner(player);
        isFull = isBoardFull();
        return true;
    }

    char getWinner() const { return winner; }

    bool isBoardFull() const
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[i][j] == ' ')
                    return false;
        return true;
    }

    void display() const
    {
        if (winner != ' ')
        {
            cout << "Winner: " << winner << "\n";
            return;
        }
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                cout << grid[i][j] << (j < 2 ? "|" : "");
            }
            cout << "\n";
            if (i < 2)
                cout << "-----\n";
        }
    }

private:
    void checkWinner(char player)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player)
            {
                winner = player;
                return;
            }
            if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player)
            {
                winner = player;
                return;
            }
        }
        if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player)
        {
            winner = player;
            return;
        }
        if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player)
        {
            winner = player;
            return;
        }
    }
};

class MainBoard
{
private:
    SmallBoard boards[3][3];
    char mainGrid[3][3];

public:
    MainBoard()
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                mainGrid[i][j] = ' ';
    }

    bool playMove(int boardRow, int boardCol, int cellRow, int cellCol, char player)
    {
        if (boardRow < 0 || boardRow >= 3 || boardCol < 0 || boardCol >= 3 || mainGrid[boardRow][boardCol] != ' ')
        {
            return false;
        }
        if (!boards[boardRow][boardCol].playMove(cellRow, cellCol, player))
        {
            return false;
        }
        updateMainGrid(boardRow, boardCol);
        return true;
    }

    bool isWinner(char player) const
    {
        for (int i = 0; i < 3; ++i)
        {
            if (mainGrid[i][0] == player && mainGrid[i][1] == player && mainGrid[i][2] == player)
                return true;
            if (mainGrid[0][i] == player && mainGrid[1][i] == player && mainGrid[2][i] == player)
                return true;
        }
        if (mainGrid[0][0] == player && mainGrid[1][1] == player && mainGrid[2][2] == player)
            return true;
        if (mainGrid[0][2] == player && mainGrid[1][1] == player && mainGrid[2][0] == player)
            return true;
        return false;
    }

    bool isDraw() const
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (mainGrid[i][j] == ' ')
                    return false;
        return true;
    }

    void display() const
    {
        cout << "Main Board:\n";
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                cout << (mainGrid[i][j] == ' ' ? '.' : mainGrid[i][j]) << " ";
            }
            cout << "\n";
        }
    }

    void displaySmallBoards() const
    {
        cout << "\nSmall Boards:\n";
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                cout << "Board (" << i << ", " << j << "):\n";
                boards[i][j].display();
                cout << "\n";
            }
        }
    }

private:
    void updateMainGrid(int boardRow, int boardCol)
    {
        char winner = boards[boardRow][boardCol].getWinner();
        if (winner != ' ')
        {
            mainGrid[boardRow][boardCol] = winner;
        }
    }
};

class UltimateTicTacToe
{
private:
    MainBoard mainBoard;
    char currentPlayer;

public:
    UltimateTicTacToe() : currentPlayer('X') {}

    void playGame()
    {
        int boardRow, boardCol, cellRow, cellCol;
        string input;
        while (true)
        {
            mainBoard.display();
            mainBoard.displaySmallBoards();
            cout << "Player " << currentPlayer << "'s turn. Choose board and cell (format: boardRow boardCol cellRow cellCol) or type 'End the game' to quit: ";
            getline(cin, input);
            if (input == "End the game")
            {
                cout << "Main Board:\n";
                mainBoard.display();
                cout << "The game has ended.\n";
                break;
            }

            istringstream iss(input);
            if (!(iss >> boardRow >> boardCol >> cellRow >> cellCol) || boardRow < 0 || boardRow >= 3 || boardCol < 0 || boardCol >= 3 ||
                cellRow < 0 || cellRow >= 3 || cellCol < 0 || cellCol >= 3)
            {
                cout << "Invalid input, please enter values between 0 and 2.\n";
                continue;
            }

            if (mainBoard.playMove(boardRow, boardCol, cellRow, cellCol, currentPlayer))
            {
                if (mainBoard.isWinner(currentPlayer))
                {
                    mainBoard.display();
                    cout << "Player " << currentPlayer << " wins the game!\n";
                    break;
                }
                else if (mainBoard.isDraw())
                {
                    mainBoard.display();
                    cout << "The game is a draw!\n";
                    break;
                }
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
            else
            {
                cout << "Invalid move, try again.\n";
            }
        }
    }
};

int main()
{
    UltimateTicTacToe game;
    game.playGame();
    return 0;
}