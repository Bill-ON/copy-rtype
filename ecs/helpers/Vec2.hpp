#ifndef VEC2_HPP
#define VEC2_HPP

/**
 * @brief A 2D vector with x and y attributes.
 * 
 */
struct Vec2
{
  Vec2(const float &x = 0, const float &y = 0) : x(x), y(y)
  {
  }

  Vec2(const Vec2 &other)
  {
    x = other.x;
    y = other.y;
  }

  Vec2 operator+(const float &val) const
  {
    return (Vec2{x + val, y + val});
  }

  Vec2 operator-(const float &val) const
  {
    return (Vec2{x - val, y - val});
  }

  Vec2 operator*(const float &val) const
  {
    return (Vec2{x * val, y * val});
  }

  Vec2 operator/(const float &val) const
  {
    return (Vec2{x / val, y / val});
  }

  Vec2 &operator+=(const float &val)
  {
    x += val;
    y += val;
    return *this;
  }

  Vec2 &operator-=(const float &val)
  {
    x -= val;
    y -= val;
    return *this;
  }

  Vec2 &operator*=(const float &val)
  {
    x *= val;
    y *= val;
    return *this;
  }

  Vec2 &operator/=(const float &val)
  {
    x /= val;
    y /= val;
    return *this;
  }

  Vec2 &operator=(const Vec2 &other)
  {
    x = other.x;
    y = other.y;
    return *this;
  }

  Vec2 operator+(const Vec2 &other) const
  {
    return (Vec2{x + other.x, y + other.y});
  }

  Vec2 operator-(const Vec2 &other) const
  {
    return (Vec2{x - other.x, y - other.y});
  }

  Vec2 operator*(const Vec2 &other) const
  {
    return (Vec2{x * other.x, y * other.y});
  }

  Vec2 operator/(const Vec2 &other) const
  {
    return (Vec2{x / other.x, y / other.y});
  }

  Vec2 &operator+=(const Vec2 &other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 &operator-=(const Vec2 &other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2 &operator*=(const Vec2 &other)
  {
    x *= other.x;
    y *= other.y;
    return *this;
  }

  Vec2 &operator/=(const Vec2 &other)
  {
    x /= other.x;
    y /= other.y;
    return *this;
  }

  bool operator==(const Vec2 &other) const
  {
    return (x == other.x && y == other.y);
  }

  bool operator!=(const Vec2 &other) const
  {
    return (x != other.x || y != other.y);
  }

  float x;
  float y;
};

#endif /* VEC2_HPP */
