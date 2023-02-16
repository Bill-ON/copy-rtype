#include "Registry.hpp"
#include "Helpers.hpp"
#include "Events.hpp"

void System::collision_system(Registry &r,
                        SparseArray<Component::Transform> &transforms,
                        SparseArray<Component::ColliderBox> &boxes)
{
    for (auto &&[idx, tf, box] : containers::IndexedZipper(transforms, boxes)) {
        for (auto &&[other_idx, other_tf, other_box] : containers::IndexedZipper(idx, transforms, boxes)) {
            if (idx == other_idx) {
                continue;
            }
            if (isCollision(get_adjusted_rect(box, tf), get_adjusted_rect(other_box, other_tf))) {
                r._event_manager->emit<Events::Collision>();
            }
        }
    }
}

void Receiver::collision_receiver(const Events::Collision &e)
{
    std::cout << "COLLISION" << std::endl;
}