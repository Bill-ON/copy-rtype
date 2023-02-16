#ifndef EVENT_HPP
#define EVENT_HPP

#include <cstddef>

class BaseEvent
{
public:
    typedef std::size_t Family;

    virtual ~BaseEvent();

protected:
    /**
     * @brief The family of the event.
     * It enable the event manager to notify
     * every event receivers when a event
     * of their corresponding type is emitted.
     * 
     */
    static Family family_counter;
};

/**
 * @brief The from which every event is derived
 * from. Warning: The events doesn't need to be
 * explictly derived from Event class in their
 * declaration.
 * 
 * @tparam Derived Use to produce c++ CRTP.
 */
template <typename Derived>
class Event : public BaseEvent
{
public:
    /**
     * @brief The family of the event.
     * It enable the event manager to notify
     * every event receivers when a event
     * of their corresponding type is emitted.
     * 
     */
    static Family family()
    {
        static Family family = family_counter++;
        return family;
    }
};

#endif /* EVENT_HPP */