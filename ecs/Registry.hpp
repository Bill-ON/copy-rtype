#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include "Managers.hpp"
#include "Prefabs.hpp"
#include "Systems.hpp"
#include "Camera.hpp"

/**
 * @brief The core of the game engine. Regroups entities, components, systems and events.
 *
 *
 */
class Registry
{
public:
    Registry();
    ~Registry();

    void run();

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
     * @brief Remove an existing entity from the game.
     *
     * @param entity The entity to remove.
     */
    void kill_entity(Entity const &e);

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
     * @brief Attach a components to an entity.
     *
     * e.g:
     * ```cpp
     * struct Component::Transform {
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
    typename SparseArray<Component>::reference_type add_component(Entity const &e, Component &&c);
    /**
     * @brief Creates a new component and attach it to an entity.
     *
     * e.g:
     * ```cpp
     * struct Component::Transform {
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
    typename SparseArray<Component>::reference_type emplace_component(Entity const &e, Params &&...p);
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
    void remove_component(Entity const &e);

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
     * @brief Add a function as a new system to the game engine.
     * The function to be added must always return void, take a Registry
     * reference as first parameter and then a variable number of
     * sparse array of components following its needs.
     *
     * e.g:
     * ```cpp
     * void moveable_system(Registry &,
     *                      SparseArray<Component::Transform> &positions,
     *                      SparseArray<Component::RigidBody> &velocities);
     *
     * ...
     *
     * registry.add_system<Component::Transform, Component::RigidBody>(moveable_system);
     *
     * ```
     *
     * @tparam Components The components types of the sparse array required
     * by the function system.
     * @tparam Function The type of function (free function or lambda) it
     * doesn't need to be defined.
     * @param f The function that will be added to the game engine as
     * system, it can be both lambda or free function.
     */
    template <class... Components, typename Function>
    void add_system(Function &&f);
    /**
     * @brief Add a function as a new system to the game engine.
     * The function to be added must always return void, take a Registry
     * reference as first parameter and then a variable number of
     * sparse array of components following its needs.
     *
     * e.g:
     * ```cpp
     * void moveable_system(Registry &,
     *                      SparseArray<Component::Transform> &positions,
     *                      SparseArray<Component::RigidBody> &velocities);
     *
     * ...
     *
     * registry.add_system<Component::Transform, Component::RigidBody>(moveable_system);
     *
     * ```
     *
     * @tparam Components The components types of the sparse array required
     * by the function system.
     * @tparam Function The type of function (free function or lambda) it
     * doesn't need to be defined.
     * @param f The function that will be added to the game engine as
     * system, it can be both lambda or free function.
     */
    template <class... Components, typename Function>
    void add_system(Function const &f);
    /**
     * @brief Run all the game engine systems.
     *
     */
    void run_systems();

    /**
     * @brief Add a function as a new receivers to the game engine.
     * The function to be added must always return void, and take a
     * reference to the event that will trigger itself.
     *
     * e.g:
     * ```cpp
     * struct Collision {
     *     ...
     * };
     *
     * void collision_receivers(const &Collision collision);
     *
     * ...
     *
     * registry.add_receiver<Collision>(collision_receiver);
     * ```
     *
     * @tparam Event The type of the event that will trigger the
     * receiver, it doesn't need to be registered to the game engine.
     * It is generally a structure that defines the details of the
     * event.
     * @tparam Function The type of function (free function or lambda) it
     * doesn't need to be defined.
     * @param f The function that will be added to the game engine as
     * system, it can be both lambda or free function.
     * @return ConnectionID Return the connection id of
     * the receivers connection to the event manager.
     */
    template <typename Event, typename Function>
    ConnectionID add_receiver(Function &&f);
    /**
     * @brief Add a function as a new receivers to the game engine.
     * The function to be added must always return void, and take a
     * reference to the event that will trigger itself.
     *
     * e.g:
     * ```cpp
     * struct Collision {
     *     ...
     * };
     *
     * void collision_receiver(const &Collision collision);
     *
     * ...
     *
     * registry.add_receiver<Collision>(collision_receiver);
     * ```
     *
     * @tparam Event The type of the event that will trigger the
     * receiver, it doesn't need to be registered to the game engine.
     * It is generally a structure that defines the details of the
     * event.
     * @tparam Function The type of function (free function or lambda) it
     * doesn't need to be defined.
     * @param f The function that will be added to the game engine as
     * system, it can be both lambda or free function.
     * @return ConnectionID Return the connection id of
     * the receivers connection to the event manager.
     */
    template <typename Event, typename Function>
    ConnectionID add_receiver(Function const &f);

    /**
     * @brief Get the camera of the game engine.
     *
     * @return Camera& A reference to the game engine camera.
     */
    Camera &get_camera();

    /**
     * @brief Get the entity manager object
     *
     * @return EntityManager& A reference to the entity manager.
     */
    EntityManager &get_entity_manager();
    /**
     * @brief Get the component manager object
     *
     * @return ComponentManager& A reference to the component manager.
     */
    ComponentManager &get_component_manager();

    /**
     * @brief Get the system manager object
     *
     * @return EntityManager& A reference to the system manager.
     */
    SystemManager &get_system_manager();

    /**
     * @brief All the systems registered of the game engine.
     * At each update the game engine call every systems.
     *
     */
    std::vector<std::function<void(Registry &)>> _systems;
    
    /**
     * @brief Handles the creation and the deletion of
     * entities.
     *
     */
    std::unique_ptr<EntityManager> _entity_manager;
    /**
     * @brief Handles the attachment and detachment of
     * components to entities.
     *
     */
    std::unique_ptr<ComponentManager> _component_manager;
    /**
     * @brief Handles the registration of systems to the
     * game engine.
     *
     */
    std::unique_ptr<SystemManager> _system_manager;
    /**
     * @brief Handles the registration of events and
     * event receivers to the game engine.
     *
     */
    std::unique_ptr<EventManager> _event_manager;
    /**
     * @brief The camera of the game engine. It controls
     * where is the center of the screen, the zoom and
     * the rotation angle.
     * 
     */
    Camera _camera;
};

inline void Registry::run()
{
    _camera.set_center({0.0f, 0.0f});

    register_component<Component::Transform>();
    register_component<Component::RigidBody>();
    register_component<Component::ColliderBox>();
    register_component<Component::Sprite>();
    register_component<Component::Mortal>();
    register_component<Component::Input>();
    register_component<Component::Damage>();

    add_system<Component::Input>(System::input_system);
    add_system<Component::Transform, Component::ColliderBox>(System::debug_system);
    add_system<Component::Transform, Component::RigidBody>(System::movement_system);
    add_system<Component::RigidBody>(System::physics_system);
    add_system<Component::Transform, Component::ColliderBox>(System::collision_system);
    add_system<Component::Mortal>(System::kill_system);
    add_system<Component::Transform, Component::Sprite>(System::draw_system);

    add_receiver<Events::Collision>(Receiver::collision_receiver);

    Prefab::Player(*this, Component::Transform{.position = Vec2(0.0f, 250.0f), .rotation = 0.0f, .scale = Vec2(3.0f, 3.0f)}, Component::RigidBody{.mass = 1.0f, .velocity = Vec2(0.0f, 0.0f), .acceleration = Vec2(0.0f, 0.0f), .delta_clock_movement = sf::Clock(), .delta_clock_physics = sf::Clock()});

    while (_system_manager->_window.isOpen())
    {
        _system_manager->_window.clear(sf::Color(238, 245, 178));
        run_systems();
        _system_manager->_window.display();
    }
}

inline Registry::Registry()
    : _entity_manager(std::make_unique<EntityManager>()),
      _component_manager(std::make_unique<ComponentManager>()),
      _system_manager(std::make_unique<SystemManager>()),
      _event_manager(std::make_unique<EventManager>()),
      _camera(*this)
{
}

inline Registry::~Registry()
{
}

inline Entity Registry::spawn_entity()
{
    return _entity_manager->spawn_entity();
}

inline Entity Registry::entity_from_index(std::size_t idx)
{
    return _entity_manager->entity_from_index(idx);
}

inline void Registry::kill_entity(Entity const &e)
{
    _entity_manager->kill_entity(*_component_manager, e);
}

template <class Component>
inline SparseArray<Component> &Registry::register_component()
{
    return _component_manager->register_component<Component>();
}

template <typename Component>
inline typename SparseArray<Component>::reference_type Registry::add_component(Entity const &e, Component &&c)
{
    return _entity_manager->add_component<Component>(*_component_manager, e, std::forward<Component>(c));
}

template <typename Component, typename... Params>
inline typename SparseArray<Component>::reference_type Registry::emplace_component(Entity const &e, Params &&...p)
{
    return _entity_manager->emplace_component<Component>(*_component_manager, e, std::forward<Params>(p)...);
}

template <typename Component>
inline void Registry::remove_component(Entity const &e)
{
    _entity_manager->remove_component<Component>(*_component_manager, e);
}

template <class Component>
inline SparseArray<Component> &Registry::get_components()
{
    return _component_manager->get_components<Component>();
}

template <class Component>
inline SparseArray<Component> const &Registry::get_components() const
{
    return _component_manager->get_components<Component>();
}

template <class... Components, typename Function>
inline void Registry::add_system(Function &&f)
{
    _systems.push_back([this, f = std::forward<Function>(f)](Registry &r)
                       { f(r, get_components<Components>()...); });
}

template <class... Components, typename Function>
inline void Registry::add_system(Function const &f)
{
    _systems.push_back([this, f](Registry &r)
                       { f(r, get_components<Components>()...); });
}

inline void Registry::run_systems()
{
    for (const auto &system : _systems)
    {
        system(*this);
    }
}

template <typename Event, typename Function>
inline ConnectionID Registry::add_receiver(Function &&f)
{
    return _event_manager->subscribe<Event>(std::forward(f));
}

template <typename Event, typename Function>
inline ConnectionID Registry::add_receiver(Function const &f)
{
    return _event_manager->subscribe<Event>(f);
}

inline EntityManager &Registry::get_entity_manager()
{
    return *_entity_manager;
}

inline ComponentManager &Registry::get_component_manager()
{
    return *_component_manager;
}

inline SystemManager &Registry::get_system_manager()
{
    return *_system_manager;
}

#endif /* REGISTRY_HPP */
