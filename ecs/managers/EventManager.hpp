#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <cstdint>
#include <cstddef>
#include <vector>
#include <list>
#include <utility>
#include <memory>
#include "3rdparty/simplesignal.h"

#include "Event.hpp"

typedef Simple::Signal<void(const void *)> EventSignal;
typedef std::shared_ptr<EventSignal> EventSignalPtr;
typedef std::weak_ptr<EventSignal> EventSignalWeakPtr;
typedef std::size_t EventID;
typedef std::size_t ConnectionID;

/**
 * @brief Represents a pub-sub simplesignal
 * connection.
 * 
 */
struct Connection
{
    EventSignalWeakPtr ptr;
    EventID event;
};

/**
 * @brief Handles events and so inter-system
 * communication.
 * 
 */
class EventManager
{
public:
    EventManager() = default;
    virtual ~EventManager(){};

    /**
     * @brief Subscribe a receiver function to an event
     * publishment (pub-sub relation). After subscription
     * whenever the corresponding event is emitted it will
     * then trigger the receiver function.
     * 
     * @tparam E The event type that will trigger
     * the receiver function.
     * @tparam Function The type of function (free function or lambda) it
     * doesn't need to be defined.
     * @param f The receivers function to be triggered.
     * @return ConnectionID The id that represents the
     * newly created connections.
     */
    template <typename E, typename Function>
    ConnectionID subscribe(const Function &f)
    {
        auto wrapper = EventCallbackWrapper<E>(std::bind(f, std::placeholders::_1));
        auto sig = signal_for(Event<E>::family());
        auto connectionID = sig->connect(wrapper);

        _connections.insert(std::make_pair(connectionID, Connection{EventSignalWeakPtr(sig), Event<E>::family()}));
        return connectionID;
    }

    /**
     * @brief Subscribe a receiver function to an event
     * publishment (pub-sub relation). After subscription
     * whenever the corresponding event is emitted it will
     * then trigger the receiver function.
     * 
     * @tparam E The event type that will trigger
     * the receiver function.
     * @tparam Function The type of function (free function or lambda) it
     * doesn't need to be defined.
     * @param f The receivers function to be triggered.
     * @return ConnectionID The id that represents the
     * newly created connections.
     */
    template <typename E, typename Function>
    ConnectionID subscribe(Function &&f)
    {
        auto wrapper = EventCallbackWrapper<E>(std::bind(std::forward(f), std::placeholders::_1));
        auto sig = signal_for(Event<E>::family());
        auto connectionID = sig->connect(wrapper);

        _connections.insert(std::make_pair(connectionID, Connection{EventSignalWeakPtr(sig), Event<E>::family()}));
        return connectionID;
    }

    /**
     * @brief Unsubscribe a receiver function from an
     * event publishment.
     * 
     * @param connection The connection id generated at
     * subscription.
     */
    void unsubscribe(ConnectionID connection)
    {
        // Assert that it has been subscribed before
        assert(_connections.find(connection) != _connections.end());
        auto [ptr, EventID] = _connections[connection];

        if (!ptr.expired())
        {
            ptr.lock()->disconnect(connection);
        }
        _connections.erase(connection);
    }

    /**
     * @brief Emit an event to trigger receiver
     * functions.
     * 
     * @tparam E The type of the event.
     * @param event The event.
     */
    template <typename E>
    void emit(const E &event)
    {
        auto sig = signal_for(Event<E>::family());

        sig->emit(&event);
    }

    /**
     * @brief Emit an already constructed event.
     * 
     * @tparam E The type of the event.
     * @param event The event.
     */
    template <typename E>
    void emit(std::unique_ptr<E> event)
    {
        auto sig = signal_for(Event<E>::family());

        sig->emit(event.get());
    }

    /**
     * @brief Construct and emit an event.
     * 
     * @tparam E The type of the event.
     * @param event The event.
     * @param args The parameters of the event constructor.
     */
    template <typename E, typename... Args>
    void emit(Args &&...args)
    {
        // Using 'E event(std::forward...)' causes VS to fail with an internal error. Hack around it.
        E event = E(std::forward<Args>(args)...);
        auto sig = signal_for(std::size_t(Event<E>::family()));

        sig->emit(&event);
    }

    /**
     * @brief Return the number of receiver functions
     * connected in the event manager.
     * 
     * @return std::size_t The number of connected
     * receiver functions.
     */
    std::size_t connected_receivers() const
    {
        std::size_t size = 0;

        for (EventSignalPtr handler : _handlers)
        {
            if (handler)
            {
                size += handler->size();
            }
        }
        return size;
    }

private:
    EventSignalPtr &signal_for(std::size_t id)
    {
        if (id >= _handlers.size())
        {
            _handlers.resize(id + 1);
        }
        if (!_handlers[id])
        {
            _handlers[id] = std::make_shared<EventSignal>();
        }
        return _handlers[id];
    }

    // Functor used as an event signal callback that casts to E.
    template <typename E>
    struct EventCallbackWrapper
    {
        explicit EventCallbackWrapper(std::function<void(const E &)> callback) : callback(callback) {}
        void operator()(const void *event) { callback(*(static_cast<const E *>(event))); }
        std::function<void(const E &)> callback;
    };

    /**
     * @brief The vector that store all the
     * simplesignal weakptr receivers function.
     * 
     */
    std::vector<EventSignalPtr> _handlers;
    /**
     * @brief The map that store all the
     * event connections.
     * 
     */
    std::unordered_map<ConnectionID, Connection> _connections;
};

#endif /* EVENT_MANAGER_HPP */