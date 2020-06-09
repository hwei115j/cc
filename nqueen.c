#include "stdio.h"

int count = 1;

int print_board(int (*board)[8])
{
    int i;
    int j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if(board[i][j])
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n\n");
}

int conflict(int (*board)[8], int row, int col)
{
    int i;
    int j;

    for (i = 0; i < row; i++) {
        if (board[i][col])
            return 1;
        j = row - i;
        if (0 < (col - j + 1) && board[i][col - j])
            return 1;
        if ((col + j) < 8 && board[i][col + j])
            return 1;
    }
    return 0;
}


int solve(int (*board)[8], int row)
{
    int i;

    if (row == 8) {
        printf("%d\n", count++);
        print_board(board);
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (!conflict(board, row, i)) {
            board[row][i] = 1;
            solve(board, row + 1);
            board[row][i] = 0;
        }
    }
}

int main()
{
    int board[64];
    int i;

    solve(board, 0);

    return 0;
}
