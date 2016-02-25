#include "GameWorld.h"

using namespace Hive;

GameWorld::GameWorld()
{
	map_width = 20;
	map_depth = 20;
	map = std::vector<char>(map_width * map_depth);

	scale = 1;

	srand(time(0));

	for (int i = 0; i < map_width * map_depth; ++i) map[i] = rand() % 2;

	for (int z = map_depth - 1; z >= 0; --z)
	{
		for (int x = 0; x < map_width; ++x)
		{
			fprintf(stdout, "%i,", map[get_map_index(x, z)]);
		}
		fprintf(stdout, "\n");
	}
}

GameWorld::~GameWorld()
{
}

int GameWorld::width()
{
	return map_width;
}

int GameWorld::depth()
{
	return map_depth;
}

const std::vector<char> GameWorld::grid()
{
	return map;
}

void GameWorld::load(GLuint shader)
{
	GameWorld::shader = shader;
	generate_mesh();
	MVP = glGetUniformLocation(shader, "MVP");
	M = glGetUniformLocation(shader, "M");

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);

	glm::scale(model_matrix, glm::vec3(scale, scale, scale));
}

void GameWorld::update(float delta)
{

}

void GameWorld::draw(const glm::mat4& VP)
{
	glm::mat4 matrix = VP;// *model_matrix;

	glUseProgram(shader);
	MVP = glGetUniformLocation(shader, "MVP");
	M = glGetUniformLocation(shader, "M");
	glUniformMatrix4fv(MVP, 1, GL_FALSE, &VP[0][0]);
	glUniformMatrix4fv(M, 1, GL_FALSE, &model_matrix[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
}

void GameWorld::close()
{
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteProgram(shader);
}

int GameWorld::get_vertex_index(int x, int y, int z)
{
	return y * (map_depth + 1) * (map_width + 1) + z * (map_width + 1) + x;
}

int GameWorld::get_map_index(int x, int y)
{
	return y * map_width + x;
}

void GameWorld::generate_mesh()
{
	int x, y, z, i;
	verts.resize((map_width + 1) * (map_depth + 1) * 2 * 3);
	for (y = 0; y < 2; ++y)
	{
		for (z = 0; z <= map_depth; ++z)
		{
			for (x = 0; x <= map_width; ++x)
			{
				i = get_vertex_index(x, y, z) * 3;
				verts[i++] = x;
				verts[i++] = y;
				verts[i++] = z;
			}
		}
	}

	for (z = 0; z < map_depth; ++z)
	{
		for (x = 0; x < map_width; ++x)
		{
			i = map[get_map_index(x, z)];

			//Make faces for this ground.
			if (i > 0)
			{
				indices.reserve(indices.size() + 6);

				indices.push_back(get_vertex_index(x, i, z));
				indices.push_back(get_vertex_index(x, i, z + 1));
				indices.push_back(get_vertex_index(x + 1, i, z + 1));

				indices.push_back(get_vertex_index(x, i, z));
				indices.push_back(get_vertex_index(x + 1, i, z + 1));
				indices.push_back(get_vertex_index(x + 1, i, z));
			}

			//Make faces for wall on west
			if (x > 0 && (y = map[get_map_index(x - 1, z)]) > i)
			{					
				indices.reserve(indices.size() + 6);

				indices.push_back(get_vertex_index(x, y, z));
				indices.push_back(get_vertex_index(x, y, z + 1));
				indices.push_back(get_vertex_index(x, i, z + 1));

				indices.push_back(get_vertex_index(x, y, z));
				indices.push_back(get_vertex_index(x, i, z + 1));
				indices.push_back(get_vertex_index(x, i, z));
			}

			//Make faces for wall on east
			if (x < map_width - 1 && (y = map[get_map_index(x + 1, z)]) > i)
			{
				indices.reserve(indices.size() + 6);

				indices.push_back(get_vertex_index(x + 1, y, z + 1));
				indices.push_back(get_vertex_index(x + 1, y, z));
				indices.push_back(get_vertex_index(x + 1, i, z));

				indices.push_back(get_vertex_index(x + 1, y, z + 1));
				indices.push_back(get_vertex_index(x + 1, i, z));
				indices.push_back(get_vertex_index(x + 1, i, z + 1));
			}

			//Make faces for wall on north
			if (z < map_depth - 1 && (y = map[get_map_index(x, z + 1)]) > i)
			{
				indices.reserve(indices.size() + 6);

				indices.push_back(get_vertex_index(x, y, z + 1));
				indices.push_back(get_vertex_index(x + 1, y, z + 1));
				indices.push_back(get_vertex_index(x + 1, i, z + 1));

				indices.push_back(get_vertex_index(x, y, z + 1));
				indices.push_back(get_vertex_index(x + 1, i, z + 1));
				indices.push_back(get_vertex_index(x, i, z + 1));
			}

			//Make faces for wall on south
			if (z > 0 && (y = map[get_map_index(x, z - 1)]) > i)
			{
				indices.reserve(indices.size() + 6);

				indices.push_back(get_vertex_index(x + 1, y, z));
				indices.push_back(get_vertex_index(x, y, z));
				indices.push_back(get_vertex_index(x, i, z));

				indices.push_back(get_vertex_index(x + 1, y, z));
				indices.push_back(get_vertex_index(x, i, z));
				indices.push_back(get_vertex_index(x + 1, i, z));
			}
		}
	}

	y = 0;
	for (z = 0; z < map_depth; ++z)
	{
		x = 0;
		i = map[get_map_index(x, z)];
		//Do West edge walls
		if (i > 0)
		{
			indices.reserve(indices.size() + 6);

			indices.push_back(get_vertex_index(x, i, z + 1));
			indices.push_back(get_vertex_index(x, i, z));
			indices.push_back(get_vertex_index(x, y, z));

			indices.push_back(get_vertex_index(x, i, z + 1));
			indices.push_back(get_vertex_index(x, y, z));
			indices.push_back(get_vertex_index(x, y, z + 1));
		}

		x = map_width - 1;
		i = map[get_map_index(x, z)];
		//Do East edge walls
		if (i > 0)
		{
			indices.reserve(indices.size() + 6);

			indices.push_back(get_vertex_index(x + 1, i, z));
			indices.push_back(get_vertex_index(x + 1, i, z + 1));
			indices.push_back(get_vertex_index(x + 1, y, z + 1));

			indices.push_back(get_vertex_index(x + 1, i, z));
			indices.push_back(get_vertex_index(x + 1, y, z + 1));
			indices.push_back(get_vertex_index(x + 1, y, z));
		}
	}
	for (x = 0; x < map_width; ++x)
	{
		z = 0;
		i = map[get_map_index(x, z)];
		//Do South edge walls
		if (i > 0)
		{
			indices.reserve(indices.size() + 6);

			indices.push_back(get_vertex_index(x, i, z));
			indices.push_back(get_vertex_index(x + 1, i, z));
			indices.push_back(get_vertex_index(x + 1, y, z));

			indices.push_back(get_vertex_index(x, i, z));
			indices.push_back(get_vertex_index(x + 1, y, z));
			indices.push_back(get_vertex_index(x, y, z));
		}

		z = map_depth - 1;
		i = map[get_map_index(x, z)];
		//Do North edge walls
		if (i > 0)
		{
			indices.reserve(indices.size() + 6);

			indices.push_back(get_vertex_index(x + 1, i, z + 1));
			indices.push_back(get_vertex_index(x, i, z + 1));
			indices.push_back(get_vertex_index(x, y, z + 1));

			indices.push_back(get_vertex_index(x + 1, i, z + 1));
			indices.push_back(get_vertex_index(x, y, z + 1));
			indices.push_back(get_vertex_index(x + 1, y, z + 1));
		}
	}

	indices.shrink_to_fit();
}