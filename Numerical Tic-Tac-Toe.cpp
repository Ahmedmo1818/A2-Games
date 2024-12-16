#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

class Numerical_Tic_Tac_Toe_Board {
private:
    int** board;
    int rows, columns, n_moves;
    set<int> valid_numbers_player1;  // Odd numbers for Player 1
    set<int> valid_numbers_player2;  // Even numbers for Player 2/Computer

public:
    Numerical_Tic_Tac_Toe_Board() {
        rows = 3;
        columns = 3;
        board = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new int[columns];
            fill(board[i], board[i] + columns, 0);  // Initialize board with 0s
        }
        n_moves = 0;

        // Initialize valid numbers for Player 1 and Player 2
        for (int i = 1; i <= 9; i += 2) valid_numbers_player1.insert(i); // Odd numbers
        for (int i = 2; i <= 8; i += 2) valid_numbers_player2.insert(i); // Even numbers
    }

    ~Numerical_Tic_Tac_Toe_Board() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    void display_board() {
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

    // Update the board at (x, y) with the given number
    bool update_board(int x, int y, int number) {
        x -= 1;
        y -= 1;  // Convert to zero-based indexing
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == 0) {
            board[x][y] = number;
            n_moves++;
            return true;
        }
        return false;
    }

    // Check if the sum of a line equals 15
    bool is_sum_15(const vector<pair<int, int>>& positions) {
        int sum = 0;
        for (auto& pos : positions) {
            sum += board[pos.first][pos.second];
        }
        return sum == 15;
    }

    // Check if a player has a winning line
    bool is_win() {
        vector<vector<pair<int, int>>> lines = {
            {{0, 0}, {0, 1}, {0, 2}}, // Row 1
            {{1, 0}, {1, 1}, {1, 2}}, // Row 2
            {{2, 0}, {2, 1}, {2, 2}}, // Row 3
            {{0, 0}, {1, 0}, {2, 0}}, // Column 1
            {{0, 1}, {1, 1}, {2, 1}}, // Column 2
            {{0, 2}, {1, 2}, {2, 2}}, // Column 3
            {{0, 0}, {1, 1}, {2, 2}}, // Diagonal 1
            {{0, 2}, {1, 1}, {2, 0}}  // Diagonal 2
        };

        for (auto& line : lines) {
            if (is_sum_15(line)) return true;
        }
        return false;
    }

    // Check if the board is a draw
    bool is_draw() {
        return n_moves == rows * columns;
    }

    // Accessors for valid numbers
    set<int>& get_valid_numbers_player1() { return valid_numbers_player1; }
    set<int>& get_valid_numbers_player2() { return valid_numbers_player2; }

    // Check if a cell is empty
    bool is_cell_empty(int x, int y) {
        return board[x - 1][y - 1] == 0;  // Return true if the cell is empty (i.e., 0)
    }
};

class Player {
protected:
    string name;

public:
    Player(string n) : name(n) {}
    virtual void getmove(int& x, int& y, int& number) = 0;
    string getname() const { return name; }
};

class Numerical_Player : public Player {
private:
    set<int>& valid_numbers;

public:
    Numerical_Player(string n, set<int>& valid_nums) : Player(n), valid_numbers(valid_nums) {}

    void getmove(int& x, int& y, int& number) override {
        cout << name << ", enter your move (row column number): ";
        cin >> x >> y >> number;
        while (valid_numbers.find(number) == valid_numbers.end()) {
            cout << "Invalid number. Please enter a valid number: ";
            cin >> number;
        }
        valid_numbers.erase(number);  // Remove chosen number from valid options
    }
};

class Computer_Player : public Player {
private:
    set<int>& valid_numbers;
    Numerical_Tic_Tac_Toe_Board& board;  // Add a reference to the board

public:
    Computer_Player(string n, set<int>& valid_nums, Numerical_Tic_Tac_Toe_Board& b) 
        : Player(n), valid_numbers(valid_nums), board(b) {}

    void getmove(int& x, int& y, int& number) override {
        cout << name << " is making a move..." << endl;

        // Check if there are valid numbers left
        if (valid_numbers.empty()) {
            cout << "No valid numbers left for the computer!" << endl;
            return;
        }

        // Choose the smallest available number from valid_numbers
        number = *valid_numbers.begin(); 
        valid_numbers.erase(valid_numbers.begin()); // Remove the chosen number from the set

        // Try to find an empty cell (0 means empty)
        for (x = 1; x <= 3; ++x) {
            for (y = 1; y <= 3; ++y) {
                // Check if the current cell is empty (represented by 0)
                if (board.is_cell_empty(x, y)) {
                    // Update the board with the selected number
                    return;  // Exit once the move is made
                }
            }
        }
    }
};

int main() {
    Numerical_Tic_Tac_Toe_Board board;  // Create the board
    // Game mode selection
    cout << "Welcome to Numerical Tic-Tac-Toe!" << endl;
    cout << "Select game mode: " << endl;
    cout << "1. Player vs. Player" << endl;
    cout << "2. Player vs. Computer" << endl;
    int game_mode;
    cin >> game_mode;
    // Player initialization based on game mode
    Numerical_Player player1("Player 1", board.get_valid_numbers_player1());
    Player* player2;

    Numerical_Player player2_obj("Player 2", board.get_valid_numbers_player2());
    Computer_Player computer_obj("Computer", board.get_valid_numbers_player2(), board);

    if (game_mode == 1) {
        // Player vs. Player
        player2 = &player2_obj;
    } else if (game_mode == 2) {
        // Player vs. Computer
        player2 = &computer_obj;
    } else {
        cout << "Invalid selection. Exiting..." << endl;
        return 0;
    }

    // Display the initial empty board
    board.display_board();

    // Game loop
    int x, y, number;
    while (!board.is_win() && !board.is_draw()) {
        // Player 1's turn (human)
        player1.getmove(x, y, number);
        board.update_board(x, y, number);
        board.display_board();

        // Check if the game ended after Player 1's move
        if (board.is_win() || board.is_draw()) {
            break;  // Exit if Player 1 has won or it's a draw
        }

        // Player 2's turn (computer or human depending on game mode)
        player2->getmove(x, y, number);
        board.update_board(x, y, number);
        board.display_board();

        // Check if the game ended after Player 2's move
        if (board.is_win() || board.is_draw()) {
            break;  // Exit if Player 2 has won or it's a draw
        }
    }

    // Output the game result
    if (board.is_win()) {
        cout << "We have a winner!" << endl;
    } else if (board.is_draw()) {
        cout << "It's a draw!" << endl;
    }}

