#include "Registry.hpp"
#include "Systems.hpp"

void System::debug_system(Registry &r,
                        SparseArray<Component::Transform> &transforms,
                        SparseArray<Component::ColliderBox> &boxes)
{
    for (auto &&[tf, box] : containers::Zipper(transforms, boxes))
    {
        sf::RectangleShape tmp;
        
        tmp.setPosition(tf.position.x - box.rect.left, tf.position.y - box.rect.top);
        tmp.setOrigin(box.rect.width / 2, box.rect.height / 2);
        tmp.setSize(sf::Vector2f{box.rect.width, box.rect.height});
        tmp.setScale(tf.scale.x, tf.scale.y);
        tmp.setOutlineColor(sf::Color::Blue);
        tmp.setOutlineThickness(1.0f);
        tmp.setFillColor(sf::Color::Transparent);
        r.get_system_manager()._window.draw(tmp);
    }
}