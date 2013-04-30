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

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <streambuf>

class Sudoku
{
public:
  Sudoku();
  virtual ~Sudoku();

  void read_puzzle_from_file(std::istream& f = std::cin);

  //read in the puzzle from a nxn grid somewhere in memory
  void read_puzzle_from_memory(int cur_board[9][9]);

  //print what we have read in
  void print(std::ostream& out = std::cout);

  //attempt to solve the puzzle
  bool solve_colorability_style();

private:
  //helpers for parsing a puzzle from a file and checking whether it is solvable
  void parse_puzzle(std::istream& f);
  void validate();

  //helper for printing out the board
  static void dump(int cur_board[9][9], std::ostream& out);

  //helpers for solving an instance, colorability-style
  static bool find_uncolored(int cur_board[9][9], int cur_x, int cur_y, int& x_out, int& y_out);
  static bool color_node(int cur_board[9][9], int cur_x = 0, int cur_y = 0);

  int board[9][9];
};

#endif // SUDOKU_H
