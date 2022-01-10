#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

void load_board(const char *filename, char board[9][9])
{

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
  {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer, 512);
  while (in && row < 9)
  {
    for (int n = 0; n < 9; n++)
    {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer, 512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row)
{
  if (!(row % 3))
  {
    cout << "  +===========+===========+===========+\n";
  }
  else
  {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char *data, int row)
{
  cout << (char)('A' + row) << " ";
  for (int i = 0; i < 9; i++)
  {
    cout << ((i % 3) ? ':' : '|') << " ";
    cout << ((data[i] == '.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9])
{
  cout << "    ";
  for (int r = 0; r < 9; r++)
  {
    cout << (char)('1' + r) << "   ";
  }
  cout << '\n';
  for (int r = 0; r < 9; r++)
  {
    print_frame(r);
    print_row(board[r], r);
  }
  print_frame(9);
}

/* add your functions here */
bool is_complete(const char board[9][9])
{
  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      if ((board[row][col] == '.') || (board[row][col] == '0'))
      {
        return false;
      }
    }
  }
  return true;
}

bool check_array(char ch, char an_array[9])
{
  // Checks whether a character exists in "an_array"
  for (int index = 0; index < 9; index++)
  {
    if (an_array[index] == ch)
    {
      return false;
    }
  }
  return true;
}

void get_column_from_matrix(int column_number, char column[9], char matrix[9][9])
{
  /* Gets values in "matrix" that have column number "column_number", and save them...
   in an array called "column" */
  for (int row = 0; row < 9; row++)
  {
    column[row] = matrix[row][column_number];
  }
};

void get_square_from_matrix(int row_number, int column_number, char board_square[9], char matrix[9][9])
{
  /* Get values in the 3x3 square where a position (with coordinates defined by...
  "row_number" and "column_number") is located
  */
  int square_row = (row_number / 3) * 3;
  int square_col = (column_number / 3) * 3;
  int index = 0;

  for (int matrix_row = square_row; matrix_row < (square_row + 3); matrix_row++)
  {
    for (int matrix_col = square_col; matrix_col < (square_col + 3); matrix_col++)
    {
      board_square[index] = matrix[matrix_row][matrix_col];
      index++;
    }
  }
}

bool make_move(const char *position, char digit, char board[9][9])
{
  char row = position[0];
  int row_num = static_cast<int>(row) - 65;
  int column_num = static_cast<int>(position[1]) - 49;
  char board_column[9];
  char board_square[9];

  // Check value of position is valid
  if (row < 'A' || row > 'I' || column_num < 0 || column_num > 8)
  {
    return false;
  }

  // Check whether digit is unique in row
  bool new_in_row = check_array(digit, board[row_num]);

  // Check whether digit is unique in column
  get_column_from_matrix(column_num, board_column, board);
  bool new_in_col = check_array(digit, board_column);

  // Check whether digit is unique in 3x3 square
  get_square_from_matrix(row_num, column_num, board_square, board);
  bool new_in_sqaure = check_array(digit, board_square);

  if (new_in_row && new_in_col && new_in_sqaure)
  {
    // Update board
    board[row_num][column_num] = digit;

    return true;
  }
  return false;
}

bool save_board(const char *filename, char board[9][9])
{
  ofstream out(filename);

  if (!out)
  {
    return false;
  }
  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      out.put(board[row][col]);
    }
    // After done with displaying all columns, jump to next line
    out.put('\n');
  }
  return true;
}

void get_empty_position(char board[9][9], char *empty_position)
{
  for (int row = 0; row < 9; row++)
  {
    empty_position[0] = static_cast<char>(row + 65);
    for (int col = 0; col < 9; col++)
    {
      if ((board[row][col] == '.') || (board[row][col] == '0'))
      {
        empty_position[1] = static_cast<char>(col + 49);

        // Break out of function after we have found empty position
        return;
      }
    }
  }
  // No empty position is found (for easy debugging)
  empty_position[0] = '\0';
  empty_position[1] = '\0';
}

bool solve_board(char board[9][9], int &moves)
{
  char empty_position[2];

  if (is_complete(board))
  {
    return true;
  }
  else
  {
    get_empty_position(board, empty_position);
  }

  for (char digit = '1'; digit <= '9'; digit++)
  {
    moves++;
    if (make_move(empty_position, digit, board))
    {
      if (solve_board(board, moves)) // solve for the next empty position
      {
        return true;
      };
      // Unable to find solution with current digit

      // Convert alphanumeric board coordinates to cartesian coordinates
      int row_num = static_cast<int>(empty_position[0]) - 65;
      int column_num = static_cast<int>(empty_position[1]) - 49;

      // Make board position empty, since we cannot find a solution with current digit
      board[row_num][column_num] = '.';

      // Try the next digit
    }
  }

  return false;
}