#ifndef THEME_HPP
#define THEME_HPP

#include <SFML/Graphics/Color.hpp>
#include <utility>
#include <array>

class Theme
{
public:
  Theme(unsigned int current_theme = 1);
  void SetTheme(unsigned int current_theme);
  sf::Color GetBackgroundColor() const;
  sf::Color GetBoardColor() const;
  std::pair<sf::Color, sf::Color> GetScoreColor() const;
  std::pair<sf::Color, sf::Color> GetTileColor(int tile_value) const;
  float GetTileTextScale(int tile_value) const;

private:
  unsigned int current_;
};

#endif
