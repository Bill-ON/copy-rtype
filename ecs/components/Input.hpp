#ifndef INPUT_HPP
#define INPUT_HPP

#include <map>
#include <functional>
#include "keyboard_input.hpp"
#include "Event.hpp"
#include <memory>

using action_map = std::map<keyboardInput, std::function<void ()>>;

namespace Component
{
    /**
     * @brief Handles all the entity events relation
     * to input.
     * 
     */
    struct Input {
        /**
         * @brief The map of action that can be triggered
         * from keyboard input.
         * 
         */
        action_map actions;
    };
}

#endif /* INPUT_HPP */