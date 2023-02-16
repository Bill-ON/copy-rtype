#include "Rect.hpp"
#include "Components.hpp"

bool doesContain(const Rect &r, const Vec2 p)
{
    if (p.x >= r.left && p.y >= r.top && p.x <= (r.left + r.width) &&
        p.y <= (r.top + r.height)) {
        return true;
    } else {
        return false;
    }
}

bool isCollision(const Rect &r, const Rect &other_r) {
    return (doesContain(other_r, r.left) ||
            doesContain(other_r, r.top) ||
            doesContain(other_r, r.left + r.width) ||
            doesContain(other_r, r.top + r.height));
}

Rect get_adjusted_rect(Component::ColliderBox &box, Component::Transform &tf)
{
    Vec2 scaledSize{box.rect.width * tf.scale.x, box.rect.height * tf.scale.y};

    return Rect{tf.position.x - scaledSize.x / 2, tf.position.y - scaledSize.y / 2, scaledSize.x, scaledSize.y};
}