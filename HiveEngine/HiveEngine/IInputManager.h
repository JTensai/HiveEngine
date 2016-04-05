#pragma once
/*
 ***************************
 * Input Manager
 * The input manager is responsible for providing a unified interface whereby all other systems may gain access to user input, whether that means polling or registering callback functions.
 * It will be necessary for some systems, like UI, to consume some input so that it is not seen by later systems.
 ***************************
 */

#include <functional>

#include <glm/glm.hpp>

namespace Hive
{

	class IInputManager {
	public:
		virtual void updateProjection(glm::mat4 projection, float near_z) = 0;
		virtual void updateView(glm::mat4 view, glm::vec3 camera_position) = 0;
		virtual bool isKeyDown(int key) = 0;
		virtual glm::vec2 getMousePosition() = 0;
		virtual glm::vec2 getMousePositionFraction() = 0;
		virtual glm::vec2 getMousePositionWorld() = 0;
		virtual bool isMouseDown(int button) = 0;
		virtual void registerMouseCallback(int button, std::function<void()> callback) = 0;
		virtual void registerKeyCallback(int key, std::function<void()> callback) = 0;

		virtual ~IInputManager() {}
	};

}