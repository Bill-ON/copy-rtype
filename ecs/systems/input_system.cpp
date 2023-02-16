#include "Registry.hpp"
#include "Helpers.hpp"

static void trigger_action(SparseArray<Component::Input> &inputs, keyboardInput pressed_key)
{
    for (auto &&[input] : containers::Zipper(inputs)) {
        const auto &it = input.actions.find(pressed_key);

        if (it != input.actions.end()) {
            it->second();
        }
    }
}

void System::input_system(Registry &r,
                          SparseArray<Component::Input> &inputs)
{
    sf::Event event;

    while (r._system_manager->_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            r._system_manager->_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            r._system_manager->_window.close();
        if (event.type == sf::Event::KeyPressed) {
            keyboardInput pressed_key = get_keyboard_input_from_sfml(event.key.code);

            trigger_action(inputs, pressed_key);
        }
    }
}
