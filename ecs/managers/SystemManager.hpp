#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceManager.hpp"

class SystemManager
{
public:
    SystemManager();

    sf::RenderWindow _window;
    ResourceManager<sf::Font> _font_manager;
    ResourceManager<sf::Music> _music_manager;
    ResourceManager<sf::SoundBuffer> _sound_buffer_manager;
    ResourceManager<sf::Texture> _texture_manager;
};

inline SystemManager::SystemManager()
    : _window(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Default),
      _font_manager("fonts", "fail.ttf"),
      _music_manager("musics", "fail.ogg"),
      _sound_buffer_manager("sounds", "fail.ogg"),
      _texture_manager("textures", "fail.png")
{
    _window.setFramerateLimit(60);
}

#endif /* SYSTEM_MANAGER_HPP */
