#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics/Text.hpp>
#include "RoundedRectangleShape.hpp"

namespace sf
{
  class RenderWindow;
}

class Board;
class Theme;

class Graphics
{
public:
  explicit Graphics(sf::RenderWindow & window);
  void Display(const Board & board, const Theme & theme);
  void Resize(const Board & board, const Theme & theme);

private:
  void DrawBoard(const Board & board, const Theme & theme);
  void DrawScore(const Board & board, const Theme & theme);

  float tile_offset_;
  sf::RoundedRectangleShape board_background_;
  sf::RoundedRectangleShape tile_background_;
  sf::RoundedRectangleShape score_background_;
  sf::RenderWindow & window_;
  sf::Font font_;
  sf::Text tile_text_;
  sf::Text score_text_;
};

#endif
