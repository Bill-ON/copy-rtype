#ifndef SFML_INPUT_HPP
#define SFML_INPUT_HPP

#include <map>
#include <SFML/Window/Keyboard.hpp>
#include "keyboard_input.hpp"

/**
 * @brief A dictionnary that convert a good part of the
 * sfml keyboard input into the game engine inputs.
 *
 */
const static std::map<sf::Keyboard::Key, keyboardInput> SFML_DICT = {
    {sf::Keyboard::Key::A, keyboardInput::KEY_A},
    {sf::Keyboard::Key::B, keyboardInput::KEY_B},
    {sf::Keyboard::Key::C, keyboardInput::KEY_C},
    {sf::Keyboard::Key::D, keyboardInput::KEY_D},
    {sf::Keyboard::Key::E, keyboardInput::KEY_E},
    {sf::Keyboard::Key::F, keyboardInput::KEY_F},
    {sf::Keyboard::Key::G, keyboardInput::KEY_G},
    {sf::Keyboard::Key::H, keyboardInput::KEY_H},
    {sf::Keyboard::Key::I, keyboardInput::KEY_I},
    {sf::Keyboard::Key::J, keyboardInput::KEY_J},
    {sf::Keyboard::Key::K, keyboardInput::KEY_K},
    {sf::Keyboard::Key::L, keyboardInput::KEY_L},
    {sf::Keyboard::Key::M, keyboardInput::KEY_M},
    {sf::Keyboard::Key::N, keyboardInput::KEY_N},
    {sf::Keyboard::Key::O, keyboardInput::KEY_O},
    {sf::Keyboard::Key::P, keyboardInput::KEY_P},
    {sf::Keyboard::Key::Q, keyboardInput::KEY_Q},
    {sf::Keyboard::Key::R, keyboardInput::KEY_R},
    {sf::Keyboard::Key::S, keyboardInput::KEY_S},
    {sf::Keyboard::Key::T, keyboardInput::KEY_T},
    {sf::Keyboard::Key::U, keyboardInput::KEY_U},
    {sf::Keyboard::Key::V, keyboardInput::KEY_V},
    {sf::Keyboard::Key::W, keyboardInput::KEY_W},
    {sf::Keyboard::Key::X, keyboardInput::KEY_X},
    {sf::Keyboard::Key::Y, keyboardInput::KEY_Y},
    {sf::Keyboard::Key::Z, keyboardInput::KEY_Z},
    {sf::Keyboard::Key::Up, keyboardInput::KEY_UP},
    {sf::Keyboard::Key::Down, keyboardInput::KEY_DOWN},
    {sf::Keyboard::Key::Left, keyboardInput::KEY_LEFT},
    {sf::Keyboard::Key::Right, keyboardInput::KEY_RIGHT},
    {sf::Keyboard::Key::Space, keyboardInput::KEY_SPACE},
    {sf::Keyboard::Key::Return, keyboardInput::KEY_RETURN},
    {sf::Keyboard::Key::Backspace, keyboardInput::KEY_BACKSPACE},
    {sf::Keyboard::Key::Delete, keyboardInput::KEY_DELETE},
    {sf::Keyboard::Key::LShift, keyboardInput::KEY_SHIFT},
    {sf::Keyboard::Key::LAlt, keyboardInput::KEY_ALT},
    {sf::Keyboard::Key::LControl, keyboardInput::KEY_CTRL},
    {sf::Keyboard::Key::Tab, keyboardInput::KEY_TAB},
    {sf::Keyboard::Key::Num1, keyboardInput::KEY_1},
    {sf::Keyboard::Key::Num2, keyboardInput::KEY_2},
    {sf::Keyboard::Key::Num3, keyboardInput::KEY_3},
    {sf::Keyboard::Key::Num4, keyboardInput::KEY_4},
    {sf::Keyboard::Key::Num5, keyboardInput::KEY_5},
    {sf::Keyboard::Key::Num6, keyboardInput::KEY_6},
    {sf::Keyboard::Key::Num7, keyboardInput::KEY_7},
    {sf::Keyboard::Key::Num8, keyboardInput::KEY_8},
    {sf::Keyboard::Key::Num9, keyboardInput::KEY_9},
    {sf::Keyboard::Key::Num0, keyboardInput::KEY_0},
};

keyboardInput get_keyboard_input_from_sfml(const sf::Keyboard::Key key);

#endif /* SFML_INPUT_HPP */