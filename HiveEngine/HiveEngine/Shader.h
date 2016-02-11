#pragma once
/*
 ***************************
 * Shader
 * The shader class is responsible for linking its already compiled vertex and fragment shaders, loading the program onto the GPU, and retaining the handle to that program.
 ***************************
 */

#include <GL\glew.h>

namespace Hive
{

	class Shader {
	private:
		GLuint _programID;
	public:
		Shader();
		~Shader();
	};

}