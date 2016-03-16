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
	char tempMap[5][5] =
	{
		{ '1','1','1','1','1' },
		{ '1','0','0','1','0' },
		{ '1','0','1','1','0' },
		{ '1','1','1','0','1' },
		{ '0','0','1','1','1' }
	};
	Graph g(tempMap);
	Node* goal = new Node(3, 4);
	g.pathfindAStar(g, new Node(0, 0), goal, new EuclideanHeuristic(goal));
	*/
}

void Game::initialize(char* XMLFilename) {
	cout << "Core XML File: \"" << XMLFilename << "\"" << endl;
	xml_filename = XMLFilename;
	if (xml_filename == NULL || xml_filename == "") {
		cout << "Didn't pass in reference to core.xml. Using default." << endl;
		xml_filename = "resources\core.xml";
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	//world_matrix = glm::scale(glm::vec3(1 / 60.f));
	world_matrix = glm::scale(glm::vec3(1));

	projection_matrix = glm::perspective(
		glm::radians(45.0f),         // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f       // Far clipping plane. Keep as little as possible.
		);

	timestep_delta = 0;

	ServiceLocator::getInstance()->registerUIManager(new UIManager());
	ServiceLocator::getInstance()->registerComponentManager(new ComponentManager());
	ServiceLocator::getInstance()->registerDataManager(new DataManager());
	ServiceLocator::getInstance()->registerGameWorld(new GameWorld());

	//ServiceLocator::getInstance()->getComponentManager()->initialize();
}


void Game::load(GLFWwindow* window) {
	glfw_window = window;
	input_manager = new InputManager(glfw_window);
	ServiceLocator::getInstance()->registerInputManager(input_manager);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS, GL_FALSE);

	glClearColor(BG.r, BG.g, BG.b, 0.0f);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	//glCullFace(GL_FRONT);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	shader_program_id = LoadShader("resources/SimpleVertexShader.vertexshader", "resources/SimpleFragmentShader.fragmentshader");
	Actor::setShader(shader_program_id);
	
	light_direction = glm::normalize(glm::vec3(1, -4, -1));
	light_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	ambient_color = glm::vec3(0.1f);

	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	try
	{
		ServiceLocator::getInstance()->getDataManager()->loadXMLData(xml_filename);
	}
	catch (DataErrorException e)
	{
		printf("Error loading data: %s\n", e.msg.c_str());
	}

	try
	{
		ServiceLocator::getInstance()->getUIManager()->load(LoadShader("resources/2DVertexShader.vertexshader", "resources/2DFragmentShader.fragmentshader"));
	}
	catch (std::exception e)
	{
		fprintf(stderr, "Error loading UIManager: %s\n", e.what());
	}

	try
	{
		ServiceLocator::getInstance()->getGameWorld()->load(LoadShader("resources/WorldVertexShader.vertexshader", "resources/WorldFragmentShader.fragmentshader"));
	}
	catch (std::exception e)
	{
		printf("Error loading map: %s\n", e.what());
	}

	IComponentManager* cm = ServiceLocator::getInstance()->getComponentManager();
	cm->load();
	player_unit_handle = cm->spawn_unit(glm::vec2(20, 25), DUnit::getIndex("BASE_UNIT"));
	Unit* u = Unit::get_component(player_unit_handle);
	player_actor_handle = u->get_actor();
	cm->attach_player_input(player_unit_handle);
}


Gamestate Game::update(float delta) {
	if (glfwGetKey(glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(glfw_window) != 0) {
		//Close if the escape key is pressed or the window was closed.
		return Gamestate::CLOSING;
	}

	ServiceLocator::getInstance()->getComponentManager()->update_free(delta, update_cache_swap_flag);

	timestep_delta += delta;
	while (timestep_delta >= TIMESTEP)
	{
		ServiceLocator::getInstance()->getComponentManager()->update_fixed(TIMESTEP, update_cache_swap_flag);
		ServiceLocator::getInstance()->getGameWorld()->update(TIMESTEP);

		timestep_delta -= TIMESTEP;
		update_cache_swap_flag = !update_cache_swap_flag;
	}

	Actor* actor = Actor::get_component(player_actor_handle);
	glm::vec3 a_pos = actor->get_position();
	camera_position = glm::vec3(a_pos.x, a_pos.y + 10, a_pos.z + 10);

	view_matrix = glm::lookAt(
		camera_position, //eye
		glm::vec3(camera_position.x, camera_position.y - .5f, camera_position.z - .5f), //look at
		glm::vec3(0, 1, 0) //up
		);

	world_view_projection = projection_matrix * view_matrix * world_matrix;

	ServiceLocator::getInstance()->getUIManager()->update(delta);

	return Gamestate::NORMAL;
}


void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ServiceLocator::getInstance()->getGameWorld()->draw(world_view_projection);
	
	glUseProgram(shader_program_id);
	GLuint LightDirection = glGetUniformLocation(shader_program_id, "LightDirection");
	GLuint LightColor = glGetUniformLocation(shader_program_id, "LightColor");
	GLuint AmbientColor = glGetUniformLocation(shader_program_id, "AmbientColor");

	glUniform3f(LightDirection, light_direction.x, light_direction.y, light_direction.z);
	glUniform4f(LightColor, light_color.r, light_color.g, light_color.b, light_color.w);
	glUniform3f(AmbientColor, ambient_color.r, ambient_color.g, ambient_color.b);

	ServiceLocator::getInstance()->getComponentManager()->draw(world_view_projection);

	//ServiceLocator::getInstance()->getUIManager()->draw();
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
