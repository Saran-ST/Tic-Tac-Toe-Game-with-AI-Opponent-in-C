#include <stdio.h>

// Function prototypes
void initializeBoard(char board[3][3]);
void printBoard(char board[3][3]);
int checkWin(char board[3][3]);
int isDraw(char board[3][3]);

int main() {
    char board[3][3];
    int row, col;
    int player = 1;
    int moves = 0;
    int winner = 0;

    initializeBoard(board);

    printf("Tic-Tac-Toe Game\n");
    printf("Player 1 (X)  -  Player 2 (O)\n");

    while (!winner && !isDraw(board)) {
        printBoard(board);
        printf("Player %d, enter your move (row and column: 1-3 1-3): ", player);
        scanf("%d %d", &row, &col);

        // Convert to 0-based index
        row--; col--;

        // Check if move is valid
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = (player == 1) ? 'X' : 'O';
            moves++;
            winner = checkWin(board);

            if (!winner)
                player = (player == 1) ? 2 : 1; // Switch player
        } else {
            printf("Invalid move! Try again.\n");
        }
    }

    printBoard(board);

    if (winner)
        printf("Player %d wins!\n", player);
    else
        printf("It's a draw!\n");

    return 0;
}

// Initialize the board with empty spaces
void initializeBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Print the current state of the board
void printBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2)
            printf("---|---|---\n");
    }
    printf("\n");
}

// Check for a win (returns 1 if current player wins)
int checkWin(char board[3][3]) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' '))
            return 1;
    }
    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return 1;

    return 0;
}

// Check if the board is full and no winner
int isDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}
