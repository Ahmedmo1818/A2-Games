#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "BoardGame_Classes.h"
using namespace std;

class Pyramidic_X_O_Board : public Board<char>
{
private:
    int minSeqLen;

    bool inBounds(int x, int y) const
    {
        return x >= 0 && x < rows && y >= columns / 2 - x && y <= columns / 2 + x;
    }

public:
    Pyramidic_X_O_Board()
    {
        rows = 3;
        columns = 5;
        n_moves = 0;
        minSeqLen = 3;
        board = new char *[rows];
        for (int i = 0; i < rows; i++)
        {
            board[i] = new char[columns]{};
        }
    }

    ~Pyramidic_X_O_Board()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override
    {
        x--;
        y--;
        if (inBounds(x, y) && board[x][y] == 0)
        {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override
    {
        for (int i = 0; i < rows; i++)
        {
            int offset = (columns - (2 * i + 1)) / 2;
            cout << string(offset * 2, ' ');
            for (int j = 0; j < 2 * i + 1; j++)
            {
                cout << (board[i][j + offset] ? board[i][j + offset] : '.') << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override
    {
        int dx[] = {0, 1, 1, -1};
        int dy[] = {1, 0, 1, 1};

        for (int i = 0; i < rows; i++)
        {
            for (int j = columns / 2 - i; j <= columns / 2 + i; j++)
            {
                if (!board[i][j])
                    continue;
                for (int d = 0; d < 4; d++)
                {
                    int count = 1;
                    for (int k = 1; k < minSeqLen; k++)
                    {
                        int nx = i + k * dx[d];
                        int ny = j + k * dy[d];
                        if (inBounds(nx, ny) && board[nx][ny] == board[i][j])
                            count++;
                        else
                            break;
                    }
                    if (count >= minSeqLen)
                        return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override
{
    // The total number of cells in the pyramid board is 9 (1 + 2 + 3 + 4 = 9)
    return n_moves == 9 && !is_win();  // Check if all moves are made and no winner
}


    bool game_is_over() override
    {
        return is_win() || is_draw();
    }
};

class SimplePlayer : public Player<char>
{
public:
    SimplePlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int &x, int &y) override
    {
        cout << this->getname() << ", enter your move (row and column): ";
        cin >> x >> y;
    }
};

// Four_in_a_row_Random_Player Class
template <typename T>
class Simple_Random_Player : public RandomPlayer<T>
{
public:
    Simple_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int &x, int &y)
    {
        x = rand() % 4;
        y = rand() % 4;
    }
};

int main()
{

    using namespace std;

    int choice;
    Player<char> *players[2];
    Pyramidic_X_O_Board *B = new Pyramidic_X_O_Board();
    string playerXName, playerOName;

    cout << "Welcome to Pyramidic X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new SimplePlayer(playerXName, 'X');
        break;
    case 2:
        players[0] = new Simple_Random_Player<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        delete B;
        return 1;
    }

    // Set up player 2
    cout << "Enter Player O name: ";
    cin >> playerOName;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new SimplePlayer(playerOName, 'O');
        break;
    case 2:
        players[1] = new Simple_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        delete players[0];
        delete B;
        return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }

    return 0;
}
