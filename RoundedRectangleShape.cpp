#include "RoundedRectangleShape.hpp"
#include <cmath>

namespace sf
{
  RoundedRectangleShape::RoundedRectangleShape(const Vector2f & size,
    float radius, std::size_t perCornerPointCount)
  {
    size_ = size;
    radius_ = radius;
    count_ = perCornerPointCount;
    update();
  }

  void RoundedRectangleShape::setSize(const Vector2f & size)
  {
    size_ = size;
    update();
  }

  void RoundedRectangleShape::setSize(float width, float height)
  {
    setSize(Vector2f(width, height));
  }

  const Vector2f & RoundedRectangleShape::getSize() const
  {
    return size_;
  }

  void RoundedRectangleShape::setRadius(float radius)
  {
    radius_ = radius;
    update();
  }

  const float RoundedRectangleShape::getRadius() const
  {
    return radius_;
  }

  void RoundedRectangleShape::setPerCornerPointCount(std::size_t count)
  {
    count_ = count;
    update();
  }

  std::size_t RoundedRectangleShape::getPointCount() const
  {
    return count_ * 4;
  }

  sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
  {
    switch (count_)
    {
      case 0:
        return sf::Vector2f(0, 0);
      case 1:
        return sf::Vector2f((index == 1 || index == 2)
        ? size_.x
        : 0, (index == 2 || index == 3)
        ? size_.y
        : 0);
      default:
        std::size_t current_corner = index / count_;
        double angle = M_PI_2 / (count_ - 1) * (index % count_);
        float cos_offset = static_cast<float>(cos(angle)) * radius_;
        float sin_offset = static_cast<float>(sin(angle)) * radius_;
        switch (current_corner)
        {
          case 0:
            return sf::Vector2f(radius_ - cos_offset, radius_ - sin_offset);
          case 1:
            return sf::Vector2f(size_.x - radius_ + sin_offset, radius_ - cos_offset);
          case 2:
            return sf::Vector2f(size_.x - radius_ + cos_offset, size_.y - radius_ + sin_offset);
          case 3:
            return sf::Vector2f(radius_ - sin_offset, size_.y - radius_ + cos_offset);
          default:
            return sf::Vector2f(0, 0);
        }
    }
  }
}
