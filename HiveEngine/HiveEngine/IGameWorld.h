#pragma once

#include <glm\glm.hpp>

namespace Hive
{

	class IGameWorld
	{
	public:
		virtual int width() = 0;
		virtual int height() = 0;
		virtual const char** grid() = 0;
		virtual void update(float delta) = 0;
		virtual void draw(const glm::mat4& VP) = 0;
	};

}