#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Components.hpp"
#include "Helpers.hpp"

class Registry;

#define PLAYER_BASE_ACCELERATION 50.0f

namespace Prefab
{
    struct Player
    {
        Player(Registry &, Component::Transform &&, Component::RigidBody &&);
    };
}

#endif /* PLAYER_HPP */
