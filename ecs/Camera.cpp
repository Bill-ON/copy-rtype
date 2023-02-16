#include "Camera.hpp"
#include "Registry.hpp"
#include "Events.hpp"

Camera::Camera(Registry &r) : _r(r), _state({0, 0}, 1.0f, 0.0f)
{
    r.add_receiver<Events::CameraConfig>(Receiver::configure_camera);
    emitConfigEvent();
}

Camera::Camera(Registry &r, const CameraState &state) : _r(r), _state(state)
{
    r.add_receiver<Events::CameraConfig>(Receiver::configure_camera);
    emitConfigEvent();
}

void Camera::emitConfigEvent() const
{
    _r._event_manager->emit<Events::CameraConfig>(
                        _state, _r._system_manager->_window);
}
