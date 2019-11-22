#include "Graphics.hpp"
#include <algorithm>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Board.hpp"
#include "Theme.hpp"

Graphics::Graphics(sf::RenderWindow & window):
  window_(window)
{
  window.create(sf::VideoMode(1920, 1200), "2048 SFML (Kurs C++ | Maschenko B.B. | 3530904/80004)");
  window.setFramerateLimit(60);
  font_.loadFromFile("ClearSans-Bold.ttf");
  tile_text_.setFont(font_);
  score_text_.setFont(font_);
}

void Graphics::Display(const Board & board, const Theme & theme)
{
  window_.clear(theme.GetBackgroundColor());
  DrawScore(board, theme);
  DrawBoard(board, theme);
  window_.display();
}

void Graphics::Resize(const Board & board, const Theme & theme)
{
  sf::Vector2u size = window_.getSize();
  float min = std::min(size.x, size.y);
  min *= 0.75f;
  board_background_.setSize(sf::Vector2f(min, min));
  board_background_.setRadius(min / 50.0f);
  board_background_.setPerCornerPointCount(15);
  board_background_.setFillColor(theme.GetBoardColor());
  board_background_.setOrigin(min / 2.0f, min / 2.0f);
  board_background_.setPosition(size.x / 2.0f, size.y / 1.8f);
  score_background_.setSize(sf::Vector2f(min / 2.0f, min / 8.0f));
  score_background_.setRadius(min / 50.0f);
  score_background_.setPerCornerPointCount(15);
  score_background_.setFillColor(theme.GetScoreColor().second);
  score_background_.setOrigin(min / 4.0f, min / 16.0f);
  score_background_.setPosition(size.x / 2.0f, size.y / 11.0f);
  score_text_.setFillColor(theme.GetScoreColor().first);
  score_text_.setCharacterSize(static_cast<unsigned int>(score_background_.getSize().y * 0.7f));
  tile_offset_ = min * 0.15f / (board.Size() + 1);
  min = min * 0.85f / board.Size();
  tile_background_.setSize(sf::Vector2f(min, min));
  tile_background_.setOrigin(min / 2.0f, min / 2.0f);
  tile_background_.setRadius(min / 18.0f);
  tile_background_.setPerCornerPointCount(10);
  window_.setView(sf::View(sf::FloatRect(0.0f, 0.0f, size.x, size.y)));
}

void Graphics::DrawBoard(const Board & board, const Theme & theme)
{
  window_.draw(board_background_);
  sf::Vector2f top_left_point(board_background_.getPosition() - board_background_.getSize() / 2.0f
      + sf::Vector2f(tile_offset_, tile_offset_) + tile_background_.getSize() / 2.0f);
  for (unsigned int i = 0; i < board.Size(); ++i)
  {
    for (unsigned int j = 0; j < board.Size(); ++j)
    {
      int tile_value = board.Tile(i, j);
      tile_background_.setPosition(
          top_left_point + sf::Vector2f((tile_offset_ + tile_background_.getSize().x) * j,
            (tile_offset_ + tile_background_.getSize().y) * i));
      tile_background_.setFillColor(theme.GetTileColor(tile_value).second);
      window_.draw(tile_background_);
      if (board.Tile(i, j))
      {
        tile_text_.setFillColor(theme.GetTileColor(tile_value).first);
        tile_text_.setString(std::to_string(1 << board.Tile(i, j)));
        tile_text_.setCharacterSize(static_cast<unsigned int>(tile_background_.getSize().x
            * theme.GetTileTextScale(tile_value)));
        sf::FloatRect text_bounds = tile_text_.getLocalBounds();
        tile_text_.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
        tile_text_.setPosition(tile_background_.getPosition());
        window_.draw(tile_text_);
      }
    }
  }
}

void Graphics::DrawScore(const Board & board, const Theme & theme)
{
  window_.draw(score_background_);
  if (board.Locked())
  {
    score_text_.setString("Game Over!");
  }
  else
  {
    score_text_.setString(std::to_string(board.Score()));
  }
  sf::FloatRect text_bounds = score_text_.getLocalBounds();
  score_text_.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
  score_text_.setPosition(score_background_.getPosition());
  window_.draw(score_text_);
}
