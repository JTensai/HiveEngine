#include "InputManager.h"

using namespace Hive;

InputManager* InputManager::instance = nullptr;

InputManager::InputManager(GLFWwindow* window)
{
	InputManager::window = window;

	left_mouse_callbacks = std::vector<std::function<void()>>();
	right_mouse_callbacks = std::vector<std::function<void()>>();

	glfwSetMouseButtonCallback(window, &InputManager::mouseCallback);

	instance = this;
}

void InputManager::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	instance->callback(window, button, action, mods);
}
void InputManager::callback(GLFWwindow* window, int button, int action, int mods)
{
	if (window != InputManager::window) return;
	if (action != GLFW_RELEASE) return;

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_1:
		for (int i = 0; i < left_mouse_callbacks.size(); i++)
		{
			left_mouse_callbacks[i]();
		}
		break;

	case GLFW_MOUSE_BUTTON_2:
		for (int i = 0; i < right_mouse_callbacks.size(); i++)
		{
			right_mouse_callbacks[i]();
		}
		break;
	default:
		break;
	}
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
void InputManager::registerMouseCallback(int button, std::function<void()> callback)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_1:
		left_mouse_callbacks.push_back(callback);
		break;
	case GLFW_MOUSE_BUTTON_2:
		right_mouse_callbacks.push_back(callback);
		break;
	default:
		throw InputException("Unrecognized mouse button.");
	}
}
void InputManager::registerKeyCallback(int key, std::function<void()> callback)
{

}