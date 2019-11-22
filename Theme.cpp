#include "Theme.hpp"

Theme::Theme(unsigned int current_theme)
{
  SetTheme(current_theme);
}

void Theme::SetTheme(unsigned int current_theme)
{
  if (current_theme <= 2)
  {
    current_ = current_theme;
  }
  else
  {
    current_ = 1;
  }
}

sf::Color Theme::GetBackgroundColor() const
{
  switch (current_)
  {
    case 2:
      return sf::Color(38, 50, 56);
    default:
      return sf::Color(250, 248, 239);
  }
}

sf::Color Theme::GetBoardColor() const
{
  switch (current_)
  {
    case 2:
      return sf::Color(17, 21, 30);
    default:
      return sf::Color(187, 173, 160);
  }
}

std::pair<sf::Color, sf::Color> Theme::GetScoreColor() const
{
  switch (current_)
  {
    case 2:
      return std::pair<sf::Color,
      sf::Color>{sf::Color(235, 235, 235),
                 sf::Color(0, 95, 95)};
    default:
      return std::pair<sf::Color,
      sf::Color>{sf::Color(249, 246, 242),
                 sf::Color(143, 122, 102)};
  }
}

std::pair<sf::Color, sf::Color> Theme::GetTileColor(int tile_value) const
{
  static const std::array<std::pair<sf::Color, sf::Color>, 13> dark_tiles_colors =
      {{{sf::Color(0, 0, 0, 0), sf::Color(49, 69, 73)},
        {sf::Color(195, 206, 227), sf::Color(80, 175, 164)},
        {sf::Color(195, 206, 227), sf::Color(0, 128, 128)},
        {sf::Color(195, 206, 227), sf::Color(44, 94, 90)},
        {sf::Color(38, 42, 56), sf::Color(235, 215, 129)},
        {sf::Color(38, 42, 56), sf::Color(223, 223, 53)},
        {sf::Color(38, 42, 56), sf::Color(238, 221, 18)},
        {sf::Color(38, 42, 56), sf::Color(247, 118, 105)},
        {sf::Color(38, 42, 56), sf::Color(255, 83, 112)},
        {sf::Color(38, 42, 56), sf::Color(188, 63, 63)},
        {sf::Color(38, 42, 56), sf::Color(147, 115, 165)},
        {sf::Color(38, 42, 56), sf::Color(199, 146, 234)},
        {sf::Color(38, 42, 56), sf::Color(78, 117, 59)}
       }
      };
  static const std::array<std::pair<sf::Color, sf::Color>, 13> light_tiles_colors =
      {{{sf::Color(0, 0, 0, 0), sf::Color(205, 193, 180)},
        {sf::Color(119, 110, 101), sf::Color(238, 228, 218)},
        {sf::Color(119, 110, 101), sf::Color(237, 224, 200)},
        {sf::Color(249, 246, 242), sf::Color(242, 177, 121)},
        {sf::Color(249, 246, 242), sf::Color(245, 149, 99)},
        {sf::Color(249, 246, 242), sf::Color(246, 124, 95)},
        {sf::Color(249, 246, 242), sf::Color(246, 94, 59)},
        {sf::Color(249, 246, 242), sf::Color(237, 207, 114)},
        {sf::Color(249, 246, 242), sf::Color(237, 204, 97)},
        {sf::Color(249, 246, 242), sf::Color(237, 200, 80)},
        {sf::Color(249, 246, 242), sf::Color(237, 197, 63)},
        {sf::Color(249, 246, 242), sf::Color(237, 194, 46)},
        {sf::Color(249, 246, 242), sf::Color(60, 58, 50)}
       }
      };
  switch (current_)
  {
    case 2:
      if (tile_value > dark_tiles_colors.size() - 2)
      {
        return dark_tiles_colors.back();
      }
      else
      {
        return dark_tiles_colors[tile_value];
      }
    default:
      if (tile_value > light_tiles_colors.size() - 2)
      {
        return light_tiles_colors.back();
      }
      else
      {
        return light_tiles_colors[tile_value];
      }
  }
}

float Theme::GetTileTextScale(int tile_value) const
{
  if (tile_value < 4)
  {
    return 0.7f;
  }
  else if (tile_value < 7)
  {
    return 0.6f;
  }
  else if (tile_value < 10)
  {
    return 0.5f;
  }
  else if (tile_value < 14)
  {
    return 0.35f;
  }
  else
  {
    return 0.3f;
  }
}
