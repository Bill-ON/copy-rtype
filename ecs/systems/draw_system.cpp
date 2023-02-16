#include "Registry.hpp"
#include "Systems.hpp"
#include "Events.hpp"

void System::draw_system(Registry &r,
                         SparseArray<Component::Transform> &transforms,
                         SparseArray<Component::Sprite> &sprites)
{
    for (auto &&[tf, sprite] : containers::Zipper(transforms, sprites))
    {
        sf::Sprite tmp;
        sf::IntRect rect;

        tmp.setTexture(r.get_system_manager()._texture_manager.get_resource(sprite.texture_name));
        rect = tmp.getTextureRect();

        tmp.setPosition(tf.position.x, tf.position.y);
        tmp.setOrigin(rect.width / 2, rect.height / 2);
        tmp.setScale(tf.scale.x, tf.scale.y);
        tmp.setRotation(tf.rotation);
        r.get_system_manager()._window.draw(tmp);
    }
}

void Receiver::configure_camera(const Events::CameraConfig &e)
{
    sf::View view;

    view.reset(sf::FloatRect(0, 0, 1920, 1080));
    view.setCenter(e.state.center.x, e.state.center.y);
    view.rotate(e.state.rotation);
    e.window.setView(view);
}