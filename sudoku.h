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

  /**
   * @brief Read in the puzzle from a given FILE* (this defaults to standard input) and store it in
   *        memory.
   *
   * @param f The file from which we should read the n*n Sudoku board, with integers [1-n] as the
   *          known values, and '?' for unknown values. Defaults to std::cin.
   **/
  void read_puzzle_from_file(std::istream& f = std::cin);

  /**
   * @brief Read in the puzzle from a n*n Sudoku board somewhere in memory and store it in another
   *        location in memory.
   *
   * @param cur_board A n*n Sudoku board, with integers [1-n] as the known values, and -1 for
   *                  unknown values.
   **/
  void read_puzzle_from_memory(int cur_board[9][9]);

  /**
   * @brief Print the current state of the board to some output stream
   *
   * @param out An output stream. Defaults to std::cout.
   **/
  void print(std::ostream& out = std::cout);

  /**
   * @brief Attempt to solve the puzzle using the graph 9-coloring technique. If the puzzle was
   *        successfully solved, then the solution will be saved to memory (overwriting the existing
   *        grid) and the method will return true. If the puzzle could not be solved for whatever
   *        reason, then this method will return false.
   *
   * @return bool Whether we were able to solve the puzzle.
   **/
  bool solve_colorability_style();

private:
  /**
   * @brief Helper method for parsing a puzzle from a file
   *
   * @param f The file from which we are reading.
   **/
  void parse_puzzle(std::istream& f);
  /**
   * @brief Helper method for checking whether the given puzzle is solvable
   **/
  void validate();

  /**
   * @brief Helper method for printing a game board to an output stream.
   *
   * @param cur_board A Sudoku board, either an incomplete or complete puzzle.
   * @param out An output stream.
   **/
  static void dump(int cur_board[9][9], std::ostream& out);

  /**
   * @brief Helper method for finding the next unmarked (i.e., undetermined) Sudoku grid.
   *
   * @param cur_board The Sudoku game board.
   * @param cur_x The last x position considered on the game board.
   * @param cur_y The last y position considered on the game board.
   * @param x_out The x position of the next uncolored cell.
   * @param y_out The y position of the next uncolored cell.
   * @return bool Whether we were able to find an uncolored node.
   **/
  static bool find_uncolored(int cur_board[9][9], int cur_x, int cur_y, int& x_out, int& y_out);
  /**
   * @brief Helper method for solving an instance of a Sudoku puzzle using the graph 9-colorability
   *        solution method. If a 9-coloring is found, the method will return true and overwrite
   *        cur_board with the solution (which corresponds with the graph coloring).
   *
   * @param cur_board The Sudoku game board.
   * @param cur_x The last x position considered on the game board. Defaults to 0.
   * @param cur_y The last y position considered on the game board. Defaults to 0.
   * @return bool Whether we were able to find a 9-coloring for the Sudoku board.
   **/
  static bool color_node(int cur_board[9][9], int cur_x = 0, int cur_y = 0);

  /**
   * @brief The Sudoku board, which we are saving in memory.
   **/
  int board[9][9];
};

#endif // SUDOKU_H
