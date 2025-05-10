#include <time.h>
#include <math.h>
#include <memory>


#include "../renderer/ShaderProgram.h"
#include "../ResourceManager/ResourceManager.h"
#include "../math/Math.h"
#include "../camera/Camera.h"
#include "../IO/Cursor.h"
#include "../Screen/Screen.h"
#include "../attribute/Attribute.h"
#include "../geometry/Geometry.h"
#include "../object3d/Object3d.h"
#include "../framelimiter/FrameLimiter.h"
#include "../Event/Event.h"
#include "../ssbo/SSBO.h"




class Application {
private:
	Camera camera;
	Screen screen;
	FrameLimiter limiter;
	ResourceManager resource_manager;
	GLint modelLoc, viewLoc, projLoc;
	EventManager event_manager;
public:
	Application(int width, int height, const std::string& path_to_exe);

	~Application();

	Camera& get_camera() {
		return camera;
	}

	EventManager& get_event_manager() {
		return event_manager;
	}

	bool init();

	void run();

	void test_run();
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);