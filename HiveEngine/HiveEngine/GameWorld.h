#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <regex>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "IGameWorld.h"
#include "game.h"
#include "Exceptions.h"
#include "IComponentManager.h"
#include "ServiceLocator.h"
#include "Data.h"
#include "Graph.h"

namespace Hive
{
	struct PositionUVNormalVertex
	{
		float x, y, z;
		float u, v;
		float nx, ny, nz;
	};

	class GameWorld : public IGameWorld
	{
	private:
		int map_width;
		int map_depth;
		std::vector<char> map;
		std::vector<float> vert_data;
		std::vector<unsigned short> indices;

		Graph* nav_mesh;

		GLuint shader;
		GLuint MVP;
		GLuint M;
		GLuint VBO;
		GLuint IBO;

		glm::vec3 ambient_light_color;
		glm::vec4 directional_light_color;
		glm::vec3 directional_light_direction;

		glm::vec3 background_color;
		glm::vec3 wallbase_color;
		glm::vec3 walltop_color;

		glm::mat4 model_matrix;
		float scale;
		float map_lowest_depth;
		float map_highest_height;

		void parse_color(XMLIterator xiter, glm::vec3& color);
		void parse_position(XMLIterator xiter, glm::vec3& vec);
		void generate_mesh();
		inline int get_vertex_index(int x, int y, int z);
		inline int get_map_index(int x, int y);
		inline void push_quad(int& index);
		inline void prep_quad(int& vert_index, PositionUVNormalVertex** verts, glm::vec3 normal, glm::vec3 defaults);

	public:
		GameWorld();
		~GameWorld();

		int width();
		int depth();
		const std::vector<char> grid();

		const glm::vec3& ambient() { return ambient_light_color; }
		const glm::vec4& light() { return directional_light_color; }
		const glm::vec3& light_direction() { return directional_light_direction; }
		const glm::vec3& background() { return background_color; }

		const Graph* get_nav_mesh() { return nav_mesh; }

		void load(GLuint shader, XMLIterator map_iter, int& player_handle);
		void update(float delta);
		void draw(const glm::mat4& VP);
		void close();
	};

}