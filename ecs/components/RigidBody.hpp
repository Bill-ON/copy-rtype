#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <SFML/System.hpp>
#include "Vec2.hpp"

namespace Component
{
  /**
   * @brief A component that holds the mass, velocity
   * and acceleration of an entity. It is used to
   * compute the physics of an entity body.
   * 
   */
  struct RigidBody
  {
    /**
     * @brief The weight of the entity.
     * 
     */
    float mass;
    /**
     * @brief The velocity of the entity.
     * Meaning its movement between each
     * tick of the clock.
     * 
     */
    Vec2 velocity;
    /**
     * @brief The increasing speed
     * of the velocity.
     * 
     */
    Vec2 acceleration;
    /**
     * @brief the clock that will
     * determin the refresh rate
     * of the entity physics.
     */
    sf::Clock delta_clock_movement;
    sf::Clock delta_clock_physics;
  };
}

#endif /* RIGIDBODY_HPP */
