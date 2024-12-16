#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

// Abstract Board Class
template <typename T>
class Board {
protected:
    int rows, columns;
    int n_moves = 0;
    T** board;

public:
    virtual bool update_board(int x, int y, int new_x, int new_y, T symbol) = 0;
    virtual void display_board() = 0;
    virtual bool is_win() = 0;
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;
};

// Player Class
template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;

public:
    Player(string n, T symbol) : name(n), symbol(symbol) {}
    Player(T symbol) : name("Computer"), symbol(symbol) {}

    virtual void getmove(int &x, int &y, int &new_x, int &new_y) = 0;
    T getsymbol() { return symbol; }
    string getname() { return name; }
    void setBoard(Board<T>* b) { boardPtr = b; }
};

// Game Manager Class
template <typename T>
class GameManager {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];

public:
    GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) : boardPtr(bPtr) {
        players[0] = playerPtr[0];
        players[1] = playerPtr[1];
    }

    void run() {
        int x, y, new_x, new_y;
        boardPtr->display_board();

        while (!boardPtr->game_is_over()) {
            for (int i : {0, 1}) {
                cout << players[i]->getname() << "'s turn (" << players[i]->getsymbol() << "):\n";
                players[i]->getmove(x, y, new_x, new_y);
                while (!boardPtr->update_board(x, y, new_x, new_y, players[i]->getsymbol())) {
                    cout << "Invalid move! Try again.\n";
                    players[i]->getmove(x, y, new_x, new_y);
                }
                boardPtr->display_board();
                if (boardPtr->is_win()) {
                    cout << players[i]->getname() << " wins!\n";
                    return;
                }
                if (boardPtr->is_draw()) {
                    cout << "It's a draw!\n";
                    return;
                }
            }
        }
    }
};









// Random Player Class
template <typename T>
class RandomPlayer : public Player<T> {
public:
    RandomPlayer(T symbol) : Player<T>(symbol) {}

    void getmove(int &x, int &y, int &new_x, int &new_y) override {
        x = rand() % 4;
        y = rand() % 4;
        new_x = x + (rand() % 3 - 1); // Adjacent move
        new_y = y + (rand() % 3 - 1);
    }
};











// 4 x 4 Tic-Tac-Toe Board Class
template <typename T>
class TicTacToeBoard : public Board<T> {
private:
    vector<vector<T>> board;

public:
    TicTacToeBoard() {
        board = {
            {'O', 'X', 'O', 'X'},
            {'.', '.', '.', '.'},
            {'.', '.', '.', '.'},
            {'X', 'O', 'X', 'O'}};
    }

    bool update_board(int x, int y, int new_x, int new_y, T symbol) override {
        // Validate move: within bounds, adjacent, and new cell is empty
        if (new_x < 0 || new_x >= 4 || new_y < 0 || new_y >= 4 || board[new_x][new_y] != '.' ||
            (abs(new_x - x) + abs(new_y - y) != 1)) {
            return false;
        }
        // Perform move
        board[x][y] = '.';
        board[new_x][new_y] = symbol;
        return true;
    }

    void display_board() override {
        for (const auto &row : board) {
            for (const auto &cell : row) {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }

    bool is_win() override {
        // Check rows, columns, and diagonals for a win
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 2; ++j) {
                // Check horizontal and vertical
                if (board[i][j] != '.' && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
                    return true;
                if (board[j][i] != '.' && board[j][i] == board[j + 1][i] && board[j][i] == board[j + 2][i])
                    return true;
            }
        }
        // Check diagonals
        for (int i = 0; i < 2; ++i) {
            if (board[i][i] != '.' && board[i][i] == board[i + 1][i + 1] && board[i][i] == board[i + 2][i + 2])
                return true;
            if (board[i][3 - i] != '.' && board[i][3 - i] == board[i + 1][2 - i] && board[i][3 - i] == board[i + 2][1 - i])
                return true;
        }
        return false;
    }

    bool is_draw() override {
        // Check for empty cells
        for (const auto &row : board) {
            for (const auto &cell : row) {
                if (cell == '.')
                    return false;
            }
        }
        return !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }





    
};

// 4 x 4 Tic-Tac-Toe Player Class
template <typename T>
class TicTacToePlayer : public Player<T> {
public:
    TicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int &x, int &y, int &new_x, int &new_y) override {
        cout << this->getname() << ", enter the current row and column of your token (1-4): ";
        cin >> x >> y;
        --x; --y;
        cout << this->getname() << ", enter the new row and column (1-4): ";
        cin >> new_x >> new_y;
        --new_x; --new_y;
    }
};



















// Main Function
int main() {
    Player<char>* players[2];
    TicTacToeBoard<char>* board = new TicTacToeBoard<char>();
    string name1, name2;
    int choice;

    cout << "Welcome to 4 x 4 Tic-Tac-Toe!\n";

    // Set up Player 1
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;
    players[0] = (choice == 1)
        ? static_cast<Player<char>*>(new TicTacToePlayer<char>(name1, 'X'))
        : static_cast<Player<char>*>(new RandomPlayer<char>('X'));

    // Set up Player 2
    cout << "Enter Player 2 name: ";
    cin >> name2;
    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;
    players[1] = (choice == 1)
        ? static_cast<Player<char>*>(new TicTacToePlayer<char>(name2, 'O'))
        : static_cast<Player<char>*>(new RandomPlayer<char>('O'));

    // Run the game
    GameManager<char> game(board, players);
    game.run();

    // Clean up
    delete board;
    delete players[0];
    delete players[1];
    return 0;
}










































