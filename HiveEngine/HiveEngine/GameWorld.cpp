#include "GameWorld.h"
#include "Graph.h"
#include "EuclideanHeuristic.h"

using namespace Hive;

GameWorld::GameWorld()
{
	scale = 1;
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

void GameWorld::load(GLuint shader, XMLIterator map_iter, int& player_handle)
{
	//TODO, load map from map_iter
	XMLIterator iter, subiter, subsubiter;
	iter = map_iter.getChildrenOfName("Size");
	if (!iter.isValid()) throw DataErrorException("Map has no Size node.");
	subiter = iter.getChildrenOfName("X");
	if (!subiter.isValid()) throw DataErrorException("Map has no X size.");
	map_width = std::stoi(subiter.getValue());
	subiter = iter.getChildrenOfName("Y");
	if (!subiter.isValid()) throw DataErrorException("Map has no Y size.");
	map_depth = std::stoi(subiter.getValue());

	map = std::vector<char>(map_width * map_depth);

	iter = map_iter.getChildrenOfName("Terrain");
	if (!iter.isValid()) throw DataErrorException("Map has no Terrain node.");
	subiter = iter.getChildrenOfName("Row");

	int row = 0;
	while (row < map_depth)
	{
		if (!subiter.isValid()) throw DataErrorException("Map missing rows, found " + std::to_string(row) + " out of " + std::to_string(map_depth));
		std::string rowval = subiter.getValue();

		std::regex re("\\d+");
		std::sregex_iterator next(rowval.begin(), rowval.end(), re);
		std::sregex_iterator end;

		int col = 0;
		while (next != end)
		{
			std::smatch match = *next;
			map[row * map_width + col++] = std::stoi(match.str());
			next++;
		}
		if (col < map_width) throw DataErrorException("Map missing columns in row " + std::to_string(row) + ". Found " + std::to_string(col) + " out of " + std::to_string(map_width) + " expected.");

		subiter = subiter.next();
		row++;
	}

	//below is some code i was using to debug A*, please don't delete
	/*
	Graph g(map,map_width,map_depth);
	Node* goal = new Node(3, 4);
	g.pathfind_a_star(g, new Node(0, 0), goal, new EuclideanHeuristic(goal));
	*/

	std::string player_type;
	glm::vec2 player_spawn_point;

	iter = map_iter.getChildrenOfName("Player");
	if (!iter.isValid()) throw DataErrorException("Map missing Player node.");
	subiter = iter.getChildrenOfName("Spawn");
	if (!subiter.isValid()) throw DataErrorException("Map Player node missing Spawn node.");
	subsubiter = subiter.getChildrenOfName("X");
	if (!subsubiter.isValid()) throw DataErrorException("Map Player Spawn node missing X.");
	player_spawn_point.x = std::stof(subsubiter.getValue());
	subsubiter = subiter.getChildrenOfName("Y");
	if (!subsubiter.isValid()) throw DataErrorException("Map Player Spawn node missing Y.");
	player_spawn_point.y = std::stof(subsubiter.getValue());
	subiter = iter.getChildrenOfName("Unit");
	if (!subiter.isValid()) throw DataErrorException("Map Player missing Unit node.");
	player_type = subiter.getValue();

	IComponentManager* component_manager = ServiceLocator::get_component_manager();

	player_handle = component_manager->spawn_unit(player_spawn_point, DUnit::getIndex(player_type), LOCAL_PLAYER);
	component_manager->attach_player_input(player_handle);

	GameWorld::shader = shader;
	generate_mesh();
	glUseProgram(shader);
	glUniform3f(glGetUniformLocation(shader, "bg"), BG.r, BG.g, BG.b);
	glUniform3f(glGetUniformLocation(shader, "subfloor"), SUB_FLOOR.r, SUB_FLOOR.g, SUB_FLOOR.b);
	glUniform3f(glGetUniformLocation(shader, "floor"), FLOOR.r, FLOOR.g, FLOOR.b);
	glUniform3f(glGetUniformLocation(shader, "wallbase"), WALL_BASE.r, WALL_BASE.g, WALL_BASE.b);
	glUniform3f(glGetUniformLocation(shader, "walltop"), WALL_TOP.r, WALL_TOP.g, WALL_TOP.b);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);

	model_matrix = glm::scale(model_matrix, glm::vec3(scale, scale, scale));
}

void GameWorld::update(float delta)
{

}

void GameWorld::draw(const glm::mat4& VP)
{
	glm::mat4 matrix = VP * model_matrix;

	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "M"), 1, GL_FALSE, &model_matrix[0][0]);

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
	verts.resize((map_width + 1) * (map_depth + 1) * map_height * 3);
	for (y = 0; y < map_height; ++y)
	{
		for (z = 0; z <= map_depth; ++z)
		{
			for (x = 0; x <= map_width; ++x)
			{
				i = get_vertex_index(x, y, z) * 3;
				verts[i++] = x;
				verts[i++] = (y == 0) ? bottom : y - 1;
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