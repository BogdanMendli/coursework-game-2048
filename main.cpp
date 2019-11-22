#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Board.hpp"
#include "Graphics.hpp"
#include "Theme.hpp"

int main()
{
  unsigned int board_size = 4;
  bool recursive_merge = false;
  sf::RenderWindow app;
  sf::Event event;
  Graphics view(app);
  Theme theme;
  Board board(board_size, recursive_merge);
  view.Resize(board, theme);
  
  while (app.waitEvent(event))
  {
    if (event.type == sf::Event::Resized)
    {
      view.Resize(board, theme);
    }
    else if (event.type == sf::Event::KeyPressed)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::S:
          if (board_size < 8)
          {
            board_size++;
            board.Reset(board_size, recursive_merge);
            view.Resize(board, theme);
          }
          break;
        case sf::Keyboard::W:
          if (board_size > 3)
          {
            board_size--;
            board.Reset(board_size, recursive_merge);
            view.Resize(board, theme);
          }
          break;
        case sf::Keyboard::BackSpace:
          recursive_merge = !recursive_merge;
          theme.SetTheme((recursive_merge) ? 2 : 1);
          board.Reset(board_size, recursive_merge);
          view.Resize(board, theme);
          break;
        case sf::Keyboard::Return:
          board.Reset(board_size, recursive_merge);
          break;
        case sf::Keyboard::Up:
          board.Up();
          break;
        case sf::Keyboard::Down:
          board.Down();
          break;
        case sf::Keyboard::Left:
          board.Left();
          break;
        case sf::Keyboard::Right:
          board.Right();
          break;
        default:
          break;
      }
    }
    else if (event.type == sf::Event::Closed)
    {
      app.close();
      break;
    }
    view.Display(board, theme);
  }
}
