#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstddef>

/**
 * @brief An entity of the game engine.
 * An entity by itself isn't very much but
 * an id. However a variable number of components
 * can be attached to an entity to gives it
 * behaviors, data, etc...
 * 
 */
class Entity
{
public:
    ~Entity();
    operator std::size_t() const;

    friend class EntityManager;

private:
    explicit Entity(std::size_t const &);

    /**
     * @brief The unique id (also called index)
     * of the entity.
     * 
     */
    std::size_t _id;
};

inline Entity::Entity(std::size_t const &id)
    : _id(id)
{
}

inline Entity::~Entity()
{
}

inline Entity::operator std::size_t() const
{
    return _id;
}

#endif /* ENTITY_HPP */
