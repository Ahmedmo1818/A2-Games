#include <iostream>
#include "BoardGame_Classes.h"
#include "Four_in_a_row.h"

using namespace std;

int main()
{
    int choice;
    Player<char> *players[2];
    Four_in_a_row_Board<char> *B = new Four_in_a_row_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Four_in_a_row Game. :)\n";

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
        players[0] = new Four_in_a_row_Player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new Four_in_a_row_Random_Player<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Set up player 2
    cout << "Enter Player O name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new Four_in_a_row_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new Four_in_a_row_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
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
