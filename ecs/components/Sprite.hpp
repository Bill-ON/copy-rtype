#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

namespace Component
{
  /**
    * @brief A component that holds the sprite of an entity.
    * 
    */
  struct Sprite
  {
    /**
     * @brief The name of the texture used
     * by the sprite.
     * 
     */
    std::string texture_name;

    // sf::Sprite sprite;
  };
}

#endif /* SPRITE_HPP */
