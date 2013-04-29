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
private:
  //helpers for validation of a complete board
  static bool is_good_row(int cur_board[9][9], int y);
  static bool is_good_column(int cur_board[9][9], int x);
  static bool is_good_block(int cur_board[9][9], int x, int y);

public:
  //validation of a complete board
  static bool is_good_board(int cur_board[9][9]);

private:
  //helpers for repeated element check
  static int partial_row(int cur_board[9][9], int y);
  static int partial_column(int cur_board[9][9], int x);
  static int partial_block(int cur_board[9][9], int x, int y);

public:
  //repeated element check
  static bool is_good_pivot(int cur_board[9][9], int x, int y, int i);

private:
  //helpers for validation of a partially-completed board
  static bool is_good_partial_row(int cur_board[9][9], int y);
  static bool is_good_partial_column(int cur_board[9][9], int x);
  static bool is_good_partial_block(int cur_board[9][9], int x, int y);

public:
  //validation of a partially-completed board
  static bool is_good_partial_board(int cur_board[9][9]);
};

#endif // VALIDATOR_H
