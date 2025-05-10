#include "Camera.h"

Camera::Camera(const glm::vec3& pos, const glm::vec3& forward, float fov) : forward(forward), position(pos), fov(fov)
{
	yaw = glm::degrees(atan2(forward.z, forward.x));  
	pitch = glm::degrees(asin(forward.y));  
}

void Camera::move(const glm::vec3& delta)
{
	position += delta;
}

void Camera::rotate_yaw(float delta_yaw)
{
    yaw += delta_yaw;
    yaw = glm::mod(yaw, 360.f);
    if (yaw < 0.f) {
        yaw += 360.f;
    }

    update_forward();
}

void Camera::rotate_pitch(float delta_pitch)
{
    pitch += delta_pitch;

    pitch = glm::clamp(pitch, -89.9f, 89.9f);

    update_forward();
}

glm::mat4 Camera::get_view()
{
    return glm::lookAt(position ,position + forward, { 0.f, 1.f, 0.f });
}

float Camera::get_fov()
{
    return fov;
}

glm::vec3 Camera::get_forward()
{
    return forward;
}

void Camera::update_forward()
{
    float yaw_radians = glm::radians(yaw);
    float pitch_radians = glm::radians(pitch);

    forward.x = cos(pitch_radians) * cos(yaw_radians);
    forward.y = sin(pitch_radians);
    forward.z = cos(pitch_radians) * sin(yaw_radians);


    forward = glm::normalize(forward);
}






