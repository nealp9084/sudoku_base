/*
 *  Sudoku Base - a library for solving Sudoku puzzles
 *  Copyright (C) 2013  Neal Patel <nealp9084@gmail.com>
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sudoku.h"
#include <iostream>

int main(int argc, char* argv[])
{
  Sudoku puzzle;
  puzzle.read_puzzle_from_file();

  std::cout << "Here's the current state of the board." << std::endl;
  puzzle.print();

  std::cout << "Attempting to solve the puzzle..." << std::endl;

  if (puzzle.solve_colorability_style())
  {
    std::cout << "A solution was found!" << std::endl;
    puzzle.print();
  }
  else
  {
    std::cout << "No solutions exist." << std::endl;
  }

  return 0;
}
