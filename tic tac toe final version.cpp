#include <iostream>

using namespace std;

char matrix[3][3];  // Matrix declaration
int moves = 0; // Counter to keep track of moves
int playerpoints = 0;
int computerpoints = 0;

char check(void); // Function declarations
void initialmatrix(void);
void playermove(void);
void computermove(void);
void displaymatrix(void);

void initialmatrix(void) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = ' ';
        }
    }
}

void playermove(void) {
    int x, y;

    cout << "Enter X,Y coordinates for your move: ";
    cin >> x >> y;

    x--; y--;

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || matrix[x][y] != ' ') {
        cout << "Invalid move, try again.\n";
        playermove();
    } else {
        matrix[x][y] = 'X';
    }
}


void computermove(void) {
    // Check if the computer can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (matrix[i][j] == ' ') {
                matrix[i][j] = 'O';
                if (check() == 'O') {
                    return; // Computer wins
                }
                matrix[i][j] = ' '; // Undo the move
            }
        }
    }

    // Check if the opponent (human) can win in the next move, block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (matrix[i][j] == ' ') {
                matrix[i][j] = 'X';
                if (check() == 'X') {
                    matrix[i][j] = 'O'; // Block the human player
                    return;
                }
                matrix[i][j] = ' '; // Undo the move
            }
        }
    }

    // If there's no immediate winning move for the computer or the opponent, play in a corner if available
    if (matrix[0][0] == ' ') {
        matrix[0][0] = 'O';
        return;
    }
    if (matrix[0][2] == ' ') {
        matrix[0][2] = 'O';
        return;
    }
    if (matrix[2][0] == ' ') {
        matrix[2][0] = 'O';
        return;
    }
    if (matrix[2][2] == ' ') {
        matrix[2][2] = 'O';
        return;
    }

    // If corners are not available, play in the center
    if (matrix[1][1] == ' ') {
        matrix[1][1] = 'O';
        return;
    }

    // Play in any remaining edge position
    if (matrix[0][1] == ' ') {
        matrix[0][1] = 'O';
        return;
    }
    // Similar logic for other edge positions

    // If the board is full, it's a draw - this should be handled in the game loop
    
}

void displaymatrix(void) {
    for (int t = 0; t < 3; t++) {
        cout << " " << matrix[t][0] << " | " << matrix[t][1] << " | " << matrix[t][2] << " ";
        if (t != 2) {
            cout << "\n---|---|---\n";
        }
    }
    cout << "\n";
}
// Function to check for a winner
char check(void) {
    for (int i = 0; i < 3; i++) {
        if (matrix[i][0] == matrix[i][1] && matrix[i][0] == matrix[i][2] && matrix[i][0] != ' ')
            return matrix[i][0]; // Check rows
    }

    for (int i = 0; i < 3; i++) {
        if (matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i] && matrix[0][i] != ' ')
            return matrix[0][i]; // Check columns
    }

    if (matrix[0][0] == matrix[1][1] && matrix[0][0] == matrix[2][2] && matrix[0][0] != ' ')
        return matrix[0][0]; // Check diagonal (top-left to bottom-right)

    if (matrix[0][2] == matrix[1][1] && matrix[0][2] == matrix[2][0] && matrix[0][2] != ' ')
        return matrix[0][2]; // Check diagonal (top-right to bottom-left)

    return ' ';
}



int main() {
    char done;

    cout << " Tic Tac Toe " << endl;
    cout << "You will be playing against the AI as 'X'" << endl;

    for (int round = 1; round <= 3; ++round) {
        moves = 0;
        done = ' ';
        initialmatrix();

        do {
            displaymatrix();
            playermove();
            moves++;
            done = check(); // Check for a winner
            if (done != ' ') break; // If a winner is found
            if (moves >= 9) {
                done = 'D'; // Game board is full, declare a draw
                break;
            }
            computermove();
            moves++;
            done = check(); // Check for a winner again
        } while (done == ' ');

        displaymatrix(); 

        if (done == 'X') {
            cout << "Human won this round!" << endl;
            playerpoints++;
        } else if (done == 'O') {
            cout << "AI won this round against you!" << endl;
            computerpoints++;
        } else {
            cout << "It's a draw in this round!" << endl;
        }

        cout << "Your points: " << playerpoints << endl;
        cout << "AI points: " << computerpoints << endl;
    }

    cout << "\nGame Over!" << endl;

    if (playerpoints > computerpoints) {
        cout << "Congratulations! Human wins the game :)) !" << endl;
    } else if (playerpoints < computerpoints) {
        cout << " AI wins the game :0 " << endl;
    } else {
        cout << "It's a tie in the game ... noone wins :( !" << endl;
    }

    return 0;
}


