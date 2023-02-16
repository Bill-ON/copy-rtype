#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vec2.hpp"

/**
 * @brief A state of a 2D camera, including
 * its position, zoom and rotation angle.
 * 
 */
struct CameraState {
    CameraState(const Vec2 center, const float zoom, const float rotation) :
    center(center), zoom(zoom), rotation(rotation) {}

    /**
     * @brief The 2D position of the center of
     * the camera.
     * 
     */
    Vec2 center;
    /**
     * @brief The zoom value of the camera.
     * 
     */
    float zoom;
    /**
     * @brief The rotation angle value of the
     * camera.
     * 
     */
    float rotation;
};

class Registry;

/**
 * @brief Handles all the parameters relative to
 * the camera like position, zoom, rotation.
 * 
 */
class Camera
{
public:
    Camera(Registry &r);
    Camera(Registry &r, const CameraState &state);

    /**
     * @brief Get the state of the camera
     * (position, zoom, rotation angle).
     * 
     */
    CameraState get_state() const;
    /**
     * @brief Get the center position of the
     * camera
     * 
     * @return Vec2 The center position of the camera
     */
    Vec2 get_center() const;
    /**
     * @brief Get the zoom value of the camera
     * 
     * @return float The zoom value of the camera
     */
    float get_zoom() const;
    /**
     * @brief Get the rotation angle value 
     * of the camera.
     * 
     * @return float The rotation angle value
     * of the camera.
     */
    float get_rotation() const;

    /**
     * @brief Set the state of the camera
     * (position, zoom, rotation angle).
     * 
     * @param state The new state of the camera.
     */
    void set_state(const CameraState &state);
    /**
     * @brief Set the center position of the
     * camera.
     * 
     * @param center The new center of the camera.
     */
    void set_center(const Vec2 center);
    /**
     * @brief Set the zoom value of the
     * camera.
     * 
     * @param zoom The new zoom value of the camera. 
     */
    void set_zoom(const float zoom);
    /**
     * @brief Set the rotation angle value 
     * of the camera.
     * 
     * @param rotation The new rotation angle value
     * of the camera.
     */
    void set_rotation(const float rotation);
private:
    void emitConfigEvent() const;

    Registry &_r;
    CameraState _state;
};

inline CameraState Camera::get_state() const {
    return _state;
}

inline Vec2 Camera::get_center() const {
    return _state.center;
}

inline float Camera::get_zoom() const {
    return _state.zoom;
}

inline float Camera::get_rotation() const {
    return _state.rotation;
}

inline void Camera::set_state(const CameraState &state) {
    _state = state;
    emitConfigEvent();
}

inline void Camera::set_center(const Vec2 center) {
    _state.center = center;
    emitConfigEvent();
}

inline void Camera::set_zoom(const float zoom) {
    _state.zoom = zoom;
    emitConfigEvent();
}

inline void Camera::set_rotation(const float rotation) {
    _state.rotation = rotation;
    emitConfigEvent();
}

#endif /* CAMERA_HPP */