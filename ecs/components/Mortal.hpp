#ifndef MORTAL_HPP
#define MORTAL_HPP

#include <cstddef>

namespace Component
{
  /**
   * @brief A component that holds the health of an entity.
   *
   */
  struct Mortal
  {
    /**
     * @brief A value that represents the living
     * points of an entity. An entity die when health
     * points come to or below zero.
     * 
     */
    std::size_t health_points;
    std::size_t entity_id;
  };
}

#endif /* MORTAL_HPP */
