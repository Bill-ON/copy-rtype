#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Components.hpp"

#include "SparseArray.hpp"
#include "Zipper.hpp"
#include "IndexedZipper.hpp"
#include "Event.hpp"
#include "Events.hpp"

class Registry;

namespace System
{
    void movement_system(Registry &,
                         SparseArray<Component::Transform> &,
                         SparseArray<Component::RigidBody> &);

    void physics_system(Registry &r,
                                SparseArray<Component::RigidBody> &rigid_bodies);

    void draw_system(Registry &,
                     SparseArray<Component::Transform> &,
                     SparseArray<Component::Sprite> &);

    void input_system(Registry &r,
                      SparseArray<Component::Input> &inputs);

    void collision_system(Registry &r,
                          SparseArray<Component::Transform> &transforms,
                          SparseArray<Component::ColliderBox> &boxes);

    // void collision_system(Registry &,
    //   SparseArray<Component::Sprite> &,
    //   SparseArray<Component::BoxCollider> &,
    //   SparseArray<Component::Mortal> &,
    //   SparseArray<Component::Ally> &,
    //   SparseArray<Component::Enemy> &,
    //   SparseArray<Component::Obstacle> &);</Component::Obstacle>

    void kill_system(Registry &,
                     SparseArray<Component::Mortal> &);

    void debug_system(Registry &r,
                      SparseArray<Component::Transform> &transforms,
                      SparseArray<Component::ColliderBox> &collider_boxes);
}

namespace Receiver
{
    void configure_camera(const Events::CameraConfig &e);

    void collision_receiver(const Events::Collision &e);
}

#endif /* SYSTEMS_HPP */
