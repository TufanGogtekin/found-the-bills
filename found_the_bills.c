#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER1 '1'
#define PLAYER2 '2'
#define nonplace '*'

char** initializeBoard(int);
void gameBoard(char**, int, int*, int*, int*);
int hasCapturedBills(int*);
void movePlayer(char**, int, int*, int*, char, int*, int*, int*, int*, int*, char*);

int main() {
    int size;
    int oldcoin[7] = {0}; // paraların alınıp alınmadığını tutan dizi
    char coin[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    int konumx[7], konumy[7];

    printf("Enter the size of the game board(minimum 5): ");
    scanf("%d", &size);
    while (size < 5) {
        printf("Minimum size is 5.\n");
        printf("Enter the size of the game board(minimum 5): ");
        scanf("%d", &size);
    }

    int raund = 7;
    int bank1 = 0, bank2 = 0;

    char** board = initializeBoard(size);

    int player1X = 0, player1Y = 0;
    int player2X = size - 1, player2Y = size - 1;
    board[player1X][player1Y] = PLAYER1;
    board[player2X][player2Y] = PLAYER2;

    srand(time(NULL));
    for (int i = 0; i < 7; i++) {
        konumx[i] = rand() % size;
        konumy[i] = rand() % size;

        while (board[konumx[i]][konumy[i]] != '.') {
            konumx[i] = rand() % size;
            konumy[i] = rand() % size;
        }
        board[konumx[i]][konumy[i]] = coin[i];
    }

    printf("Welcome to found the bills game!\n");
    printf("Player 1 (1) starts at (0, 0) and Player 2 (2) starts at (%d, %d).\n", size - 1, size - 1);

    while (1) {
        printf("\nCurrent Board:\n");
        gameBoard(board, size, konumx, konumy, oldcoin);

        // Player 1's turn
        char move;
        printf("\nPlayer 1's turn (1): Enter move (U/D/L/R): ");
        scanf(" %c", &move);
        movePlayer(board, size, &player1X, &player1Y, move, &raund, &bank1, konumx, konumy, oldcoin, coin);
        printf("Player 1 has %d.\n", bank1);
        if (hasCapturedBills(&raund)) {
            gameBoard(board, size, konumx, konumy, oldcoin);
            if (bank1 > bank2)
                printf("\nPlayer 1 has %d. Player 1 wins!\n", bank1);
            else if (bank2 > bank1)
                printf("\nPlayer 2 has %d. Player 2 wins!\n", bank2);
            else
                printf("\nDraw! Both players have %d.\n", bank1);
            break;
        }

        printf("\nCurrent Board:\n");
        gameBoard(board, size, konumx, konumy, oldcoin);

        // Player 2's turn
        printf("\nPlayer 2's turn (2): Enter move (U/D/L/R): ");
        scanf(" %c", &move);
        movePlayer(board, size, &player2X, &player2Y, move, &raund, &bank2, konumx, konumy, oldcoin, coin);
        printf("Player 2 has %d.\n", bank2);
        if (hasCapturedBills(&raund)) {
            gameBoard(board, size, konumx, konumy, oldcoin);
            if (bank2 > bank1)
                printf("\nPlayer 2 has %d. Player 2 wins!\n", bank2);
            else if (bank1 > bank2)
                printf("\nPlayer 1 has %d. Player 1 wins!\n", bank1);
            else
                printf("\nDraw! Both players have %d.\n", bank1);
            break;
        }
    }

    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}

char** initializeBoard(int size) {
    char** board = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        board[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            board[i][j] = '.';
        }
    }
    return board;
}

void gameBoard(char** board, int size, int* konumx, int* konumy, int* oldcoin) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int yazildi = 0;
            for (int k = 0; k < 7; k++) {
                if (i == konumx[k] && j == konumy[k]) {
                    if (board[i][j] == PLAYER1 || board[i][j] == PLAYER2)
                        printf("%c ", board[i][j]);
                    else if (oldcoin[k] == 1)
                        printf("* ");
                    else
                        printf(". ");
                    yazildi = 1;
                    break;
                }
            }
            if (!yazildi)
                printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int hasCapturedBills(int* raund) {
    return (*raund == 0);
}

void movePlayer(char** board, int size, int* x, int* y, char direction, int* raund, int* bank1, int* konumx, int* konumy, int* oldcoin, char* coin) {
    int newX = *x, newY = *y;
    char playerId = board[*x][*y];

    switch (direction) {
        case 'U': newX--; break;
        case 'D': newX++; break;
        case 'L': newY--; break;
        case 'R': newY++; break;
        default:
            printf("Invalid move! Use U, D, L, or R.\n");
            return;
    }

    if (newX < 0 || newX >= size || newY < 0 || newY >= size ||
        board[newX][newY] == PLAYER1 || board[newX][newY] == PLAYER2) {
        printf("Invalid move!\n");
        return;
    }

    for (int i = 0; i < 7; i++) {
        if (newX == konumx[i] && newY == konumy[i] && oldcoin[i] == 1) {
            printf("Coin already collected here. Move elsewhere.\n");
            return;
        }
    }

    board[*x][*y] = ','; // iz bırak
    *x = newX;
    *y = newY;

    int values[7] = {1, 2, 5, 10, 20, 50, 100};
    for (int i = 0; i < 7; i++) {
        if (*x == konumx[i] && *y == konumy[i] && oldcoin[i] == 0) {
            *bank1 += values[i];
            (*raund)--;
            oldcoin[i] = 1;
            coin[i] = '*';
        }
    }

    board[*x][*y] = playerId;
}
