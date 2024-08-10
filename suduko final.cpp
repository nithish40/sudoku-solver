#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int generate_randomr(int n) {
    return (rand() % n);
}
int generate_randomc(int n) {
    return (rand() % n);
}
int generate_randomv(int n) {
    return (rand() % n) + 1;
}
void print(int **arr, int n) {
    printf("Sudoku board:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int issafe(int **arr, int row, int col, int val, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[row][i] == val || arr[i][col] == val)
            return 0;
    }
    int sqrt_n = sqrt(n);
    int box_row_start = row - row % sqrt_n;
    int box_col_start = col - col % sqrt_n;
    
    for (int i = 0; i < sqrt_n; i++) {
        for (int j = 0; j < sqrt_n; j++) {
            if (arr[box_row_start + i][box_col_start + j] == val)
                return 0;
        }
    }
    return 1;
}

void generate_sudoku(int **arr, int n) {
    int count = (n == 6) ? 8 : (n == 9) ? 16 : 12;
    while (count > 0) {
        int rows = generate_randomr(n);
        int cols = generate_randomc(n);
        
        if (arr[rows][cols] == 0) {
            int val = generate_randomv(n);
            if (issafe(arr, rows, cols, val, n)) {
                arr[rows][cols] = val;
                count--;
            }
        }
    }
    print(arr, n);
}

int sudoku_solver(int **arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 0) {
                for (int val = 1; val <= n; val++) {
                    if (issafe(arr, i, j, val, n)) {
                        arr[i][j] = val;
                        if (sudoku_solver(arr, n))
                            return 1;
                        arr[i][j] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    srand(time(NULL));
    int n, x;
    FILE *file;
    
    printf("Enter the order of Sudoku (6, 8, or 9): ");
    scanf("%d", &n);

    int **arr = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        arr[i] = (int *)calloc(n, sizeof(int));
    }
    printf("If you want to generate a new Sudoku, enter 0\n");
    printf("If you want to solve a Sudoku given in a file, enter 1\n");
    scanf("%d", &x);

    if (x == 0) {
        generate_sudoku(arr, n);
    } 
    else if (x == 1) {
        switch(n) {
            case 6: file = fopen("sudokuinput6.txt", "r"); break;
            case 8: file = fopen("sudokuinput8.txt", "r"); break;
            case 9: file = fopen("sudokuinput9.txt", "r"); break;
            default: printf("Invalid Sudoku order.\n"); return 1;
        }
        if (!file) {
            printf("Failed to open file.\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fscanf(file, "%d", &arr[i][j]);
            }
        }
        fclose(file);
        print(arr, n);
    }
    else {
        printf("Invalid choice.\n");
        for (int i = 0; i < n; i++)
            free(arr[i]);
        free(arr);
        return 1;
    }
    if (sudoku_solver(arr, n)) {
        print(arr, n);
    } else {
        printf("No solution exists.\n");
    }
    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);

    return 0;
}
