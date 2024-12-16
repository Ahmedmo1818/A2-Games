#include <iostream>
#include <vector>
using namespace std;
class Player {
public:
    char mark;
    Player(char m) : mark(m) {}
};

class Board {
private:
    vector<vector<char>> grid;
    int size;

public:
    Board(int s) : size(s) {
        grid.resize(size, vector<char>(size, ' '));
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << grid[i][j];
                if (j < size - 1) cout << "|";
            }
            cout <<endl;
            if (i < size - 1) {
                for (int k = 0; k < size - 1; ++k) cout << "---";
                cout << endl;
            }
        }
    }

    bool placeMark(int row, int col, char mark) {
        if (row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == ' ') {
            grid[row][col] = mark;
            return true;
        }
        return false;
    }

    int countThreeInARow(char mark) {
        int count = 0;


        for (int i = 0; i < size; ++i) {
            for (int j = 0; j <= size - 3; ++j) {
                if (grid[i][j] == mark && grid[i][j + 1] == mark && grid[i][j + 2] == mark) {
                    count++;
                }
            }
        }


        for (int j = 0; j < size; ++j) {
            for (int i = 0; i <= size - 3; ++i) {
                if (grid[i][j] == mark && grid[i + 1][j] == mark && grid[i + 2][j] == mark) {
                    count++;
                }
            }
        }


        for (int i = 0; i <= size - 3; ++i) {
            for (int j = 0; j <= size - 3; ++j) {
                if (grid[i][j] == mark && grid[i + 1][j + 1] == mark && grid[i + 2][j + 2] == mark) {
                    count++;
                }
            }
            for (int j = 2; j < size; ++j) {
                if (grid[i][j] == mark && grid[i + 1][j - 1] == mark && grid[i + 2][j - 2] == mark) {
                    count++;
                }
            }
        }

        return count;
    }

    bool isFull() {
        for (const auto& row : grid) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }
};

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

public:
    Game() : board(5), player1('X'), player2('O'), currentPlayer(&player1) {}

    void play() {
        int turns = 0;

        while (turns < 24) {
            board.display();
            int row, col;

            cout << "Player " << currentPlayer->mark << ", enter row and column (0-4): ";
            cin >> row >> col;

            if (board.placeMark(row, col, currentPlayer->mark)) {
                turns++;
                currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
            } else {
                cout << "Invalid move. Try again." << std::endl;
            }
        }

        board.display();

        int countX = board.countThreeInARow('X');
        int countO = board.countThreeInARow('O');

        cout << "Player X has " << countX << " three-in-a-rows." << endl;
        cout << "Player O has " << countO << " three-in-a-rows." << endl;

        if (countX > countO) {
            cout << "Player X wins!" << endl;
        } else if (countO > countX) {
            cout << "Player O wins!" << endl;
        } else {
            cout << "It's a tie!" << endl;
        }
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}