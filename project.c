#include <stdlib.h>
#include <stdio.h>
#define COUNT 9
#define SHUFF 10 /*min no of times to shuffle*/
void g_swap_row(int from, int to);
void g_swap_colm(int from, int to);
void g_print();
int gen();
void gusr();

int sol();
int solSudo(int puzzle[][9]);
int findempty(int puzzle[][9], int row, int column );
int isValid(int number, int puzzle[][9], int row, int column);
int sudoHelp(int puzzle[][9], int row, int column);
void printSudoku(int puzzle[][9]);

static int soln[9][9], zr[9][9];
static int source[9][9] = {
	1, 2, 3, 6, 5, 4, 9, 8, 7,
	9, 8, 7, 1, 2, 3, 6, 5, 4,
	6, 5, 4, 9, 8, 7, 1, 2, 3,
	2, 3, 1, 5, 4, 6, 8, 7, 9, 
	8, 7, 9, 2, 3, 1, 5, 4, 6, 
	5, 4, 6, 8, 7, 9, 2, 3, 1,
	3, 1, 2, 4, 6, 5, 7, 9, 8,
	7, 9, 8, 3, 1, 2, 4, 6, 5,
	4, 6, 5, 7, 9, 8, 3, 1, 2
	};
int main() {
	int x;
	printf("Sudoku\n  1.Generate\n  2.Solve\n");
	scanf("%d", &x);
	if(x == 1)
		gen();
	else if(x == 2)
		sol();
	else {
		printf("Invalid Option\n");
		exit(0);
	}
}
static int hint;
int gen() {
	int i, j, z, swap, trio;
	printf("Select Difficulty:\n  1.Easy\n  2.Medium\n  3.Difficult\n");
	scanf("%d", &hint);
	if(hint == 1)
		hint = 75;/*inverse % Difficulty level*/
	else if(hint == 2)
		hint = 65;
	else if(hint == 3)
		hint = 50;
	else {
		printf("Invalid Option\n");
		exit(0);
	}
	for(i = 0; i < COUNT; i++) {
		for(j = 0; j < (SHUFF * (rand() % 10 + 2)); j++) {
			trio = (rand() % 3) * 3; /*generates 0, 3 or 6*/
			swap = rand() % 2; /*either 0 or 1*/
			switch(rand() % 6) { /*0,1,2,3,4,5*/
				case 0:
					g_swap_row((trio + 0), swap ? (trio + 1) : (trio + 2));
					break;
				case 1:
					g_swap_row((trio + 1), swap ? (trio + 2) : (trio + 0));
					break;
				case 2:
					g_swap_row((trio + 2), swap ? (trio + 0) : (trio + 1));
					break;
				case 3:
					g_swap_colm((trio + 0), swap ? (trio + 1) : (trio + 2));
					break;
				case 4:
					g_swap_colm((trio + 1), swap ? (trio + 2) : (trio + 0));
					break;
				case 5:
					g_swap_colm((trio + 2), swap ? (trio + 0) : (trio + 1));
					break;
			}
		}
	}
	g_print();
	return 0;
}
void g_swap_row(int from, int to) {/*from,to sets: {0,1,2},{3,4,5},{6,7,8}*/
	int i, temp;
	for(i = 0; i < 9; i++) {
		temp = source[from][i];
		source[from][i] = source[to][i];
		source[to][i] = temp;
	}
}

void g_swap_colm(int from, int to)
{
	int i, temp;
	for(i = 0; i < 9; i++){
		temp = source[i][from];
		source[i][from] = source[i][to];
		source[i][to] = temp;
	}
}
void g_print() { 
	int i,j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			soln[i][j] = source[i][j];
			if (2 == j || 5 == j) {
				source[i][j] = rand() % 100 > hint ? 0 : source[i][j];
				zr[i][j] = source[i][j];
				printf("%d | ", source[i][j]);
			}
			else if (8 == j) {
				source[i][j] = rand() % 100 > hint ? 0 : source[i][j];
				zr[i][j] = source[i][j];
				printf("%d\n", source[i][j]);
			}
			else {
				source[i][j] = rand() % 100 > hint ? 0 : source[i][j];
				zr[i][j] = source[i][j];
				printf("%d ", source[i][j]);
			}
		}
		if (2 == i || 5 == i) {
			printf("------+-------+------\n");
		}
	}
	printf("\nEnter coordinates and number\nEnter -1 for solution.\n");
	gusr();
}

void gusr() {
	int nxt, i, j, m1, m2;
	for(m1 = 0; m1 < 9; m1++) {
		for(m2 = 0; m2 < 9; m2++) {
			if (2 == m2 || 5 == m2) {
				if(zr[m1][m2] == 0) {
					printf( "\033[22;34m%d \033[0m", source[m1][m2]);
					printf("| ");
				}
				else
					printf("%d | ", source[m1][m2]);
			}
			else if (8 == m2) {
			if(zr[m1][m2] == 0) {
					printf( "\033[22;34m%d \033[0m", source[m1][m2]);
					printf("\n");
				}
				else
				printf("%d\n", source[m1][m2]);
			}
			else {
			if(zr[m1][m2] == 0) {
					printf( "\033[22;34m%d \033[0m", source[m1][m2]);
				}
				else
				printf("%d ", source[m1][m2]);
			}
		}
		if (2 == m1 || 5 == m1) {
			printf("------+-------+------\n");
				
		}
	}

	scanf("%d", &i);
	if(i == -1) {
		printf("\nSolution:\n");
		for(m1 = 0; m1 < 9; m1++) {
			for(m2 = 0; m2 < 9; m2++) {
				if (2 == m2 || 5 == m2) {
					printf("%d | ", soln[m1][m2]);
				}
				else if (8 == m2) {
					printf("%d\n", soln[m1][m2]);
				}
				else {
					printf("%d ", soln[m1][m2]);
				}
			}
			if (2 == m1 || 5 == m1) {
				printf("------+-------+------\n");				
			}
		}
		exit(0);
	}
	scanf("%d%d", &j, &nxt);
	printf("\n");
	if(zr[i][j] == 0)
		source[i][j] = nxt;
	gusr();
}

int sol() {
int puzzle[9][9], c, j, zero = 0;
	char* fileName;
	FILE *sudokuFile;
	int i = 0;
	char fileN[81];
	printf("Read from\n  1.File\t2.terminal\n");
	scanf("%d", &c);
	if (c == 1) {
		scanf("%s",fileN);
		fileName = fileN;
		sudokuFile = fopen(fileName, "r");
	}
	else {
		sudokuFile = stdin;
	}
	if (sudokuFile == NULL) {
		perror("Error Opening File!\n");
		return 1;
	}
	for (i = 0; i < 9; i++) {
		fscanf(sudokuFile, "%d %d %d %d %d %d %d %d %d", &puzzle[i][0], &puzzle[i][1], &puzzle[i][2], &puzzle[i][3], &puzzle[i][4], &puzzle[i][5], &puzzle[i][6], &puzzle[i][7], &puzzle[i][8]);
	}
	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++) {
			if(puzzle[i][j] == 0)
				zero++;
			if(puzzle[i][j] > 9 || puzzle[i][j] < 0) {
				printf("Invalid sudoku\n");
				return 0;
			}
		}
	printf("Original Puzzle:\n");
	printSudoku(puzzle);

	if (solSudo(puzzle)) {
		printf("Sudoku Solved:\n");
		printSudoku(puzzle);
	}
	else {
		printf("Invalid sudoku\n");
	}
	return 0;
}
int solSudo(int puzzle[][9]) {
	return sudoHelp(puzzle, 0, 0);
}

int sudoHelp(int puzzle[][9], int row, int column) {
	int nxtnum = 1;
	if (9 == row) {
		return 1;
	}

	if (puzzle[row][column]) {
		if (column == 8) {
			if (sudoHelp(puzzle, row + 1, 0))
				return 1;
		}
		else {
			if (sudoHelp(puzzle, row, column + 1))
				return 1;
		}
		return 0;
	}
	for (; nxtnum < 10; nxtnum++) {
		if(isValid(nxtnum, puzzle, row, column)) {
			puzzle[row][column] = nxtnum;
			if (column == 8) {
				if (sudoHelp(puzzle, row + 1, 0))
					return 1;
			}
			else {
				if (sudoHelp(puzzle, row, column + 1))
					return 1;
			}
			puzzle[row][column] = 0;
		}
	}
	return 0;
}

int isValid(int number, int puzzle[][9], int row, int column) {
	int i = 0;
	int modRow = 3 * (row / 3);
	int modCol = 3 * (column / 3);
	int row1 = (row + 2) % 3;
	int row2 = (row + 4) % 3;
	int col1 = (column + 2) % 3;
	int col2 = (column + 4) % 3;

	for (i = 0; i < 9; i++) {
		if (puzzle[i][column] == number)
			return 0;
		if (puzzle[row][i] == number)
			return 0;
	}
    
	if(puzzle[row1 + modRow][col1 + modCol] == number)
		return 0;
	if(puzzle[row2 + modRow][col1 + modCol] == number)
		return 0;
	if(puzzle[row1 + modRow][col2 + modCol] == number)
		return 0;
	if(puzzle[row2 + modRow][col2 + modCol] == number)
		return 0;
	return 1;
}

void printSudoku(int puzzle[][9]) {
	int i = 0, j = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (2 == j || 5 == j) {
				printf("%d | ", puzzle[i][j]);
			}
			else if (8 == j) {
				printf("%d\n", puzzle[i][j]);
			}
			else {
				printf("%d ", puzzle[i][j]);
			}
		}
		if (2 == i || 5 == i) {
			puts("------+-------+------");
		}
	}
}
