//#include "Cursor.h"
//
//void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
//{
//    Cursor* pcur = (Cursor*)glfwGetWindowUserPointer(window);
//    auto pos = pcur->getMousePos();
//
//    Math::vec4 direction((float)(xpos - pos.first), (float)(ypos - pos.second), 0, 1);
//    //direction.normalize();
//    
//    pcur->setDir(direction);
//    pcur->setMousePos(400, 300);
//}
//
//
//
//Cursor::Cursor(GLFWwindow* winPtr) : winPtr(winPtr), lastX(0.0f), lastY(0.0f), isDragging(false) {
//
//	glfwGetCursorPos(winPtr, &lastX, &lastY);
//	glfwSetCursorPosCallback(winPtr, mouseMoveCallback);
//    glfwSetInputMode(winPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
//
//
//}
//
//void Cursor::setMousePos(double newx, double newy)
//{
//	lastX = newx;
//	lastY = newy;
//	glfwSetCursorPos(winPtr, lastX, lastY);
//
//}
//
//std::pair<double, double> Cursor::getMousePos()
//{
//	return std::pair<double, double>(lastX, lastY);
//}
