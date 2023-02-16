#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <queue>
#include "ComponentManager.hpp"

/**
 * @brief Handles all the entities of the
 * game engine.
 * 
 */
class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    /**
     * @brief Create a brand new entity with no component
     * attached to.
     * 
     * @return Entity The newly created entity.
     */
    Entity spawn_entity();
    /**
     * @brief Retrieve an existing entity from its entity
     * index (also called id). The entity must exists.
     * 
     * @param index The index of the expected entity.
     * @return Entity The entity correspoding to the entity
     * index.
     */
    Entity entity_from_index(std::size_t index);
    /**
     * @brief Remove an entity from the game engine.
     * 
     * @param c_m The components manager of the game engine.
     * @param e The entity to be removed.
     */
    void kill_entity(ComponentManager &c_m, Entity const &e);

    /**
     * @brief Get a component reference of a specific type from a specific
     * entity to an entity.
     * 
     * @tparam Component The component type.
     * @param c_m The game engine component manager.
     * @param e The entity.
     * @return SparseArray<Component>::reference_type A reference
     * to the attached components in its component type sparse array.
     */
    template <typename Component>
    typename SparseArray<Component>::reference_type get_component(ComponentManager &c_m, Entity e);

    /**
     * @brief Indicate if a component of a specific type
     * if attached to a specific entity.
     * 
     * @tparam Component The component type.
     * @param c_m The game engine component manager.
     * @param e The entity.
     * @return true The entity has a component of this type
     * attached to itself.
     * @return false The entity has no component of this type
     * attached to itself.
     */
    template <typename Component>
    bool has_component(ComponentManager &c_m, Entity e);

    /**
     * @brief Attach a components to an entity.
     * 
     * e.g:
     * ```cpp
     * struct Component::Position {
     *     int x;
     *     int y;
     * };
     * 
     * Entity e = registry.spawn_entity();
     * ComponentManager &c_m = registry.get_component_manager();
     * Position pos{0, 0};
     * 
     * registry.add_component<Position>(c_m, e, pos);
     * ```
     * 
     * @tparam Component The type of the component which will be attached.
     * It must be already registered in the game engine.
     * @param c_m The component manager of the game engine.
     * @param e The entity to be attached to.
     * @param c The component to be attached.
     * @return SparseArray<Component>::reference_type A reference
     * to the attached components in its component type sparse array.
     */
    template <typename Component>
    typename SparseArray<Component>::reference_type add_component(ComponentManager &, Entity const &, Component &&);
    /**
     * @brief Creates a new component and attach it to an entity.
     * 
     * e.g:
     * ```cpp
     * struct Component::Position {
     *     int x;
     *     int y;
     * };
     * 
     * Entity e = registry.spawn_entity();
     * ComponentManager &c_m = registry.get_component_manager();
     * 
     * registry.add_component<Position>(c_m, e, {0, 0});
     * ```
     * 
     * @tparam Component The type of the component which will be attached.
     * It must be already registered in the game engine.
     * @param c_m The component manager of the game engine.
     * @param e The entity to be attached to.
     * @param p The constructor parameters of the components to be attached.
     * @return SparseArray<Component>::reference_type A reference
     * to the attached components in its component type sparse array.
     */
    template <typename Component, typename... Params>
    typename SparseArray<Component>::reference_type emplace_component(ComponentManager &, Entity const &, Params &&...);
    /**
     * @brief Remove a components of an entity.
     * 
     * @tparam Component The type of the component which will be detached.
     * It must be already registered in the game engine. The entity must
     * already have a component of type attached.
     * @param c_m The component manager of the game engine.
     * @param e The entity to be detached to.
     */
    template <typename Component>
    void remove_component(ComponentManager &, Entity const &);

private:
    /**
     * @brief The index (also called id) of the last
     * created entity.
     * 
     */
    std::size_t _last_registered_entity_id;
    /**
     * @brief The queue of all the removed entities
     * indexes.
     * 
     */
    std::queue<std::size_t> _dead_entities_id;
};

inline EntityManager::EntityManager()
    : _last_registered_entity_id(0),
      _dead_entities_id()
{
}

inline EntityManager::~EntityManager()
{
}

inline Entity EntityManager::spawn_entity()
{
    if (_dead_entities_id.empty())
        return entity_from_index(_last_registered_entity_id++);
    std::size_t id = _dead_entities_id.front();

    _dead_entities_id.pop();
    return entity_from_index(id);
}

inline Entity EntityManager::entity_from_index(std::size_t idx)
{
    return Entity(idx);
}

inline void EntityManager::kill_entity(ComponentManager &c_m, Entity const &e)
{
    for (auto &f : c_m._erase_component_functions_array)
    {
        f.second(e);
    }
    _dead_entities_id.push(e);
}

template <typename Component>
inline typename SparseArray<Component>::reference_type EntityManager::get_component(ComponentManager &c_m, Entity e)
{
    return (c_m.get_components<Component>()[e]);
}

template <typename Component>
bool EntityManager::has_component(ComponentManager &c_m, Entity e)
{
    SparseArray<Component> &comp_array = c_m.get_components<Component>();

    return comp_array.doesContain(e);
}

template <class Component>
inline typename SparseArray<Component>::reference_type EntityManager::add_component(ComponentManager &c_m, Entity const &to, Component &&c)
{
    return c_m.get_components<Component>().insert_at(to, std::forward<Component>(c));
}

template <class Component, class... Params>
inline typename SparseArray<Component>::reference_type EntityManager::emplace_component(ComponentManager &c_m, Entity const &to, Params &&...p)
{
    return c_m.get_components<Component>().emplace_at(to, std::forward<Params>(p)...);
}

template <class Component>
inline void EntityManager::remove_component(ComponentManager &c_m, Entity const &from)
{
    c_m.get_components<Component>().erase(from);
}

#endif /* ENTITYMANAGER_HPP */
