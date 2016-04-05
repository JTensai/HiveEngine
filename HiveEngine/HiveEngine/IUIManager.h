#pragma once
#include "GL\glew.h"
#include "Unit.h"

namespace Hive 
{
	class IUIManager
	{
	public:
		virtual void load(GLuint shader, UnitHandle player_unit_handle) = 0;
		virtual void update(float delta) = 0;
		virtual void draw() = 0;
		//virtual const glm::mat4& getProjectionMatrix() = 0;

		virtual ~IUIManager() {}
	};
}


