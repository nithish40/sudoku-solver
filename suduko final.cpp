#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
//generate random value for rows
int generate_randomr(int n){
    while(1){
    int r=(rand() % n)+1;
    return r;
    }
    
}
//generate random value for columns
int generate_randomc(int n){
    while(1){
    int r=(rand() % n)+1;
    return r;
    }
    
}
//generate random value for value
int generate_randomv(int n){
     while(1){
    int r=(rand() % n)+1;
     srand(time(NULL));
    return r;
    }
    
}
void sudoku(){
    printf("\t\t\t\t  _____   _   _   ____     ____    _   __  _   _ \n");
    printf("\t\t\t\t / ____| | | | | |  _ \\   / __ \\  | | / / | | | |\n");
    printf("\t\t\t\t| (___   | | | | | | | | | |  | | | |/ /  | | | |\n");
    printf("\t\t\t\t\\____ \\  | | | | | | | | | |  | | | < |   | | | |\n");
    printf("\t\t\t\t ____) | | |_| | | |_| | | |__| | | |\\ \\  | |_| |\n");
    printf("\t\t\t\t|_____/  |_____| |____/   \\____/  |_| \\_\\ |_____|\n");

}
//Functio  to check and verify the given constraints for a sudoku
int issafe(int **arr, int row, int col, int val, int n) {
	    for (int i = 0; i < n; i++) {
	        if (arr[row][i] == val || arr[i][col] == val)
	            return 0;
	    }
	
	    int x = sqrt(n);
	    if (x * x != n) {
	        if (n % 2 == 0) {
	            x = n / 2;
	            for (int i = 0; i < 2; i++) {
	                for (int j = 0; j < x; j++) {
	                    if (arr[(row - row % 2) + i][(col - col % x) + j] == val) {
	                        return 0;
	                    }
	                }
	            }
	        }
	    } else {
	        for (int i = 0; i < n; i++) {
	            if (arr[(x * (row / x)) + (i / x)][(x * (col / x)) + (i % x)] == val)
	                return 0;
	        }
	    }
	    return 1;
	}
	int k=0,question[100][100];
	//Function for printing the sudoku
void print(int **arr, int n) {
    if(k==0){
        printf("the question geneterated is :\n");
        k++;
    }
    else
	    printf("Solution no: %d\n", k++);
	    for (int i = 0; i < n; i++) {
	        printf("\t");
	        for (int j = 0; j < n; j++)
	            printf("%d ", question[i][j]);
	        printf("\t\t\t");
	        for (int j = 0; j < n; j++)
	            printf("%d ", arr[i][j]);
	        printf("\n");
	    }
	}
int count,abc=0;

int generate(int **arr,int n){
     int rows,cols,val;
        rows=generate_randomr(n);
        cols=generate_randomc(n);
        if(arr[rows-1][cols-1]==0){
        val=generate_randomv(n);
        }
        else
        return 0;
    if(issafe(arr,rows-1,cols-1,val,n)){
    question[rows-1][cols-1]=arr[rows-1][cols-1]=val;
    count--;
    }
    }
//generates the suduko 
int generate_suduko(int **arr,int n){
    if(n==6){
    count=8;
    }else if(n==9){
        count=16;
    }
    else if(n==8){
        count =12;
    }
    else
    count=8;
    while(count){
    generate(arr,n);
}
print(arr,n);
}
//solves the sudoku 
int sudoku_solver(int **arr, int n) {
	    for (int i = 0; i < n; i++) {
	        for (int j = 0; j < n; j++) {
	            if (arr[i][j] == 0) {
	                for (int val = 1; val <= n; val++) {
	                    if (issafe(arr, i, j, val, n)) {
	                        arr[i][j] = val;
	                        if (sudoku_solver(arr, n)) {
	                            if (i == (n - 1) && j == (n - 1)) {
	                                print(arr, n);
	                                arr[i][j] = 0;// backtracking for multiple solutions
	                            } else
	                                return 1;
	                        } else
	                            arr[i][j] = 0; // backtracking for solution
	                    }
	                }
	                return 0;
	            }
	        }
	        
	    }
	    return 1;
	}
int main()
{       int n,x,var;
        FILE *file;
        sudoku();
        printf("enter the order of suduko :");
        scanf("%d",&n);
         int **arr = (int **)malloc(n * sizeof(int *));
	    for (int i = 0; i < n; i++) {
	       arr[i] = (int *)malloc(n * sizeof(int));
	    }
	    repeat:
	    printf("if you want a to generate a new suduko 0 \n");
	    printf("if you want to solve the suduko given from file enter 1");
	    scanf("%d",&x);
	    if(x==0){
        generate_suduko(arr,n);
        printf("\a");
        printf("if you want ans for the above question give n value");
        scanf("%d",&n);
	    }
	    else if(x==1){
	   //taking input from file
	   switch(n){
	    	case 6:file=fopen("sudokuinput6.txt","r");
	    	break;
	    	case 8:file=fopen("sudokuinput8.txt","r");
	    	break;
	    	case 9:file=fopen("sudokuinput9.txt","r");
		}
	   for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file,"%d",&var);
            question[i][j]=arr[i][j]=var;
        }
        }
        print(arr,n);
	    }
	    else {
	        printf("invalid choice");
	        system("cls");
	        goto repeat;
	    }
    if (sudoku_solver(arr, n)) {
	        // Solution found
	    } 
	    else {
	        if (k-1== 0){
	            printf("No solution exists.\n");
	            
	        }
	        else
	            printf("Only %d solutions exist.\n", k-1);
	    }
    printf("\a");
    //printf("%d",generate_random(n));
    return 0;
}
