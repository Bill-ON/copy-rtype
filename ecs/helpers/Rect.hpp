#ifndef RECT_HPP
#define RECT_HPP

/**
 * @brief A 2D rectangle with left, top, width and height attributes.
 * 
 */
struct Rect
{
  Rect(const float &left = 0, const float &top = 0, const float &width = 0, const float &height = 0) : left(left), top(top), width(width), height(height)
  {
  }

  Rect(const Rect &Rect)
  {
    left = Rect.left;
    top = Rect.top;
    width = Rect.width;
    height = Rect.height;
  }

  bool operator==(const Rect &Rect) const
  {
    return (left == Rect.left && top == Rect.top && width == Rect.width && height == Rect.height);
  }

  bool operator!=(const Rect &Rect) const
  {
    return (left != Rect.left || top != Rect.top || width != Rect.width || height != Rect.height);
  }

  float left;
  float top;
  float width;
  float height;
};

#endif /* RECT_HPP */
