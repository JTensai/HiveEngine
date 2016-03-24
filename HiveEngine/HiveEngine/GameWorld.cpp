#include "GameWorld.h"
//#include "Graph.h"
//#include "EuclideanHeuristic.h"

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
	XMLIterator iter, subiter, subsubiter, sssiter;
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

	iter = map_iter.getChildrenOfName("Depth");
	if (!iter.isValid()) throw DataErrorException("Map missing Depth node.");
	map_lowest_depth = std::stof(iter.getValue());

	iter = map_iter.getChildrenOfName("Height");
	if (!iter.isValid()) throw DataErrorException("Map missing Height node.");
	map_highest_height = std::stof(iter.getValue());

#pragma region Lighting
	iter = map_iter.getChildrenOfName("Lighting");
	if (!iter.isValid()) throw DataErrorException("Map missing Lighting node.");
	subiter = iter.getChildrenOfName("Ambient");
	if (!subiter.isValid()) throw DataErrorException("Map Lighting missing Ambient node.");
	try
	{
		parse_color(subiter, ambient_light_color);
	}
	catch (const DataErrorException& e)
	{
		throw DataErrorException("Map::Lighting::Ambient::" + e.msg);
	}
	subiter = iter.getChildrenOfName("Directional");
	if (!subiter.isValid()) throw DataErrorException("Map Lighting missing Directional node.");
	try
	{
		glm::vec3 dir_temp;
		parse_color(subiter, dir_temp);
		parse_position(subiter, directional_light_direction);
		directional_light_direction = glm::normalize(directional_light_direction);

		subsubiter = subiter.getChildrenOfName("Intensity");
		if (!subsubiter.isValid()) throw DataErrorException("Missing Intensity node.");
		directional_light_color.r = dir_temp.r;
		directional_light_color.g = dir_temp.g;
		directional_light_color.b = dir_temp.b;
		directional_light_color.w = std::stof(subsubiter.getValue());
	}
	catch (const DataErrorException& e)
	{
		throw DataErrorException("Map::Lighting::Directional::" + e.msg);
	}
	subiter = iter.getChildrenOfName("Background");
	if (!subiter.isValid()) throw DataErrorException("Map Lighting missing Background node.");
	try
	{
		parse_color(subiter, background_color);
	}
	catch (const DataErrorException& e)
	{
		throw DataErrorException("Map::Lighting::Background::" + e.msg);
	}
	subiter = iter.getChildrenOfName("WallBase");
	if (!subiter.isValid()) throw DataErrorException("Map Lighting missing WallBase node.");
	try
	{
		parse_color(subiter, wallbase_color);
	}
	catch (const DataErrorException& e)
	{
		throw DataErrorException("Map::Lighting::WallBase::" + e.msg);
	}
	subiter = iter.getChildrenOfName("WallTop");
	if (!subiter.isValid()) throw DataErrorException("Map Lighting missing WallTop node.");
	try
	{
		parse_color(subiter, walltop_color);
	}
	catch (const DataErrorException& e)
	{
		throw DataErrorException("Map::Lighting::WallTop::" + e.msg);
	}
#pragma endregion
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
	

	ambient_light_color = glm::vec3(0.1f);
	directional_light_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	directional_light_direction = glm::normalize(glm::vec3(1, -4, -1));

	IComponentManager* component_manager = ServiceLocator::get_component_manager();

	player_handle = component_manager->spawn_unit(player_spawn_point, DUnit::getIndex(player_type), LOCAL_PLAYER);
	component_manager->attach_player_input(player_handle);

	GameWorld::shader = shader;
	generate_mesh();
	glUseProgram(shader);
	glUniform3f(glGetUniformLocation(shader, "background"), background_color.r, background_color.g, background_color.b);
	glUniform3f(glGetUniformLocation(shader, "wallbase"), wallbase_color.r, wallbase_color.g, wallbase_color.b);
	glUniform3f(glGetUniformLocation(shader, "walltop"), walltop_color.r, walltop_color.g, walltop_color.b);

	glUniform1f(glGetUniformLocation(shader, "depth"), -map_lowest_depth);
	glUniform1f(glGetUniformLocation(shader, "height"), map_highest_height);

	glUniform3f(glGetUniformLocation(shader, "LightDirection"), directional_light_direction.x, directional_light_direction.y, directional_light_direction.z);
	glUniform4f(glGetUniformLocation(shader, "LightColor"), directional_light_color.r, directional_light_color.g, directional_light_color.b, directional_light_color.w);
	glUniform3f(glGetUniformLocation(shader, "AmbientColor"), ambient_light_color.r, ambient_light_color.g, ambient_light_color.b);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vert_data.size() * sizeof(float), vert_data.data(), GL_STATIC_DRAW);

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
	glUniformMatrix4fv(glGetUniformLocation(shader, "WVP"), 1, GL_FALSE, &matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "W"), 1, GL_FALSE, &model_matrix[0][0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Position
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
		);
	//UV
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*) (3 * sizeof(float))
		);
	//Normal
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(5 * sizeof(float))
		);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void GameWorld::close()
{
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteProgram(shader);
}


void GameWorld::parse_color(XMLIterator xiter, glm::vec3& color)
{
	if (!xiter.isValid()) throw DataErrorException("Missing color data.");

	XMLIterator iter;

	iter = xiter.getChildrenOfName("R");
	if (!iter.isValid()) throw DataErrorException("Missing Red component.");
	color.r = std::stof(iter.getValue());

	iter = xiter.getChildrenOfName("G");
	if (!iter.isValid()) throw DataErrorException("Missing Green component.");
	color.g = std::stof(iter.getValue());

	iter = xiter.getChildrenOfName("B");
	if (!iter.isValid()) throw DataErrorException("Missing Blue component.");
	color.b = std::stof(iter.getValue());
}
void GameWorld::parse_position(XMLIterator xiter, glm::vec3& vec)
{
	if (!xiter.isValid()) throw DataErrorException("Missing position data.");

	XMLIterator iter;

	iter = xiter.getChildrenOfName("X");
	if (!iter.isValid()) throw DataErrorException("Missing X component.");
	vec.x = std::stof(iter.getValue());

	iter = xiter.getChildrenOfName("Y");
	if (!iter.isValid()) throw DataErrorException("Missing Y component.");
	vec.y = std::stof(iter.getValue());

	iter = xiter.getChildrenOfName("Z");
	if (!iter.isValid()) throw DataErrorException("Missing Z component.");
	vec.z = std::stof(iter.getValue());
}

int GameWorld::get_vertex_index(int x, int y, int z)
{
	return y * (map_depth + 1) * (map_width + 1) + z * (map_width + 1) + x;
}

int GameWorld::get_map_index(int x, int y)
{
	return y * map_width + x;
}

void GameWorld::push_quad(int& index)
{
	indices.reserve(indices.size() + 6);

	indices.push_back(index);
	indices.push_back(index + 1);
	indices.push_back(index + 2);

	indices.push_back(index + 1);
	indices.push_back(index + 3);
	indices.push_back(index + 2);

	index += 4;
}

void GameWorld::prep_quad(int& vert_index, PositionUVNormalVertex** verts, glm::vec3 normal, glm::vec3 defaults)
{
	vert_data.reserve(vert_data.size() + 4 * (3 + 2 + 3));
	vert_data.insert(vert_data.end(), 4 * (3 + 2 + 3), 0);
	float* cursor = vert_data.data();
	cursor += vert_index * (3 + 2 + 3);

	verts[0] = (PositionUVNormalVertex*) cursor;
	verts[1] = verts[0] + 1;
	verts[2] = verts[1] + 1;
	verts[3] = verts[2] + 1;
	vert_index += 4;

	verts[0]->x = defaults.x;
	verts[0]->y = defaults.y;
	verts[0]->z = defaults.z;
	verts[0]->u = 0;
	verts[0]->v = 1;
	verts[0]->nx = normal.x;
	verts[0]->ny = normal.y;
	verts[0]->nz = normal.z;

	verts[1]->x = defaults.x;
	verts[1]->y = defaults.y;
	verts[1]->z = defaults.z;
	verts[1]->u = 1;
	verts[1]->v = 1;
	verts[1]->nx = normal.x;
	verts[1]->ny = normal.y;
	verts[1]->nz = normal.z;

	verts[2]->x = defaults.x;
	verts[2]->y = defaults.y;
	verts[2]->z = defaults.z;
	verts[2]->u = 0;
	verts[2]->v = 0;
	verts[2]->nx = normal.x;
	verts[2]->ny = normal.y;
	verts[2]->nz = normal.z;

	verts[3]->x = defaults.x;
	verts[3]->y = defaults.y;
	verts[3]->z = defaults.z;
	verts[3]->u = 1;
	verts[3]->v = 0;
	verts[3]->nx = normal.x;
	verts[3]->ny = normal.y;
	verts[3]->nz = normal.z;
}

void GameWorld::generate_mesh()
{
	int x, y, z, i, bottom;
	
	int index = 0;
	int vert_index = 0;

	PositionUVNormalVertex* verts[4];

	for (z = -1; z <= map_depth; ++z)
	{
		for (x = -1; x <= map_width; ++x)
		{
			if (
				(z == -1 || z == map_depth) &&
				(x == -1 || x == map_width)
				)
			{
				//Ignore corners;
				continue;
			}

			i = 0;
			if (z >= 0 && z < map_depth && x >= 0 && x < map_width)
			{
				i = map[get_map_index(x, z)];
			}
			bottom = (i > 0) ? i - 1 : map_lowest_depth;

			//Make faces for this ground.
			if (i > 0)
			{
				float top = (i > 1) ? map_highest_height : 0;
				prep_quad(vert_index, verts, glm::vec3(0, 1, 0), glm::vec3(x, top, z));
				push_quad(index);

				verts[1]->x = x + 1;

				verts[2]->z = z + 1;

				verts[3]->x = x + 1;
				verts[3]->z = z + 1;
			}

			//Make faces for wall on west
			if (x > 0 && !(z == -1 || z == map_depth) && (y = map[get_map_index(x - 1, z)]) > i)
			{
				float top = (y > 1) ? map_highest_height : 0;
				prep_quad(vert_index, verts, glm::vec3(1, 0, 0), glm::vec3(x, bottom, z));
				push_quad(index);

				verts[0]->y = top;

				verts[1]->y = top;
				verts[1]->z = z + 1;

				verts[3]->z = z + 1;
			}

			//Make faces for wall on east
			if (x < map_width - 1 && !(z == -1 || z == map_depth) && (y = map[get_map_index(x + 1, z)]) > i)
			{
				float top = (y > 1) ? map_highest_height : 0;
				prep_quad(vert_index, verts, glm::vec3(-1, 0, 0), glm::vec3(x + 1, bottom, z));
				push_quad(index);

				verts[0]->y = top;
				verts[0]->z = z + 1;

				verts[1]->y = top;

				verts[2]->z = z + 1;
			}

			//Make faces for wall on north
			if (z > 0 && !(x == -1 || x == map_width) && (y = map[get_map_index(x, z - 1)]) > i)
			{
				float top = (y > 1) ? map_highest_height : 0;
				prep_quad(vert_index, verts, glm::vec3(0, 0, 1), glm::vec3(x, bottom, z));
				push_quad(index);

				verts[0]->y = top;

				verts[1]->y = top;
				verts[1]->x = x + 1;

				verts[3]->x = x + 1;
			}

			//Make faces for wall on south
			if (z < map_depth - 1 && !(x == -1 || x == map_width) && (y = map[get_map_index(x, z + 1)]) > i)
			{
				float top = (y > 1) ? map_highest_height : 0;
				prep_quad(vert_index, verts, glm::vec3(0, 0, -1), glm::vec3(x, bottom, z + 1));
				push_quad(index);

				verts[0]->x = x + 1;
				verts[0]->y = top;

				verts[1]->y = top;

				verts[2]->x = x + 1;
			}
		}
	}

	vert_data.shrink_to_fit();
	indices.shrink_to_fit();
}
