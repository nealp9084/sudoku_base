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

void Sudoku::read_puzzle_from_file(FILE* f)
{
  this->parse_puzzle(f);
  this->validate();
}

void Sudoku::read_puzzle_from_memory(int cur_board[9][9])
{
  for (int y = 0; y < 9; y++)
  {
    memcpy(this->board[y], cur_board[y], sizeof(cur_board[y]));
  }

  this->validate();
}

void Sudoku::print(std::ostream& out)
{
  this->dump(this->board, out);
}

void Sudoku::dump(int cur_board[9][9], std::ostream& out)
{
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      if (x != 0)
      {
        out << ' ';
      }

      int a = cur_board[y][x];

      if (a == -1)
      {
        out << '?';
      }
      else
      {
        out << a;
      }
    }
    out << std::endl;
  }
}

bool Sudoku::find_uncolored(int cur_board[9][9], int cur_x, int cur_y, int& x_out, int& y_out)
{
  for (int y = cur_y; y < 9; y++, cur_x = 0)
  {
    for (int x = cur_x; x < 9; x++)
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

bool Sudoku::color_node(int cur_board[9][9], int cur_x, int cur_y)
{
  int uncolored_x, uncolored_y;

  //check if we can keep coloring nodes, or if we need to stop and assess the generated board
  if (find_uncolored(cur_board, cur_x, cur_y, uncolored_x, uncolored_y))
  {
    for (int i = 1; i <= 9; i++)
    {
      if (Validator::is_good_color(cur_board, uncolored_x, uncolored_y, i))
      {
        //clone the existing game board
        int new_board[9][9] = {};

        for (int y = 0; y < 9; y++)
        {
          memcpy(new_board[y], cur_board[y], sizeof(cur_board[y]));
        }

        new_board[uncolored_y][uncolored_x] = i;

        //if the coloring was successful, then return the colored graph indicate success
        if (color_node(new_board, uncolored_x, uncolored_y))
        {
          for (int y = 0; y < 9; y++)
          {
            memcpy(cur_board[y], new_board[y], sizeof(new_board[y]));
          }

          return true;
        }
      }
    }
  }
  else
  {
    //the board is completely colored, so we can't color any more nodes, but is it a valid coloring?
    return Validator::is_good_board(cur_board);
  }
}

bool Sudoku::solve_colorability_style()
{
  return color_node(this->board);
}

Sudoku::~Sudoku()
{
  
}
