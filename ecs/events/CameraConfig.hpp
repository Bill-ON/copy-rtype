#ifndef CAMERA_CONFIG_HPP
#define CAMERA_CONFIG_HPP

#include "Camera.hpp"

#include <SFML/Graphics.hpp>

namespace Events {
    struct CameraConfig {
        CameraConfig(const CameraState &state, sf::RenderWindow &window)
        : state(state), window(window) {}

        const CameraState &state;
        sf::RenderWindow &window;
    };
}

#endif /* CAMERA_CONFIG_HPP */