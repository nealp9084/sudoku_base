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
#include "validator.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <stdexcept>
#include <iostream>

Sudoku::Sudoku() : board {}
{
}

void Sudoku::parse_puzzle(FILE* f)
{
  QTextStream file(f);

  //read 9 lines
  for (int y = 0; y < 9; y++)
  {
    QString line = file.readLine();
    QStringList tokens = line.split(' ');

    //each line must have 9 tokens: [1-9] or ?
    if (tokens.size() == 9)
    {
      for (int x = 0; x < 9; x++)
      {
        bool ok = false;
        int value = tokens[x].toInt(&ok);

        if (ok)
        {
          //integer tokens must be between 1 and 9
          if (value < 1 || value > 9)
            throw std::runtime_error("Invalid value in board");
          else
            this->board[y][x] = value;
        }
        else if (tokens[x] == "?")
        {
          this->board[y][x] = -1;
        }
        else
        {
          throw std::runtime_error("Invalid character in board");
        }
      }
    }
    else
    {
      throw std::runtime_error("Invalid board");
    }
  }
}

void Sudoku::validate()
{
  if (!Validator::is_good_partial_board(this->board))
  {
    throw std::runtime_error("This board is unsolvable!");
  }
}

void Sudoku::read_puzzle(FILE* f)
{
  this->parse_puzzle(f);
  this->validate();
}

void Sudoku::print()
{
  std::cout << "Here's what I've got." << std::endl;
  this->dump(this->board);
}

void Sudoku::dump(int cur_board[9][9])
{
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      if (x != 0)
      {
        std::cout << ' ';
      }

      std::cout << cur_board[y][x];
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

bool Sudoku::find_uncolored(int cur_board[9][9], int cur_x, int cur_y, int& x_out, int& y_out)
{
  for (int y = cur_y; y < 9; y++)
  {
    for (int x = (y == cur_y ? cur_x : 0); x < 9; x++)
    {
      if (cur_board[y][x] == -1)
      {
        x_out = x;
        y_out = y;
        return true;
      }
    }
  }

  return false;
}

void Sudoku::color_node(int cur_board[9][9], int cur_x, int cur_y)
{
  int pivot_x, pivot_y;

  //check if we can keep branching off, or if we need to stop and assess the generated board
  if (find_uncolored(cur_board, cur_x, cur_y, pivot_x, pivot_y))
  {
    for (int i = 1; i <= 9; i++)
    {
      if (Validator::is_good_pivot(cur_board, pivot_x, pivot_y, i))
      {
        int new_board[9][9] = {};
        for (int y = 0; y < 9; y++)
        {
          memcpy(new_board[y], cur_board[y], sizeof(cur_board[y]));
        }

        new_board[pivot_y][pivot_x] = i;
        color_node(new_board, pivot_x, pivot_y);
      }
    }
  }
  else
  {
    //found a solution
    if (Validator::is_good_board(cur_board))
    {
      std::cout << "We've got a winner!" << std::endl;
      dump(cur_board);
      exit(0);
    }
    else
    {
    }
    
    return;
  }
}

void Sudoku::solve_colorability_style()
{
  color_node(this->board);
}

Sudoku::~Sudoku()
{
  
}
