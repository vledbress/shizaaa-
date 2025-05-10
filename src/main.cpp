#include "application/Application.h"
#include <functional>


void _cdecl asd(void) {
	std::cout << "penis" << std::endl;
}



int main(int argc, char** argv) {


	

	Application app(192 * 5, 108 * 5, argv[0]);
	if (!app.init()) {
		std::cout << "can't initialize app\n";
		return -1;
	}
	app.test_run();

	



}

