#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Vec2.hpp"

namespace Component
{
  /**
   * @brief A component that holds the position, rotation and scale of an entity.
   * 
   */
  struct Transform
  {
    /**
     * @brief The position of the entity
     * in a 2D world.
     * 
     */
    Vec2 position;
    /**
     * @brief The rotation angle of
     * the entity.
     * 
     */
    float rotation;
    /**
     * @brief The size scaling of
     * the entity.
     * 
     */
    Vec2 scale;
  };
}

#endif /* TRANSFORM_HPP */
