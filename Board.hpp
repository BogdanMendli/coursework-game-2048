#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Random.hpp"

class Board
{
public:
  explicit Board(unsigned int size = 0, bool recursive_merge = false);
  void Reset(unsigned int size = 0, bool recursive_merge = false);
  unsigned int Size() const;
  unsigned int Score() const;
  int Tile(unsigned int row, unsigned int column) const;
  bool Locked() const;
  int GreatestTile() const;
  bool Up();
  bool Down();
  bool Left();
  bool Right();

private:
  int & At(unsigned int row, unsigned int column);
  int At(unsigned int row, unsigned int column) const;
  void Rotate();
  bool Merge();
  bool Slide();
  void Pop();
  void Pop(int value);

  unsigned int size_;
  bool recursive_merge_;
  unsigned int score_;
  unsigned int empty_counter_;
  std::vector<int> data_;
  int greatest_tile_;
  Random rand_;
};

#endif
