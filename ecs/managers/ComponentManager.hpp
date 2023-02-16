#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include <any>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <functional>
#include "Entity.hpp"
#include "SparseArray.hpp"

/**
 * @brief Handles all the components of the
 * game engine.
 * 
 */
class ComponentManager
{
public:
    ComponentManager();
    ~ComponentManager();

    /**
     * @brief Add a new type of components to the game engine.
     * 
     * @tparam Component The new components type to be added.
     * @return SparseArray<Component>& A reference to the newly
     * created sparse array of components.
     */
    template <class Component>
    SparseArray<Component> &register_component();

    /**
     * @brief Get the game engine sparse array of the corresponding
     * component type.
     * 
     * @tparam Component The type of the components sparse array to
     * be returned. It must be already registered in the game engine.
     * @return SparseArray<Component>& the game engine sparse array of
     * the corresponding components type.
     */
    template <class Component>
    SparseArray<Component> &get_components();
    /**
     * @brief Get the game engine sparse array of the corresponding
     * component type.
     * 
     * @tparam Component The type of the components sparse array to
     * be returned. It must be already registered in the game engine.
     * @return SparseArray<Component>& the game engine sparse array of
     * the corresponding components type.
     */
    template <class Component>
    SparseArray<Component> const &get_components() const;

    /**
     * @brief A map that stores all the destructor function of the
     * components type of the game engine.
     * 
     */
    std::unordered_map<std::type_index, std::function<void(Entity const &)>> _erase_component_functions_array;

private:
    /**
     * @brief A map that stores all the type of components in the
     * game engine.
     * 
     */
    std::unordered_map<std::type_index, std::any> _components_array;
};

inline ComponentManager::ComponentManager()
{
}

inline ComponentManager::~ComponentManager()
{
}

template <class Component>
inline SparseArray<Component> &ComponentManager::register_component()
{
    _components_array[std::type_index(typeid(Component))] = SparseArray<Component>();
    _erase_component_functions_array[std::type_index(typeid(Component))] = [this](Entity const &e)
    {
        this->get_components<Component>().erase(e);
    };
    return get_components<Component>();
}

template <class Component>
inline SparseArray<Component> &ComponentManager::get_components()
{
    return std::any_cast<SparseArray<Component> &>(_components_array[std::type_index(typeid(Component))]);
}

template <class Component>
inline SparseArray<Component> const &ComponentManager::get_components() const
{
    return std::any_cast<SparseArray<Component> const &>(_components_array.at(std::type_index(typeid(Component))));
}

#endif /* COMPONENT_MANAGER_HPP */
