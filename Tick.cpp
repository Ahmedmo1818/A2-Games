#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std;
#include <vector>
void BoardGame(const vector<vector<int>> &Board) {
    cout << "   |  1   2   3  " << endl;
    cout << "---+-------------" << endl;

    for (size_t i = 0; i < Board.size(); ++i) {
        cout << " " << i + 1 << " | ";
        for (size_t j = 0; j < Board[i].size(); ++j) {
            cout << (Board[i][j] == 0 ? " " : to_string(Board[i][j])) << " "; 
            if (j < Board[i].size() - 1) cout << "| ";
        }
        cout << std::endl;
        if (i < Board.size() - 1) {
            cout << "   |---+---+---" << endl;
        }
    }
}

bool isWin(const vector<vector<int>> &Board)
{
    if (Board[0][0] + Board[0][1] + Board[0][2] == 15)
    {
        return true;
    }
    if (Board[1][0] + Board[1][1] + Board[1][2] == 15)
    {
        return true;
    }
    if (Board[2][0] + Board[2][1] + Board[2][2] == 15)
    {
        return true;
    }
    if (Board[0][0] + Board[1][0] + Board[2][0] == 15)
    {
        return true;
    }
    if (Board[0][1] + Board[1][1] + Board[2][1] == 15)
    {
        return true;
    }
    if (Board[0][2] + Board[1][2] + Board[2][2] == 15)
    {
        return true;
    }
    if (Board[0][0] + Board[1][1] + Board[2][2] == 15)
    {
        return true;
    }
    if (Board[0][2] + Board[1][1] + Board[2][0] == 15)
    {
        return true;
    }
    return false;
}


void RandomPlayer1(vector<vector<int>> &Board, int &player1row, int &player1column, int &player1number) {
    player1row = rand() % 3;
    player1column = rand() % 3;
    player1number = 0;

    while (Board[player1row][player1column] != 0) {
        player1row = rand() % 3;
        player1column = rand() % 3;
    }

    while (player1number == 0) {
        player1number = rand() % 10;
        if (player1number % 2 != 0 && player1number > 0) {
            break;
        }
        else {
            continue;
        }
    }
    Board[player1row][player1column] = player1number;
}


void RandomPlayer2(vector<vector<int>> &Board, int &player2row, int &player2column, int &player2number) {
    player2row = rand() % 3;
    player2column = rand() % 3;
    player2number = 0;
    while (Board[player2row][player2column] != 0) {
        player2row = rand() % 3;
        player2column = rand() % 3;
    }
    while (player2number == 0) {
        player2number = rand() % 10;
        if (player2number % 2 == 0 && player2number > 0) {
            break;
        }
        else {
            continue;
        }
    }
    Board[player2row][player2column] = player2number;
}





void HumanPlayer1(vector<vector<int>> &Board, int &player1row, int &player1column, int &player1number, string player1Name) {
    cout << player1Name << "'s turn: \n";
    // Row and column validation
    do {
        cout << "Enter your move row and column (1-3): ";
        cin >> player1row >> player1column;
        if (player1row < 1 || player1row > 3 || player1column < 1 || player1column > 3) {
            cout << "Invalid row or column! Please choose values between 1 and 3.\n";
        } else if (Board[player1row - 1][player1column - 1] != 0) {
            cout << "That spot is already taken! Choose another spot.\n";
        } else {
            break;
        }
    } while (true);

    // Number validation
    do {
        cout << "Enter a number from (1, 3, 5, 7, 9): ";
        cin >> player1number;
        if (player1number != 1 && player1number != 3 && player1number != 5 && player1number != 7 && player1number != 9) {
            cout << "Invalid number! Please choose an odd number from (1, 3, 5, 7, 9).\n";
        } else {
            break;
        }
    } while (true);

    Board[player1row - 1][player1column - 1] = player1number;
}





void HumanPlayer2(vector<vector<int>> &Board, int &player2row, int &player2column, int &player2number, string player2Name) {
    cout << player2Name << "'s turn: \n";

    // Row and column validation
    do {
        cout << "Enter your move row and column (1-3): ";
        cin >> player2row >> player2column;
        if (player2row < 1 || player2row > 3 || player2column < 1 || player2column > 3) {
            cout << "Invalid row or column! Please choose values between 1 and 3.\n";
        } else if (Board[player2row - 1][player2column - 1] != 0) {
            cout << "That spot is already taken! Choose another spot.\n";
        } else {
            break;
        }
    } while (true);

    // Number validation
    do {
        cout << "Enter a number from (2, 4, 6, 8): ";
        cin >> player2number;
        if (player2number != 2 && player2number != 4 && player2number != 6 && player2number != 8) {
            cout << "Invalid number! Please choose an even number from (2, 4, 6, 8).\n";
        } else {
            break;
        }
    } while (true);

    Board[player2row - 1][player2column - 1] = player2number;
}


int main()
{
vector<vector<int>> Board = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    string player1Name;
    string player2Name;
    int player1type;
    int player2type;
    int player1row;
    int player1column;
    int player2row;
    int player2column;
    int player1number;
    int player2number;

    cout << "Welcome to Numerical Tic-Tac-Toe Game. :)\n";
    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> player1type;
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> player2type;

    while (true)
    {

        if (player1type == 1 && player2type == 1)
        {
            BoardGame(Board);
            HumanPlayer1(Board, player1row, player1column, player1number, player1Name);
            if (isWin(Board))
            {
                cout << player1Name << " wins!" << endl;
                break;
            }
            BoardGame(Board);
            HumanPlayer2(Board, player2row, player2column, player2number, player2Name);
            if (isWin(Board))
            {
                cout << player2Name << " wins!" << endl;
                break;
            }
        }

        else if (player1type == 1 && player2type == 2)
        {
            BoardGame(Board);
            HumanPlayer1(Board, player1row, player1column, player1number, player1Name);
            if (isWin(Board))
            {
                cout << player1Name << " wins!" << endl;
                break;
            }
            BoardGame(Board);
            RandomPlayer2(Board, player2row, player2column, player2number);
            if (isWin(Board))
            {
                cout << "Computer wins!" << endl;
                break;
            }
        }

        else if (player1type == 2 && player2type == 1)
        {
            BoardGame(Board);
            RandomPlayer1(Board, player1row, player1column, player1number);
            if (isWin(Board))
            {
                cout << "Computer wins!" << endl;
                break;
            }
            BoardGame(Board);
            HumanPlayer2(Board, player2row, player2column, player2number, player2Name);
            if (isWin(Board))
            {
                cout << player2Name << " wins!" << endl;
                break;
            }
        }

        else if (player1type == 2 && player2type == 2)
        {
            BoardGame(Board);
            RandomPlayer1(Board, player1row, player1column, player1number);
            if (isWin(Board))
            {
                cout << "Computer wins!" << endl;
                break;
            }
            BoardGame(Board);
            RandomPlayer2(Board, player2row, player2column, player2number);
            if (isWin(Board))
            {
                cout << "Computer wins!" << endl;
                break;
            }
        }
    }

    return 0;
}
