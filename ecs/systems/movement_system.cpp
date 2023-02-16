#include "Registry.hpp"
#include "Systems.hpp"

void System::movement_system(Registry &r,
                             SparseArray<Component::Transform> &transforms,
                             SparseArray<Component::RigidBody> &rigid_bodies)
{
    for (auto &&[tfm, rb] : containers::Zipper(transforms, rigid_bodies))
    {
        sf::Time delta_time = rb.delta_clock_movement.restart();

        rb.velocity += rb.acceleration * delta_time.asSeconds();
        tfm.position += rb.velocity * delta_time.asSeconds();
    }
}
