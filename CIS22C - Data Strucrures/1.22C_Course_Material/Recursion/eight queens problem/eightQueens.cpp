/**~*~*
  8 Queens Problem - The recursive solution
*~**/

#include <iostream>
#include <iomanip>

using namespace std;

const int SIZE = 30;

int getValidSize(int low, int high, string msg);
bool threatened(int board[][SIZE], int row, int col, int boardSize);
int placeQueen ( int board[][SIZE], int boardSize, int row);
void printBoard (int board[][SIZE], int boardSize);

int main ( void )
{
    int board[SIZE][SIZE] = {{0}};
	int boardSize;

	cout << "\n\t **~*~** Eight Queens problem **~*~** \n\n"
	       "\t Place a queen in each row of the board\n"
	       "\t so that no two queens threaten each other. \n";

	boardSize = getValidSize (4, SIZE, "the board size: ");
	placeQueen (board, boardSize, 0);
	printBoard (board, boardSize);

	cout << "\n\t **~*~** THE END **~*~** \n\n";
	return 0;
}

/**~*~*
   This function prompts the user to enter an integer number within a given range
   If the input is not valid (not a number or if it is outside of the range) it
   prompts the user to enter a new number, until the input is valid.
*~**/
int getValidSize(int low, int high, string msg)
{
    int num;
    bool success;

    do
    {
        cout << "\nPlease enter " << msg << " (" << low << " to " << high << "): ";
        success = cin >> num;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success || num < low || num > high);

    return num;
}

/**~*~*
  	Position queens on a game board so that no queen
	can capture any other queen.
*~**/
int placeQueen ( int board[][SIZE], int boardSize, int row)
{
	int  col;
    if (row >= boardSize)
        return 1; // last row: stop

	for (col = 0; col < boardSize; col++)
	{
        if (!threatened(board, row, col, boardSize))
        {
            board[row][col] = 1;
            if(placeQueen(board, boardSize, row + 1))
                return 1;
            else
                board[row][col] = 0; // remove queen
        }
    }
	return 0;
}

/**~*~*
 	Checks rows, columns, and diagonals for threatening queens
	- board contains current positions for queens.
    - row and col are position for new queen
    - boardSize is number of rows and cols in board.
	- returns true if guarded; false if not guarded
*~**/
bool threatened(int board[][SIZE], int row, int col, int boardSize)
{
	int r, c;

	// Check current col for a queen
	c = col;
	for (r = 0; r < row; r++)
	    if (board[r][c] == 1)
	       return true;

	// Check diagonal right-up
	for (r = row - 1, c = col + 1; r > -1 && c < boardSize; r--, c++)
	    if (board[r][c] == 1)
	       return true;

	// Check diagonal left-up
	for (r = row - 1, c = col - 1; r > -1 && c > -1; r--, c--)
	    if (board[r][c] == 1)
	       return true;

	return false;
}

/**~*~*
	Print positions of chess queens on a game board
	- board[][] contains positions of queen.
    - boardSize is the number of rows and columns
*~**/
void printBoard (int board[][SIZE], int boardSize)
{
	int col, stCol;

	if (boardSize > 16)
	{
        cout << "Only boards <= 16 are printed!\n";
        return;
	}

	// Print Column numbers
	cout << "\n    ";
	for(int i = 0; i < boardSize; i++)
        cout << setw(3) << i + 1 << "|";
    cout << endl;

    // print divider
	cout << "    ";
	for(int i = 0; i < boardSize; i++)
        cout << "--- ";
    cout << endl;

    // print board
	for (int row = 0; row < boardSize; row++)
    {
	    cout << setw(3) << row + 1 << "|";
	    for (col = 0; col < boardSize; col++)
	    {
	        if (board[row][col])
	            cout << " Q |";
            else
	            cout << "   |";
	    }
        cout << endl;
        cout << "    ";
	    for(int i = 0; i < boardSize; i++)
        {
            cout << "--- ";
        }
        cout << endl;
    }

	return;
}

/**~*~*

         **~*~** Eight Queens problem **~*~**

         Place a queen in each row of the board
         so that no two queens threaten each other.

Please enter the board size:  (4 to 30): 5

      1|  2|  3|  4|  5|
    --- --- --- --- ---
  1| Q |   |   |   |   |
    --- --- --- --- ---
  2|   |   | Q |   |   |
    --- --- --- --- ---
  3|   |   |   |   | Q |
    --- --- --- --- ---
  4|   | Q |   |   |   |
    --- --- --- --- ---
  5|   |   |   | Q |   |
    --- --- --- --- ---

         **~*~** THE END **~*~**
*~**/

