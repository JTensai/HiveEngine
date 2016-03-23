#include "game.h"
/*
#include "QuadTree.h"
#include <vector>
#include "Graph.h"
#include "Node.h"
#include "EuclideanHeuristic.h"
*/

using namespace std;
using namespace Hive;

Game::Game() {
	camera_position = glm::vec3(20, 10, 35);
	//Below is code being used to test the quadTree. Please do not delete. Testing in progress.
	/*
	QuadTree tree = QuadTree(100, 100);
	vector<glm::vec2> quadTreeTest = {glm::vec2(1,1), glm::vec2(1,2), glm::vec2(1,3), glm::vec2(1,4),
		glm::vec2(2,2), glm::vec2(2,4), glm::vec2(2,6),
		glm::vec2(3,3), glm::vec2(3,6), glm::vec2(3,9),
		glm::vec2(10, 10), glm::vec2(2, 20), glm::vec2(3, 25), glm::vec2(2, 18),
		glm::vec2(10, 40), glm::vec2(8, 48), glm::vec2(9, 53), glm::vec2(3, 60),
		glm::vec2(40, 40), glm::vec2(40, 30), glm::vec2(44, 50), glm::vec2(40, 12),
		glm::vec2(50, 7), glm::vec2(55, 32), glm::vec2(70, 3), glm::vec2(70, 20),
		glm::vec2(60, 20), glm::vec2(62, 27), glm::vec2(69, 50), glm::vec2(85, 12),
		glm::vec2(78, 60), glm::vec2(79, 90), glm::vec2(93, 9), glm::vec2(95, 35),
		glm::vec2(95, 83), glm::vec2(10, 73), glm::vec2(12, 98), glm::vec2(30, 92)};

	tree.populate_tree(quadTreeTest);
	*/
	//below is some code i was using to debug A*, please don't delete
	/*
	char temp_map[5][5] =
	{
		{ '1','1','1','1','1' },
		{ '1','0','0','1','0' },
		{ '1','0','1','1','0' },
		{ '1','1','1','0','1' },
		{ '0','0','1','1','1' }
	};
	Graph g(temp_map);
	Node* goal = new Node(3, 4);
	g.pathfind_a_star(g, new Node(0, 0), goal, new EuclideanHeuristic(goal));
	*/
}

void Game::initialize(char* core_xml_filename, char* game_xml_filename, char* map_xml_filename) {
	Game::core_xml_filename = core_xml_filename;
	Game::game_xml_filename = game_xml_filename;
	Game::map_xml_filename = map_xml_filename;

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	world_matrix = glm::scale(glm::vec3(1));

	projection_matrix = glm::perspective(
		glm::radians(45.0f),         // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f       // Far clipping plane. Keep as little as possible.
		);

	timestep_delta = 0;

	ServiceLocator::register_ui_manager(new UIManager());
	ServiceLocator::register_component_manager(new ComponentManager());
	ServiceLocator::register_data_manager(new DataManager());
	ServiceLocator::register_game_world(new GameWorld());

	ServiceLocator::get_component_manager()->initialize();
}


void Game::load(GLFWwindow* window) {
	glfw_window = window;
	input_manager = new InputManager(glfw_window);
	ServiceLocator::register_input_manager(input_manager);
	ServiceLocator::get_input_manager()->updateProjection(projection_matrix, 0.1f);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS, GL_FALSE);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	//glCullFace(GL_FRONT);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	shader_program_id = LoadShader("resources/SimpleVertexShader.vertexshader", "resources/SimpleFragmentShader.fragmentshader");
	Actor::setShader(shader_program_id);
	ServiceLocator::register_graphics(new Graphics(shader_program_id));

	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	try
	{
		ServiceLocator::get_data_manager()->loadXMLData(core_xml_filename);
		ServiceLocator::get_data_manager()->loadXMLData(game_xml_filename);
		ServiceLocator::get_data_manager()->loadXMLData(map_xml_filename);
	}
	catch (const DataErrorException& e)
	{
		printf("Error loading data: %s\n", e.msg.c_str());
		throw e;
	}

	ServiceLocator::get_component_manager()->load();

	try
	{
		ServiceLocator::get_ui_manager()->load(LoadShader("resources/2DVertexShader.vertexshader", "resources/2DFragmentShader.fragmentshader"));
	}
	catch (const Exception& e)
	{
		fprintf(stderr, "Error loading UIManager: %s\n", e.msg.c_str());
		throw e;
	}

	try
	{
		XMLInterface xml_interface(map_xml_filename);
		XMLIterator xiter = xml_interface.begin();
		XMLIterator map_iter = xiter.getChildrenOfName("Map");
		if (!map_iter.isValid()) throw DataErrorException("Map xml does not contain map node.");

		ServiceLocator::get_game_world()->load(
			LoadShader("resources/WorldVertexShader.vertexshader", "resources/WorldFragmentShader.fragmentshader"),
			map_iter,
			player_unit_handle
			);
		Unit* unit = Unit::get_component(player_unit_handle);
		player_actor_handle = unit->get_actor();
	}
	catch (const Exception& e)
	{
		printf("Error loading map: %s\n", e.msg.c_str());
		throw e;
	}

	// Code below here is temporary hackish code to get something in game until we are loading the world from XML.

	world_cursor_actor_handle = -1;
	world_cursor_actor_handle = Actor::create_component();
	printf("cursor handle %i\n", world_cursor_actor_handle);
	Actor* cursor = Actor::get_component(world_cursor_actor_handle);
	cursor->loadFromData(DActor::getIndex("QUAD_ACTOR"));
	cursor->set_rotation(glm::vec3(-glm::half_pi<float>(), 0, 0));
	cursor->set_spin(glm::vec3(0, 0, 1));
	cursor->set_scale(glm::vec3(0.5f));
}


Gamestate Game::update(float delta) {
	if (glfwGetKey(glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(glfw_window) != 0) {
		//Close if the escape key is pressed or the window was closed.
		return Gamestate::CLOSING;
	}

	ServiceLocator::get_component_manager()->update_free(delta);

	timestep_delta += delta;
	while (timestep_delta >= TIMESTEP)
	{
		ServiceLocator::get_component_manager()->update_fixed(TIMESTEP);
		ServiceLocator::get_game_world()->update(TIMESTEP);

		timestep_delta -= TIMESTEP;
	}

	Actor* actor = Actor::get_component(player_actor_handle);
	glm::vec3 actor_pos = actor->get_position();
	camera_position = glm::vec3(actor_pos.x, actor_pos.y + 10, actor_pos.z + 10);


	view_matrix = glm::lookAt(
		camera_position, //eye
		glm::vec3(camera_position.x, camera_position.y - .5f, camera_position.z - .5f), //look at
		glm::vec3(0, 1, 0) //up
		);

	ServiceLocator::get_input_manager()->updateView(view_matrix, camera_position);
	world_view_projection = projection_matrix * view_matrix * world_matrix;

	actor = Actor::get_component(world_cursor_actor_handle);
	glm::vec2 mouse_pos = ServiceLocator::get_input_manager()->getMousePositionWorld();
	actor->set_position(mouse_pos, 0.1f);

	ServiceLocator::get_ui_manager()->update(delta);

	return Gamestate::NORMAL;
}


void Game::draw() {
	glm::vec3 bg = ServiceLocator::get_game_world()->background();
	glm::vec3 light_direction = ServiceLocator::get_game_world()->light_direction();
	glm::vec4 light_color = ServiceLocator::get_game_world()->light();
	glm::vec3 ambient_color = ServiceLocator::get_game_world()->ambient();

	glClearColor(bg.r, bg.g, bg.b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ServiceLocator::get_game_world()->draw(world_view_projection);
	
	glUseProgram(shader_program_id);
	GLuint LightDirection = glGetUniformLocation(shader_program_id, "LightDirection");
	GLuint LightColor = glGetUniformLocation(shader_program_id, "LightColor");
	GLuint AmbientColor = glGetUniformLocation(shader_program_id, "AmbientColor");

	glUniform3f(LightDirection, light_direction.x, light_direction.y, light_direction.z);
	glUniform4f(LightColor, light_color.r, light_color.g, light_color.b, light_color.w);
	glUniform3f(AmbientColor, ambient_color.r, ambient_color.g, ambient_color.b);

	ServiceLocator::get_component_manager()->draw(world_view_projection);

	//ServiceLocator::getUIManager()->draw();
}


void Game::close() {
	glDeleteProgram(shader_program_id);
}

//http://www.opengl-tutorial.org/
GLuint Hive::LoadShader(const char* vertex_file_path, const char* fragment_file_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	//printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		fprintf(stderr, "%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	//printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		fprintf(stderr, "%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	//printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
