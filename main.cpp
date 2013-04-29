#include "sudoku.h"

int main(int argc, char* argv[])
{
  Sudoku puzzle;
  puzzle.read_puzzle();
  puzzle.print();
  puzzle.solve_colorability_style();
  return 0;
}
