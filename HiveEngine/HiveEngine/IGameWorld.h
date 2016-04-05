#pragma once

#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "XMLInterface.h"
#include "Graph.h"
#include "Data.h"

namespace Hive
{
	/**
	 * Assumes 0,0,0 is the bottomleft corner of the map
	 * Y is the up axis
	 * If the world scale is 1:
	 * Y of 1 is walkable terrain for now
	 * 1,1,1 is the corner between grid spaces 0,0; 1,0; 0,1; and 1,1
	 * All the area between 0,1,0 and 1,1,1 is the space of grid 0,0
	 */
	class IGameWorld
	{
	public:
		virtual int width() = 0;
		virtual int depth() = 0;
		virtual int get_map_index(int x, int y) = 0;
		virtual const std::vector<char>& grid() = 0;

		virtual const glm::vec3& ambient() = 0;
		virtual const glm::vec4& light() = 0;
		virtual const glm::vec3& light_direction() = 0;
		virtual const glm::vec3& background() = 0;

		virtual Graph* get_nav_mesh() = 0;

		virtual void load(GLuint shader, XMLIterator map_iter, UnitHandle& player_unit_handle) = 0;
		virtual void update(float delta) = 0;
		virtual void draw(const glm::mat4& VP) = 0;
		virtual void close() = 0;

		IGameWorld() {}
		virtual ~IGameWorld() {}
	};

}