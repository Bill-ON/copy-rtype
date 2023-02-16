#include "Registry.hpp"
#include "Systems.hpp"
#include <cmath>

void System::physics_system(Registry &r,
                            SparseArray<Component::RigidBody> &rigid_bodies)
{
  for (auto &&[rb] : containers::Zipper(rigid_bodies))
  {
    sf::Time delta_time = rb.delta_clock_physics.restart();

    rb.acceleration *= powf(0.1, delta_time.asSeconds());
    rb.velocity *= powf(0.1, delta_time.asSeconds());
  }
}
