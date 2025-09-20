#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

#define PLAYER 'O'
#define AI 'X'

// ---------- Function Prototypes ----------
void printMenu();
void playGame();
void viewResults();
void saveResult(const char *result);
void printBoard(char board[3][3]);
bool isMovesLeft(char board[3][3]);
int evaluate(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMax);
void findBestMove(char board[3][3], int *bestRow, int *bestCol);
void makeMove(char board[3][3], int row, int col, char player);
void delay(int ms);

// ---------- Menu ----------
void printMenu() {
    int choice;
    while (1) {
        system(CLEAR);
        printf("\n=== TIC TAC TOE 3D STYLE ===\n");
        printf("1. Play Game\n");
        printf("2. View Saved Results\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: playGame(); break;
            case 2: viewResults(); break;
            case 3: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

// ---------- Print 3D board ----------
void printBoard(char board[3][3]) {
    system(CLEAR);
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("     ");
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("||");
        }
        printf("\n");
        if (i < 2) printf("    ====||====||====\n");
    }
    printf("\n");
}

// ---------- Save results to file ----------
void saveResult(const char *result) {
    FILE *fp = fopen("results.txt", "a");
    if (fp == NULL) {
        printf("Error saving results!\n");
        return;
    }
    fprintf(fp, "%s\n", result);
    fclose(fp);
}

// ---------- View saved results ----------
void viewResults() {
    system(CLEAR);
    FILE *fp = fopen("results.txt", "r");
    if (fp == NULL) {
        printf("No saved results yet.\n");
    } else {
        char line[100];
        printf("\n=== Saved Game Results ===\n");
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
        }
        fclose(fp);
    }
    printf("\nPress Enter to go back...");
    getchar(); getchar();
}

// ---------- Check moves ----------
bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// ---------- Evaluate ----------
int evaluate(char b[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == AI) return +10;
            else if (b[row][0] == PLAYER) return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == AI) return +10;
            else if (b[0][col] == PLAYER) return -10;
        }
    }
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == AI) return +10;
        else if (b[0][0] == PLAYER) return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == AI) return +10;
        else if (b[0][2] == PLAYER) return -10;
    }
    return 0;
}

// ---------- Minimax ----------
int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    int val = minimax(board, depth + 1, false);
                    best = (best > val) ? best : val;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    int val = minimax(board, depth + 1, true);
                    best = (best < val) ? best : val;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// ---------- Find AI move ----------
void findBestMove(char board[3][3], int *bestRow, int *bestCol) {
    int bestVal = -1000;
    *bestRow = -1;
    *bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    *bestRow = i;
                    *bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

// ---------- Make move ----------
void makeMove(char board[3][3], int row, int col, char player) {
    board[row][col] = player;
}

// ---------- Delay ----------
void delay(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

// ---------- Play game ----------
void playGame() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    int row, col;
    while (1) {
        printBoard(board);
        printf("Enter your move (row and col: 0-2): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move. Try again.\n");
            delay(1000);
            continue;
        }

        makeMove(board, row, col, PLAYER);
        if (evaluate(board) == -10) {
            printBoard(board);
            printf("🎉 You win!\n");
            saveResult("Player won");
            delay(2000);
            break;
        }
        if (!isMovesLeft(board)) {
            printBoard(board);
            printf("🤝 It's a draw!\n");
            saveResult("Draw");
            delay(2000);
            break;
        }

        int aiRow, aiCol;
        findBestMove(board, &aiRow, &aiCol);
        makeMove(board, aiRow, aiCol, AI);
        printBoard(board);
        printf("AI is thinking...\n");
        delay(1500);

        if (evaluate(board) == 10) {
            printBoard(board);
            printf("💻 AI wins!\n");
            saveResult("AI won");
            delay(2000);
            break;
        }
        if (!isMovesLeft(board)) {
            printBoard(board);
            printf("🤝 It's a draw!\n");
            saveResult("Draw");
            delay(2000);
            break;
        }
    }
    printf("Press Enter to return to menu...");
    getchar(); getchar();
}

// ---------- Main ----------
int main() {
    printMenu();
    return 0;
}
