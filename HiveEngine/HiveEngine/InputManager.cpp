#include "InputManager.h"

using namespace Hive;
InputManager::InputManager(GLFWwindow* window)
{
	InputManager::window = window;
}

InputManager::~InputManager()
{

}

void InputManager::updateProjection(glm::mat4 projection, float near_z)
{
	projection_i = glm::inverse(projection);
	InputManager::near_z = near_z;
}
void InputManager::updateView(glm::mat4 view, glm::vec3 camera_position)
{
		view_i = glm::inverse(view);
		InputManager::camera_position = camera_position;
}

bool InputManager::isKeyDown(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

glm::vec2 InputManager::getMousePosition() {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return glm::vec2(x, y);
}
glm::vec2 InputManager::getMousePositionFraction()
{
	glm::vec2 mpos = getMousePosition();
	int width = 1;
	int height = 1;

	glfwGetWindowSize(window, &width, &height);

	mpos.x = mpos.x / width;
	mpos.y = mpos.y / height;
	return mpos;
}
glm::vec2 InputManager::getMousePositionWorld()
{
	glm::vec2 screenspace = getMousePositionFraction();

	glm::vec4 clipspace = glm::vec4(
		screenspace.x * 2 - 1,
		1 - screenspace.y * 2,
		near_z,
		1
		);

	glm::vec4 viewspace = glm::normalize(projection_i * clipspace);
	viewspace.w = 0;

	glm::vec4 world_dir = glm::normalize(view_i * viewspace);
	glm::vec3 world_dir_3 = glm::vec3(world_dir.x, world_dir.y, world_dir.z);

	float dist = camera_position.y / glm::dot(world_dir_3, glm::vec3(0, -1, 0));

	glm::vec3 intersection = camera_position + world_dir_3 * dist;

	return glm::vec2(intersection.x, intersection.z);
}

bool InputManager::isMouseDown(int button)
{
	return false;
}
void InputManager::registerMouseCallback(int button, void(*callback)())
{

}
void InputManager::registerKeyCallback(int key, void(*callback)())
{

}