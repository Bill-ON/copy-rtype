#include "keyboard_input.hpp"
#include "sfml_dict.hpp"

keyboardInput get_keyboard_input_from_sfml(const sf::Keyboard::Key key)
{
    const auto &it = SFML_DICT.find(key);

    if (it != SFML_DICT.end()) {
        return it->second;
    } else {
        return keyboardInput::UNKNOWN_KEY;
    }
}