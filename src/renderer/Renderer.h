#pragma once
#include <GLFW/glfw3.h>
#include "../object3d/Object3d.h"
#include "../camera/Camera.h"
#include "../ssbo/SSBO.h"



class Renderer {
private:
	std::unordered_map<std::shared_ptr<Mesh>, std::vector<std::shared_ptr<Actor>>> render_groups;
	glm::mat4 perspective;
	SSBO ssbo;
public:
	Renderer();
	void update_if_needed();
	void draw();
	void add_group();
	void remove_actor();
};




