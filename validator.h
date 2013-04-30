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

#ifndef VALIDATOR_H
#define VALIDATOR_H

class Validator
{
/*
 * A board is defined as "good" if every row has the digits 1-9 used exactly once, if every column
 * has the digits 1-9 used exactly once, and if every 3x3 block has the digits 1-9 used exactly
 * once. Basically, this function is just checking whether the given board is a solution to some
 * Sudoku puzzle.
 * 
 * This function can be used when solving a Sudoku puzzle with the brute force method, the graph
 * 9-colorability method, and many other solution methods.
 */
public:
  static bool is_good_board(int cur_board[9][9]);
private:
  //helpers for the above task
  static bool is_good_row(int cur_board[9][9], int y);
  static bool is_good_column(int cur_board[9][9], int x);
  static bool is_good_block(int cur_board[9][9], int x, int y);

/*
 * Check whether a specific node can be colored in a particular way. This validation will tell you
 * whether you can use a specific color, provided that it does not appear in the same row, in the
 * same column, or the same 3x3 block.
 * 
 * This function is used when solving a Sudoku puzzle with the graph 9-coloring method (as the
 * function's name implies).
 */
public:
  static bool is_good_color(int cur_board[9][9], int x, int y, int i);
private:
  //helpers for the above task (they just tell you which colors have been used)
  static int partial_row(int cur_board[9][9], int y);
  static int partial_column(int cur_board[9][9], int x);
  static int partial_block(int cur_board[9][9], int x, int y);

/*
 * A partially-completed board is defined as "good" if every row has the digits 1-9 used at most
 * once, if every column has the digits 1-9 used at most once, and if every 3x3 block has the digits
 * 1-9 used at most once. Basically, this function is just checking whether the given board is a
 * solvable Sudoku puzzle.
 * 
 * This function can be used when solving a Sudoku puzzle with the graph 9-colorability method, and
 * many other solution methods.
 */
public:
  static bool is_good_partial_board(int cur_board[9][9]);
private:
  //helpers for the above task
  static bool is_good_partial_row(int cur_board[9][9], int y);
  static bool is_good_partial_column(int cur_board[9][9], int x);
  static bool is_good_partial_block(int cur_board[9][9], int x, int y);
};

#endif // VALIDATOR_H
