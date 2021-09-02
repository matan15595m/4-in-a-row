#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


// Matan Ohayon
//311435614

//Matan Sofer	
//208491811

							//4 IN A ROW 

					  /*Instruction for the game:

'Four in a row' It is the goal of the game to connect four of your tokens in a line.
All directions(vertical, horizontal, diagonal) are allowed each player play his turn .*/

int inputRows();
int inputColumns();
void buildboard(int*** board, int rows, int cols);
void free1(int** board, int rows);
void run(int** board, int rows, int cols);
void print(int** board, int rows, int cols);
int player(int** board, int rows, int cols, int val);
int input(int** board, int rows, int cols);
int topPlace(int** board, int rows, int r, int c);  ///  ----> the recursive function
int isValid(int rows, int cols, int r, int c);
int WinStat(int** board, int rows, int cols, int r, int c);


int main()
{
	int rows = inputRows(); //to scan rows
	int cols = inputColumns();//to scan cols
	int** board = NULL;//sending NULL pointer
	buildboard(&board, rows, cols);    //function for allocate memory
	run(board, rows, cols);
	free1(board, rows);
	return 0;
}


int inputRows()
{
	int rows;
	printf("Enter rows: ");
	scanf("%d", &rows);
	while (rows < 1) //check for valid value
	{
		printf("Invalid, must be positive number, Enter rows: ");
		scanf("%d", &rows);
	}
	return rows;
}

int inputColumns()
{
	int cols;
	printf("Enter colums: ");
	scanf("%d", &cols);
	while (cols < 1)//check for valid value
	{
		printf("Invalid, must be positive number, Enter columns: ");
		scanf("%d", &cols);
	}
	return cols;
}


//this function allocate memory by the size of cols and rows
void buildboard(int*** board, int rows, int cols)
{
	(*board) = (int**)malloc(sizeof(int*) * rows);

	if (*board == NULL)
	{
		printf("Allocate Error");
		return 0;
	}



	for (int i = 0; i < rows; i++)
	{
		(*board)[i] = (int*)malloc(sizeof(int) * cols);

		if ((*board)[i] == NULL)
		{
			printf("Allocate error");
			return 0;
		}

		for (int j = 0; j < cols; j++)
		{
			(*board)[i][j] = 0;       //every index will be equal to zero (for the start)
		}

	}
}

//this function free all memory by order
void free1(int** board, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(board[i]);
	}
	free(board);
}

//this function check if moves are avilable and the print final result 
void run(int** board, int rows, int cols)
{
	print(board, rows, cols);
	int move = 0;
	int loop = 1;

	while (loop) //loop run until win or draw announcment
	{
		if (move < rows * cols) //size of the board
		{

			printf("First Player Move:\n");
			if (player(board, rows, cols, 1) == 1)  //  -->calling player function
			{
				printf("\nFirst Player Win.\n");
				break;
			}

			move++;

			if (move < rows * cols)
			{
				printf("Second Player Move:\n");
				if (player(board, rows, cols, 2) == 1)     //  -->calling player function
				{
					printf("\nSecond Player Win.\n");
					break;
				}
				move++;
			}
			else
			{
				printf("\nDraw.\n");
				break;
			}
		}

		else
		{
			printf("\nDraw.\n");
			break;
		}

	}
}

//this function print the board for every play

void print(int** board, int rows, int cols)
{
	for (int r = rows - 1; r >= 0; r--)
	{
		for (int c = 0; c < cols; c++)
		{
			printf("+---");
		}
		printf("+\n|");
		for (int c = 0; c < cols; c++)
		{
			if (board[r][c] == 0)
				printf("   |");
			else
				printf(" %d |", board[r][c]);
		}
		printf("\n");
	}
	for (int c = 0; c < cols; c++)
	{
		printf("+---");
	}
	printf("+\n");
	for (int c = 0; c < cols; c++)
	{
		printf("  %d ", c + 1);
	}
	printf("\n");
}

//this function manage every player play by ( if input avilable , if he won or not (by return from WinStat function) ,print the board ) 
int player(int** board, int rows, int cols, int val)
{

	int c = input(board, rows, cols) - 1;
	int r = topPlace(board, rows, 0, c);
	board[r][c] = val;
	print(board, rows, cols);
	return WinStat(board, rows, cols, r, c);

}


//scan which col the player wanna choose

int input(int** board, int rows, int cols)
{
	int c;
	int loop = 1;
	while (loop)
	{
		printf("Enter Column Number: ");
		scanf("%d", &c);
		//find if the column player chose is valid
		if (c < 1 || cols < c)
			printf("Column out of range.\n");

		else if (board[rows - 1][c - 1] != 0)
			printf("Column already full, select another column.\n");

		else
			return c;
	}

}

//this is the recursive function to find the "empty place" in the column player chose                                                           
int topPlace(int** board, int rows, int r, int c)
{

	if (r >= rows)
		return -1;

	if (board[r][c] == 0)
		return r;

	return
		topPlace(board, rows, r + 1, c);
}

//check the availability of the index
int isValid(int rows, int cols, int r, int c)
{
	if (0 <= r && r < rows && 0 <= c && c < cols)
		return 1;

	else
		return 0;

}


int WinStat(int** board, int rows, int cols, int r, int c)
{
	int v = board[r][c];  //get the index value on board


	//Check every possible situation which each player has won or not  (4 in a=( row,column ,diagonal)
	if (0 <= r - 3 && r < rows)
	{
		if (board[r - 1][c] == v && board[r - 2][c] == v && board[r - 3][c] == v)
		{
			return 1;
		}
	}
	for (int j = 3; j >= 0; j--)
	{
		if (0 <= c - j && c - j + 3 < cols)
		{
			if (board[r][c - j] == v && board[r][c - j + 1] == v && board[r][c - j + 2] == v && board[r][c - j + 3] == v)
			{
				return 1;
			}
		}
	}
	for (int j = 0; j <= 3; j++)
	{

		if (isValid(rows, cols, r + j - 3, c + j - 3) && isValid(rows, cols, r + j - 2, c + j - 2) && isValid(rows, cols, r + j - 1, c + j - 1) && isValid(rows, cols, r + j - 0, c + j - 0))
		{
			if (board[r + j - 3][c + j - 3] == v && board[r + j - 2][c + j - 2] == v && board[r + j - 1][c + j - 1] == v && board[r + j - 0][c + j - 0] == v)
				return 1;
		}
	}
	for (int j = 0; j <= 3; j++)
	{

		if (isValid(rows, cols, r + j - 3, c - j + 3) && isValid(rows, cols, r + j - 2, c - j + 2) && isValid(rows, cols, r + j - 1, c - j + 1) && isValid(rows, cols, r + j - 0, c - j + 0))
		{

			if (board[r + j - 3][c + 3 - j] == v && board[r + j - 2][c + 2 - j] == v && board[r + j - 1][c + 1 - j] == v && board[r + j - 0][c + 0 - j] == v)
				return 1;
		}
	}
	return 0;
}