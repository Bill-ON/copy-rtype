#ifndef COLLIDER_BOX_HPP
#define COLLIDER_BOX_HPP

#include "Rect.hpp"

namespace Component
{
  /**
   * @brief A component that holds the collision rectangle of an entity.
   * 
   */
  struct ColliderBox
  {
    /**
     * @brief The rectangle BoudingBox.
     * 
     */
    Rect rect;
  };
}

#endif /* COLLIDER_BOX_HPP */
