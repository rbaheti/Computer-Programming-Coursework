// Developer : Rashmi Baheti
// Project   : Game Takuzu
// Date      : 22 June 2016

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
using namespace std;

char unsolved4x4Matrix[4][4] = {
  {'_', '1', '_', '0'},
  { '_', '_', '0', '_' },
  { '_', '0', '_', '_' },
  { '1', '1', '_', '0' } };

char unsolved6x6Matrix[6][6] = {
  { '1', '0', '0', '_', '_', '0' },
  { '_', '1', '_', '0', '0', '1' },
  { '_', '1', '1', '_', '_', '_' },
  { '1', '0', '_', '1', '0', '_' },
  { '0', '_', '1', '_', '0', '1' },
  { '1', '1', '_', '_', '_', '_' } };

class Matrix {
public:
  Matrix(int numRow, int numCol) {
    this->numRow = numRow;
    this->numCol = numCol;
  }

  void ReadMatrixFromUser() {
    cout << endl;
    for (int i = 0; i < numRow; ++i) {
      matrix.push_back(vector<char>());
      for (int j = 0; j < numCol; ++j) {
        string input;
        bool isvalid = false;
        while (!isvalid) {
          cout << "Enter value (0, 1 or _) at row " << i << " col " << j << ": ";
          getline(cin, input);
          if (input.size() == 1 && (input.at(0) == '0' || input.at(0) == '1' || input.at(0) == '_')) {
            isvalid = true;
          }
          else {
            cout << "Invalid value entered. Only one of following characters allowed: 0, 1 or _" << endl;
          }
        }
        matrix[i].push_back(input.at(0));
      }
    }
  }

  void UseSample4x4Matrix() {
    for (int i = 0; i < 4; ++i) {
      matrix.push_back(vector<char>());
      for (int j = 0; j < 4; ++j) {
        matrix[i].push_back(unsolved4x4Matrix[i][j]);
      }
    }
  }

  void UseSample6x6Matrix() {
    for (int i = 0; i < 6; ++i) {
      matrix.push_back(vector<char>());
      for (int j = 0; j < 6; ++j) {
        matrix[i].push_back(unsolved6x6Matrix[i][j]);
      }
    }
  }

  void PrintMatrix() {
    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix[i].size(); ++j) {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
  }

  vector<vector<char>>& GetMatrix() {
    return matrix;
  }
private:
  int numRow;
  int numCol;
  vector<vector<char>> matrix;
};

class Takuzu {
public:
  bool RecursivelySolveTakuzu(vector<vector<char>>& matrix, int row, int col) {
    int next_row = row;
    int next_col = col;
    if (col < matrix[0].size() - 1) {
      ++next_col;

      if (matrix[row][col] == '_') {
        matrix[row][col] = '0';
        if (RecursivelySolveTakuzu(matrix, next_row, next_col)) return true;

        matrix[row][col] = '1';
        if (RecursivelySolveTakuzu(matrix, next_row, next_col)) return true;

        matrix[row][col] = '_';
        return false;
      }
      return RecursivelySolveTakuzu(matrix, next_row, next_col);
    }
    else if (row < matrix.size() - 1) {
      ++next_row;
      next_col = 0;

      if (matrix[row][col] == '_') {
        matrix[row][col] = '0';
        if (RecursivelySolveTakuzu(matrix, next_row, next_col)) return true;

        matrix[row][col] = '1';
        if (RecursivelySolveTakuzu(matrix, next_row, next_col)) return true;

        matrix[row][col] = '_';
        return false;
      }
      return RecursivelySolveTakuzu(matrix, next_row, next_col);
    }
    else if (matrix[row][col] == '_') {
      matrix[row][col] = '0';
      if (ValidateMatrix(matrix)) return true;

      matrix[row][col] = '1';
      if (ValidateMatrix(matrix)) return true;

      matrix[row][col] = '_';
      return false;
    }
    else {
      return ValidateMatrix(matrix);
    }
  }

private:
  bool ValidateMatrix(const vector<vector<char>>& matrix) {
    // Check that number of 1s and 0s are same in each row. Also check that each row is different.
    set<string> rows;
    for (int i = 0; i < matrix.size(); ++i) {
      int num_zero_count = 0, num_one_count = 0;
      string row;
      for (int j = 0; j < matrix[0].size(); ++j) {
        if (matrix[i][j] == '0') {
          ++num_zero_count;
        }
        else if (matrix[i][j] == '1') {
          ++num_one_count;
        }
        else {
          return false;
        }
        row += matrix[i][j];
      }
      if (num_zero_count != num_one_count) {
        return false;
      }
      if (rows.find(row) != rows.end()) {
        return false;
      }
      rows.insert(row);
    }

    // Check that number of 1s and 0s are same in each column. Also check that each column is different.
    set<string> columns;
    for (int j = 0; j < matrix[0].size(); ++j) {
      int num_zero_count = 0, num_one_count = 0;
      string column;
      for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i][j] == '0') {
          ++num_zero_count;
        }
        else if (matrix[i][j] == '1') {
          ++num_one_count;
        }
        else {
          return false;
        }
        column += matrix[i][j];
      }
      if (num_zero_count != num_one_count) {
        return false;
      }
      if (columns.find(column) != columns.end()) {
        return false;
      }
      columns.insert(column);
    }
    return true;
  }
};

int ReadIntegerInput() {
  string input;
  getline(cin, input);
  // atoi returns 0 when the conversion of string to integer is not possible due to invalid input.
  return atoi(input.c_str());
}

int main() {
  const string introduction =
    "Let's play the game of Takuzu!\n"
    "The objective is to fill a N x N matrix with 1s and 0s such that:\n"
    "1. There are same number of 0s and 1s in each row as well as each column.\n"
    "2. No 2 rows are same.\n"
    "3. No 2 columns are same.\n\n"
    "You will enter unsolved matrix consisting of 1s, 0s and underscores and the program will "
    "fill in 1s or 0s in place of underscores to turn your matrix into a solved Takuzu matrix.\n\n"
    "Basically, you will enter a matrix that looks like the one on the left below, and the program will print a matrix that looks like the one on the right below.\n"
    "\t\t_ 1 _ 0                0 1 1 0\n"
    "\t\t_ _ 0 _    -------\\    1 0 0 1\n"
    "\t\t_ 0 _ _    -------/    0 0 1 1\n"
    "\t\t1 1 _ 0                1 1 0 0\n\n";
  cout << introduction;
  int numRowsAndColumns = 0;
  do {
    cout << "Enter the number of rows and columns in the matrix (4 or 6): ";
    numRowsAndColumns = ReadIntegerInput();
    if (numRowsAndColumns != 4 && numRowsAndColumns != 6) {
      cout << "Invalid value. Please only enter 4 or 6." << endl;
    }
    else {
      break;
    }
  } while (true);

  cout << "\nPlease select one of the following options:\n";
  cout << "1. You enter unsolved matrix.\n";
  cout << "2. Program uses an unsolved matrix from its collection and solves it.\n";

  int menuChoice = 0;
  do {
    cout << "Enter your choice (1 or 2): ";
    menuChoice = ReadIntegerInput();
    if (menuChoice != 1 && menuChoice != 2) {
      cout << "Invalid value. Please only enter 1 or 2." << endl;
    }
    else {
      break;
    }
  } while (true);

  Matrix matrix(numRowsAndColumns, numRowsAndColumns);
  if (menuChoice == 1) {
    matrix.ReadMatrixFromUser();
  }
  else if (numRowsAndColumns == 4) {
    matrix.UseSample4x4Matrix();
  }
  else {
    matrix.UseSample6x6Matrix();
  }

  cout << endl << "This is the matrix the program will solve:" << endl;
  matrix.PrintMatrix();

  cout << "\nPress enter to see the solution. Note that this could take a while for a 6 x 6 matrix.";
  string ignoreLine;
  getline(cin, ignoreLine);
  
  Takuzu takuzu;
  if (takuzu.RecursivelySolveTakuzu(matrix.GetMatrix(), 0, 0)) {
    cout << endl << "This is the solution for the matrix you entered:" << endl;
    matrix.PrintMatrix();
  }
  else {
    cout << endl << "No solution exists for the matrix you entered:" << endl;
    matrix.PrintMatrix();
  }

  cin.get();
  cin.get();
  return 0;
}