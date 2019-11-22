#include "Board.hpp"
#include <algorithm>
#include <stdexcept>

Board::Board(unsigned int size, bool recursive_merge)
{
  Reset(size, recursive_merge);
}

void Board::Reset(unsigned int size, bool recursive_merge)
{
  size_ = size;
  recursive_merge_ = recursive_merge;
  empty_counter_ = size * size;
  score_ = 0;
  data_.resize(size * size);
  if (size > 0)
  {
    std::fill(data_.begin(), data_.end(), 0);
    Pop(1);
    if (size > 1)
    {
      Pop(1);
    }
    greatest_tile_ = 1;
  }
  else
  {
    greatest_tile_ = 0;
  }
}

unsigned int Board::Size() const
{
  return size_;
}

unsigned int Board::Score() const
{
  return score_;
}

int Board::Tile(unsigned int row, unsigned int column) const
{
  if (row < size_ && column < size_)
  {
    return At(row, column);
  }
  else
  {
    throw std::out_of_range("Error. Invalid tile index!");
  }
}

bool Board::Locked() const
{
  if (empty_counter_ != 0)
  {
    return false;
  }
  for (unsigned int row = 0; row < size_; ++row)
  {
    for (unsigned int column = 0; column < size_; ++column)
    {
      if (row > 0 && At(row, column) == At(row - 1, column))
      {
        return false;
      }
      if (column > 0 && At(row, column) == At(row, column - 1))
      {
        return false;
      }
    }
  }
  return true;
}

int Board::GreatestTile() const
{
  return greatest_tile_;
}

bool Board::Up()
{
  bool success = false;
  Rotate();
  success |= Merge();
  success |= Slide();
  Rotate();
  Rotate();
  Rotate();
  if (success)
  {
    Pop();
  }
  return success;
}

bool Board::Down()
{
  bool success = false;
  Rotate();
  Rotate();
  Rotate();
  success |= Merge();
  success |= Slide();
  Rotate();
  if (success)
  {
    Pop();
  }
  return success;
}

bool Board::Left()
{
  bool success = false;
  success |= Merge();
  success |= Slide();
  if (success)
  {
    Pop();
  }
  return success;
}

bool Board::Right()
{
  bool success = false;
  Rotate();
  Rotate();
  success |= Merge();
  success |= Slide();
  Rotate();
  Rotate();
  if (success)
  {
    Pop();
  }
  return success;
}

int & Board::At(unsigned int row, unsigned int column)
{
  return data_[row * size_ + column];
}

int Board::At(unsigned int row, unsigned int column) const
{
  return data_[row * size_ + column];
}

void Board::Rotate()
{
  int temp;
  for (unsigned int line = 0; line < size_ / 2; ++line)
  {
    for (unsigned int column = line; column < size_ - line - 1; ++column)
    {
      temp = At(line, column);
      At(line, column) = At(column, size_ - line - 1);
      At(column, size_ - line - 1) = At(size_ - line - 1, size_ - column - 1);
      At(size_ - line - 1, size_ - column - 1) = At(size_ - column - 1, line);
      At(size_ - column - 1, line) = temp;
    }
  }
}

bool Board::Merge()
{
  unsigned int last_column;
  bool success = false;
  for (unsigned int line = 0; line < size_; ++line)
  {
    last_column = 0;
    for (unsigned int column = 1; column < size_; ++column)
    {
      if (At(line, column) != 0)
      {
        if (At(line, column) == At(line, last_column))
        {
          At(line, column)++;
          At(line, last_column) = 0;
          score_ += (1 << At(line, column));
          empty_counter_++;
          greatest_tile_ = std::max(At(line, column), greatest_tile_);
          success = true;
        }
        else
        {
          last_column = column;
        }
      }
    }
  }
  if (success && recursive_merge_)
  {
    Merge();
  }
  return success;
}

bool Board::Slide()
{
  unsigned int empty_column;
  bool success = false;
  for (unsigned int line = 0; line < size_; ++line)
  {
    empty_column = 0;
    for (unsigned int column = 0; column < size_; ++column)
    {
      if (At(line, column) != 0)
      {
        if (empty_column != column)
        {
          At(line, empty_column) = At(line, column);
          At(line, column) = 0;
          success = true;
        }
        empty_column++;
      }
    }
  }
  return success;
}

void Board::Pop()
{
  if (rand_(0.1))
  {
    Pop(2);
  }
  else
  {
    Pop(1);
  }
}

void Board::Pop(int value)
{
  empty_counter_--;
  int rng = rand_(0, empty_counter_);
  for (unsigned int row = 0; row < size_; ++row)
  {
    for (unsigned int column = 0; column < size_; ++column)
    {
      if (At(row, column) == 0)
      {
        if (rng == 0)
        {
          At(row, column) = value;
          return;
        }
        else
        {
          rng--;
        }
      }
    }
  }
}
