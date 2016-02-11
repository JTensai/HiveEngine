#include "game.h"

using namespace std;

namespace Hive {

	Game::Game() {
		_camPos = glm::vec3(0, .5, -3);
	}

	void Game::initialize(char* XMLFilename) {
		_cpXMLFilename = XMLFilename;

		glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

		_mWorldMatrix = glm::scale(glm::vec3(1 / 60.f));

		_mProjectionMatrix = glm::perspective(
			glm::radians(45.0f),         // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
			4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
			0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
			100.0f       // Far clipping plane. Keep as little as possible.
			);

		ServiceLocator::getInstance()->registerComponentManager(new ComponentManager());
		ServiceLocator::getInstance()->registerDataManager(new DataManager());
	}


	void Game::load(GLFWwindow* window) {
		_wpWindow = window;
		_inputManager = new InputManager(_wpWindow);
		ServiceLocator::getInstance()->registerInputManager(_inputManager);
		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(_wpWindow, GLFW_STICKY_KEYS, GL_FALSE);

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		_iProgramID = LoadShader("resources/SimpleVertexShader.vertexshader", "resources/SimpleFragmentShader.fragmentshader");
		glUseProgram(_iProgramID);
		_iMatrixID = glGetUniformLocation(_iProgramID, "MVP");
		_iViewMatrixID = glGetUniformLocation(_iProgramID, "V");
		_iWorldMatrixID = glGetUniformLocation(_iProgramID, "M");

		glm::vec3 lightPos = glm::vec3(4, 4, 4);
		GLuint LightID = glGetUniformLocation(_iProgramID, "LightPosition_worldspace");
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);


		/*tinyxml2::XMLDocument doc;
		doc.LoadFile(_cpXMLFilename);

		tinyxml2::XMLElement* root_element;
		root_element = doc.RootElement();

		tinyxml2::XMLElement* unit = root_element->FirstChildElement();
		tinyxml2::XMLElement* name = unit->FirstChildElement();
		tinyxml2::XMLElement* unitModel = name->NextSiblingElement();

		_mpModel = new TempModel(unitModel->Attribute("value"));*/

		_mpModel = new TempModel("resources/teapot.obj");

		glGenVertexArrays(1, &_iVertexArrayID);
		glBindVertexArray(_iVertexArrayID);

		ServiceLocator::getInstance()->getDataManager()->loadCoreData();
		ServiceLocator::getInstance()->getDataManager()->loadXMLData(_cpXMLFilename);
	}


	int Game::update(float delta) {
		//bool tmp = glfwGetKey(_wpWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS;
		//tmp = glfwWindowShouldClose(_wpWindow) == 0;
		if (glfwGetKey(_wpWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(_wpWindow) != 0) {
			//Close if the escape key is pressed or the window was closed.
			return HE_GAMESTATE_CLOSING;
		}
		//_fCamRotation += delta;
		glm::vec3 _movDir = glm::vec3(0);
		if (ServiceLocator::getInstance()->getInputManager()->isKeyDown(GLFW_KEY_W)) {
			_movDir.z += 1.0;
		}
		if (ServiceLocator::getInstance()->getInputManager()->isKeyDown(GLFW_KEY_A)) {
			_movDir.x += 1.0;
		}
		if (ServiceLocator::getInstance()->getInputManager()->isKeyDown(GLFW_KEY_S)) {
			_movDir.z -= 1.0;
		}
		if (ServiceLocator::getInstance()->getInputManager()->isKeyDown(GLFW_KEY_D)) {
			_movDir.x -= 1.0;
		}

		//cout << "length: " << _movDir.length() << endl;
		if (glm::length(_movDir) != 0) {
			//cout << "Before X: " << _movDir.x << " Y: " << _movDir.y << " Z: " << _movDir.z << endl;
			_movDir = glm::normalize(_movDir);
			//cout << "AFter  X: " << _movDir.x << " Y: " << _movDir.y << " Z: " << _movDir.z << endl;
			_movDir *= delta * 5;
			_camPos += _movDir;
		}



		_mViewMatrix = glm::lookAt(
			//glm::vec3(3 * glm::cos(_fCamRotation), .5, 3 * glm::sin(_fCamRotation)), //Camera position
			//InputManager::getInstance()->getCameraPosition(),
			//InputManager::getInstance()->getCameraLookAtPosition(), //Camera target (position where the camera is looking at)
			_camPos,
			glm::vec3(0, .25, 0),
			glm::vec3(0, 1, 0)
			);

		_mWVP = _mProjectionMatrix * _mViewMatrix * _mWorldMatrix;

		ServiceLocator::getInstance()->getComponentManager()->update(delta);

		return HE_GAMESTATE_NORMAL;
	}


	void Game::draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(_iMatrixID, 1, GL_FALSE, &_mWVP[0][0]);
		glUniformMatrix4fv(_iWorldMatrixID, 1, GL_FALSE, &_mWorldMatrix[0][0]);
		glUniformMatrix4fv(_iViewMatrixID, 1, GL_FALSE, &_mViewMatrix[0][0]);

		ServiceLocator::getInstance()->getComponentManager()->draw(_mWVP);

		_mpModel->draw();
	}


	void Game::close() {
		delete _mpModel;
		glDeleteVertexArrays(1, &_iVertexArrayID);
		glDeleteProgram(_iProgramID);
	}

	//http://www.opengl-tutorial.org/
	GLuint LoadShader(const char * vertex_file_path, const char * fragment_file_path) {
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
		printf("Compiling shader : %s\n", vertex_file_path);
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}

		// Compile Fragment Shader
		printf("Compiling shader : %s\n", fragment_file_path);
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}

		// Link the program
		printf("Linking program\n");
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}

		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return ProgramID;
	}

}