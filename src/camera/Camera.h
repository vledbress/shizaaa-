#pragma once
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




class Camera {
private:
	glm::vec3 position;
	glm::vec3 forward;

	float yaw, pitch, fov;
public:
	Camera(const glm::vec3& pos, const glm::vec3& forward, float fov);

	void move(const glm::vec3& delta);

	void rotate_yaw(float delta_yaw);

	void rotate_pitch(float delta_pitch);

	glm::mat4 get_view();

	float get_fov();

	glm::vec3 get_forward();
private:
	void update_forward();
};










