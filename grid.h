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

#ifndef GRID_H
#define GRID_H

#include <boost/multi_array.hpp>

class Grid
{
public:
  Grid(std::size_t n);
  Grid(Grid const& grid);
  Grid& operator =(Grid const& grid);
  virtual ~Grid();

  int get(std::size_t x, std::size_t y) const;
  void set(std::size_t x, std::size_t y, int i);

  std::size_t n() const;

private:
  boost::multi_array<int, 2> matrix;
  std::size_t dim;
};

#endif // GRID_H
