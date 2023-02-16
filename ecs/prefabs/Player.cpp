#include "Registry.hpp"
#include "Player.hpp"
#include "keyboard_input.hpp"
#include <cmath>
#include <iostream>

Prefab::Player::Player(Registry &r, Component::Transform &&transform, Component::RigidBody &&rigid_body)
{
    auto e = r.spawn_entity();

    r.add_component(e, std::forward<Component::Transform>(transform));
    auto &physics = *r.add_component<Component::RigidBody>(e, std::forward<Component::RigidBody>(rigid_body));
    r.add_component(e,
        Component::ColliderBox{.rect = Rect(0, 0, 32, 32)});
    r.add_component(e,
        Component::Sprite{.texture_name = "player.png"});
    r.add_component(e,
        Component::Mortal{.health_points = 100});
    action_map actions;
    actions[KEY_UP] = [&physics](){ physics.acceleration += Vec2{0, -PLAYER_BASE_ACCELERATION}; };
    actions[KEY_LEFT] = [&physics](){ physics.acceleration += Vec2{-PLAYER_BASE_ACCELERATION, 0}; };
    actions[KEY_DOWN] = [&physics](){ physics.acceleration += Vec2{0, PLAYER_BASE_ACCELERATION}; };
    actions[KEY_RIGHT] = [&physics](){ physics.acceleration += Vec2{PLAYER_BASE_ACCELERATION, 0}; };

    r.add_component(e, Component::Input{.actions = actions});

    // r.add_component(e, Component::BoxCollider{});
    // r.add_component(e, Component::Sprite{.sprite = sf::Sprite(r.get_system_manager()._texture_manager.get_resource("player.png"))});
    // r.add_component(e, Component::Mortal{.health_points = 100, .entity_id = e});
    // r.add_component(e, Component::Ally{});
    // r.add_component(e, Component::Human{});
}
