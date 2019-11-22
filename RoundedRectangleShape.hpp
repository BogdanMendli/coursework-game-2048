#ifndef ROUNDEDRECTANGLESHAPE_HPP
#define ROUNDEDRECTANGLESHAPE_HPP

#include <SFML/Graphics/Shape.hpp>

namespace sf
{
  class RoundedRectangleShape: public sf::Shape
  {
  public:
    explicit RoundedRectangleShape(const Vector2f & size = Vector2f(0, 0), float radius = 0, std::size_t perCornerPointCount = 0);
    void setSize(const Vector2f & size);
    void setSize(float width, float height);
    const Vector2f & getSize() const;
    void setRadius(float radius);
    const float getRadius() const;
    void setPerCornerPointCount(std::size_t count);
    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;

  private:
    Vector2f size_;
    float radius_;
    std::size_t count_;
  };
}

#endif
