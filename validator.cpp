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

#include "validator.h"

//TODO: this is a bit hacky, and won't scale well (n >= 64)
bool Validator::is_good_row(int cur_board[9][9], int y)
{
  int mask = 0;
  
  for (int x = 0; x < 9; x++)
  {
    int a = cur_board[y][x];
    
    //reject rows that are incomplete or have duplicates
    if ((a == -1) || ((mask & (1 << (a - 1))) != 0))
    {
      return false;
    }
    else
    {
      mask |= (1 << (a - 1));
    }
  }
  
  return (mask == (1 << 9) - 1);
}

//TODO: this is a bit hacky, and won't scale well (n >= 64)
bool Validator::is_good_column(int cur_board[9][9], int x)
{
  int mask = 0;
  
  for (int y = 0; y < 9; y++)
  {
    int a = cur_board[y][x];
    
    //reject cols that are incomplete or have duplicates
    if ((a == -1) || ((mask & (1 << (a - 1))) != 0))
    {
      return false;
    }
    else
    {
      mask |= (1 << (a - 1));
    }
  }
  
  return (mask == (1 << 9) - 1);
}

//TODO: this is a bit hacky, and won't scale well (n >= 64)
bool Validator::is_good_block(int cur_board[9][9], int x, int y)
{
  int mask = 0;
  
  for (int y_off = 0; y_off < 3; y_off++)
  {
    for (int x_off = 0; x_off < 3; x_off++)
    {
      int a = cur_board[y + y_off][x + x_off];
      
      //reject blocks that are incomplete or have duplicates
      if ((a == -1) || ((mask & (1 << (a - 1))) != 0))
      {
        return false;
      }
      else
      {
        mask |= (1 << (a - 1));
      }
    }
  }
  
  return (mask == (1 << 9) - 1);
}

//TODO: remove outputs to stderr
bool Validator::is_good_board(int cur_board[9][9])
{
  for (int y = 0; y < 9; y++)
  {
    if (!is_good_row(cur_board, y))
    {
      return false;
    }
  }
  
  for (int x = 0; x < 9; x++)
  {
    if (!is_good_column(cur_board, x))
    {
      return false;
    }
  }
  
  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      if (!is_good_block(cur_board, x * 3, y * 3))
      {
        return false;
      }
    }
  }
  
  return true;
}

int Validator::partial_row(int cur_board[9][9], int y)
{
  int mask = 0;

  for (int x = 0; x < 9; x++)
  {
    int a = cur_board[y][x];

    //ignore incomplete elements
    if (a != -1)
    {
      mask |= (1 << (a - 1));
    }
  }

  return mask;
}

int Validator::partial_column(int cur_board[9][9], int x)
{
  int mask = 0;

  for (int y = 0; y< 9; y++)
  {
    int a = cur_board[y][x];

    //ignore incomplete elements
    if (a != -1)
    {
      mask |= (1 << (a - 1));
    }
  }

  return mask;
}

int Validator::partial_block(int cur_board[9][9], int x, int y)
{
  int mask = 0;

  for (int y_off = 0; y_off < 3; y_off++)
  {
    for (int x_off = 0; x_off < 3; x_off++)
    {
      int a = cur_board[y + y_off][x + x_off];

      //ignore incomplete elements
      if (a != -1)
      {
        mask |= (1 << (a - 1));
      }
    }
  }

  return mask;
}

bool Validator::is_good_color(int cur_board[9][9], int x, int y, int i)
{
  int bit = (1 << (i - 1));
  int row_mask = partial_row(cur_board, y),
    col_mask = partial_column(cur_board, x),
    block_mask = partial_block(cur_board, (x / 3) * 3, (y / 3) * 3);

  return (row_mask & bit) == 0 && (col_mask & bit) == 0 && (block_mask & bit) == 0;
}

//TODO: this is a bit hacky, and won't scale well (n >= 64)
bool Validator::is_good_partial_row(int cur_board[9][9], int y)
{
  int mask = 0;

  for (int x = 0; x < 9; x++)
  {
    int a = cur_board[y][x];

    //ignore incomplete elements
    if (a != -1)
    {
      //reject rows that have duplicates
      if ((mask & (1 << (a - 1))) != 0)
      {
        return false;
      }
      else
      {
        mask |= (1 << (a - 1));
      }
    }
  }

  return true;
}

//TODO: this is a bit hacky, and won't scale well (n >= 64)
bool Validator::is_good_partial_column(int cur_board[9][9], int x)
{
  int mask = 0;

  for (int y = 0; y < 9; y++)
  {
    int a = cur_board[y][x];

    //ignore incomplete elements
    if (a != -1)
    {
      //reject cols that have duplicates
      if ((mask & (1 << (a - 1))) != 0)
      {
        return false;
      }
      else
      {
        mask |= (1 << (a - 1));
      }
    }
  }

  return true;
}

//TODO: this is a bit hacky, and won't scale well (n >= 64)
bool Validator::is_good_partial_block(int cur_board[9][9], int x, int y)
{
  int mask = 0;

  for (int y_off = 0; y_off < 3; y_off++)
  {
    for (int x_off = 0; x_off < 3; x_off++)
    {
      int a = cur_board[y + y_off][x + x_off];

      //ignore incomplete elements
      if (a != -1)
      {
        //reject blocks that have duplicates
        if ((mask & (1 << (a - 1))) != 0)
        {
          return false;
        }
        else
        {
          mask |= (1 << (a - 1));
        }
      }
    }
  }

  return true;
}

bool Validator::is_good_partial_board(int cur_board[9][9])
{
  for (int y = 0; y < 9; y++)
  {
    if (!is_good_partial_row(cur_board, y))
    {
      return false;
    }
  }

  for (int x = 0; x < 9; x++)
  {
    if (!is_good_partial_column(cur_board, x))
    {
      return false;
    }
  }

  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      if (!is_good_partial_block(cur_board, x * 3, y * 3))
      {
        return false;
      }
    }
  }

  return true;
}
