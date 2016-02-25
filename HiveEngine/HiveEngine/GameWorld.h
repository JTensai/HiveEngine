#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "IGameWorld.h"
#include "game.h"

namespace Hive
{

	class GameWorld : public IGameWorld
	{
	private:
		const int map_height = 4;
		const int bottom = -2;

		int map_width;
		int map_depth;
		std::vector<char> map;
		std::vector<float> verts;
		std::vector<unsigned short> indices;

		GLuint shader;
		GLuint MVP;
		GLuint M;
		GLuint VBO;
		GLuint IBO;

		glm::mat4 model_matrix;
		float scale;

		void generate_mesh();
		inline int get_vertex_index(int x, int y, int z);
		inline int get_map_index(int x, int y);

	public:
		GameWorld();
		~GameWorld();

		int width();
		int depth();
		const std::vector<char> grid();
		void load(GLuint shader);
		void update(float delta);
		void draw(const glm::mat4& VP);
		void close();
	};

}