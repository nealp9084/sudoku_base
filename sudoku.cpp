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

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

Sudoku::Sudoku() : grid(9)
{
}

void Sudoku::parse_puzzle(std::istream& f)
{
  //read n lines
  for (std::size_t y = 0; y < this->grid.n(); y++)
  {
    std::string line;
    std::getline(f, line);
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(" "));

    //each line must have n tokens
    if (tokens.size() == this->grid.n())
    {
      for (std::size_t x = 0; x < this->grid.n(); x++)
      {
        std::string const& token = tokens[x];

        try
        {
          int value = std::stoi(token);

          //integer tokens must be between 1 and n, and unknowns should be question marks
          if (value < 1 || value > (int)this->grid.n())
          {
            throw std::runtime_error("Invalid value in board");
          }
          else
          {
            this->grid.set(x, y, value);
          }
        }
        catch (std::invalid_argument &)
        {
          if (token == "?")
          {
            this->grid.set(x, y, -1);
          }
          else
          {
            throw std::runtime_error("Invalid character in board");
          }
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
  if (!Validator::is_good_partial_board(this->grid))
  {
    throw std::runtime_error("This board is unsolvable!");
  }
}

void Sudoku::read_puzzle_from_file(std::istream& f)
{
  this->parse_puzzle(f);
  this->validate();
}

void Sudoku::read_puzzle_from_memory(Grid& cur_grid)
{
  this->grid = cur_grid;
  this->validate();
}

void Sudoku::print(std::ostream& out)
{
  this->dump(this->grid, out);
}

void Sudoku::dump(Grid& cur_grid, std::ostream& out)
{
  for (std::size_t y = 0; y < cur_grid.n(); y++)
  {
    for (std::size_t x = 0; x < cur_grid.n(); x++)
    {
      if (x != 0)
      {
        out << ' ';
      }

      int a = cur_grid.get(x, y);

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

bool Sudoku::find_uncolored(Grid& cur_grid, std::size_t cur_x, std::size_t cur_y,
  std::size_t& x_out, std::size_t& y_out)
{
  //find the next uncolored node from where we left off, so we don't need to re-examine any elements
  for (std::size_t y = cur_y; y < cur_grid.n(); y++, cur_x = 0)
  {
    for (std::size_t x = cur_x; x < cur_grid.n(); x++)
    {
      if (cur_grid.get(x, y) == -1)
      {
        x_out = x;
        y_out = y;
        return true;
      }
    }
  }

  return false;
}

bool Sudoku::color_node(Grid& cur_grid, std::size_t cur_x, std::size_t cur_y)
{
  std::size_t uncolored_x, uncolored_y;

  //check if we can keep coloring nodes, or if we need to stop and assess the generated board
  if (find_uncolored(cur_grid, cur_x, cur_y, uncolored_x, uncolored_y))
  {
    std::uint_fast64_t colors = Validator::good_colors(cur_grid, uncolored_x, uncolored_y);

    for (int i = 1; i <= (int)cur_grid.n(); i++)
    {
      //can we use this color here?
      if ((colors & (1 << (i - 1))) != 0)
      {
        //clone the existing game board
        Grid new_grid(cur_grid);
        new_grid.set(uncolored_x, uncolored_y, i);

        //if the coloring was successful, then return the colored graph indicate success
        if (color_node(new_grid, uncolored_x, uncolored_y))
        {
          cur_grid = new_grid;
          return true;
        }
      }
    }

    //we couldn't find a coloring :(
    return false;
  }
  else
  {
    //the board is completely colored, so we can't color any more nodes, but is it a valid coloring?
    return Validator::is_good_board(cur_grid);
  }
}

bool Sudoku::solve_colorability_style()
{
  return color_node(this->grid);
}

Sudoku::~Sudoku()
{

}
