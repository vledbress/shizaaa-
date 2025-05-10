#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


class SSBO {
private:
	GLuint _id;
	void bind();
	void unbind();
public:
	SSBO();

	~SSBO();

	void set_data(const std::vector<glm::mat4>& matrices);

	void update_single_matrix(GLuint index, const glm::mat4& matrix);
};







