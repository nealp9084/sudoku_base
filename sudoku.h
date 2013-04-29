/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef SUDOKU_H
#define SUDOKU_H

#include <cstdio>

class Sudoku
{
public:
  Sudoku();
  virtual ~Sudoku();

  //read in the puzzle from a given FILE* (this defaults to standard input)
  void read_puzzle(FILE* f = stdin);

  void print();

  void solve_colorability_style();

private:
  //helpers for parsing a puzzle from a file and checking whether it is solvable
  void parse_puzzle(FILE* f);
  void validate();

  //helper for printing out the board
  static void dump(int cur_board[9][9]);

  //helpers for solving an instance, colorability-style
  static bool find_uncolored(int cur_board[9][9], int cur_x, int cur_y, int& x_out, int& y_out);
  static void color_node(int cur_board[9][9], int cur_x = 0, int cur_y = 0);

  int board[9][9];
};

#endif // SUDOKU_H