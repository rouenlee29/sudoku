#include <iostream>
#include <cstdio>
#include <string>
#include "sudoku.h"

using namespace std;

int main()
{

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
  cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
  {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
  {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board))
  {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // // write more tests
  string location = "E5";
  char number = '9';
  cout << "Putting '" << number << "' into " << location << " is ";
  if (!make_move(&location[0], number, board))
  {
    cout << "NOT ";
  }
  cout << "a valid move.\n";

  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
  {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  }
  else
  {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  int easy_moves = 0;
  if (solve_board(board, easy_moves))
  {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  cout << "Number of moves made in easy board: " << easy_moves << endl;

  load_board("medium.dat", board);
  int medium_moves = 0;
  if (solve_board(board, medium_moves))
  {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  cout << "Number of moves made in medium board: " << medium_moves << endl;

  // cout << "=================== Question 5 ===================\n\n";

  std::string filenames[3] = {"mystery1.dat", "mystery2.dat", "mystery3.dat"};

  for (int index = 0; index < 3; index++)
  {
    std::string file = filenames[index];
    int moves = 0;

    load_board(&file[0], board);
    cout << "Solving puzzle in " << file;

    if (solve_board(board, moves))
    {
      cout << " is successful, and requires " << moves << " moves." << endl;
    }
    else
    {
      cout << " failed after " << moves << " moves."
           << endl;
    }
    cout << "\n";
  }

  return 0;
}
