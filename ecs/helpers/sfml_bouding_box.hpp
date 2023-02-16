#ifndef ADJUSTMENT_HPP
#define ADJUSTMENT_HPP

#include "Components.hpp"

/**
 * @brief A function that check if a point (2D position)
 * is contained in a rectangle (generally a bounding box).
 * 
 * @param r The rectangle which is compose of 4 position (2D positions).
 * @param p The point to be checked.
 * @return true The point is contained in the rectangle.
 * @return false The point isn't contained in the rectangle.
 */
bool doesContain(const Rect &r, const Vec2 p);

/**
 * @brief A function that check if there is an intersection
 * between two rectangles (generally two bounding box).
 * 
 * @param r The first rectangle to check.
 * @param other_r The second rectangle to check.
 * @return true There is a collision between the two
 * rectangles.
 * @return false There is no collision between the two
 * rectangles. 
 */
bool isCollision(const Rect &r, const Rect &other_r);

/**
 * @brief Create a new Rect struct adjusted to
 * a Transform component entity (it is used mainly
 * to retrieve bounding box).
 * 
 * @param box The ColliderBox component where the
 * bounding box template is stored.
 * @param tf The Transform component that gives the
 * whole context in which the template bouding
 * boc will be.
 * @return Rect A structure that represent a 2D
 * rectangle 
 */
Rect get_adjusted_rect(Component::ColliderBox &box, Component::Transform &tf);

#endif /* ADJUSTMENT_HPP */