#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <glm/vec3.hpp>
#include <tiny_obj_loader.h>

#include <stdio.h>
#include <iostream>

namespace Hive
{

	class TempModel {
	private:
		float * _fVertData = 0;
		unsigned short * _iIndexData = 0;
		float * _fNormalData = 0;
		int _iNumVerts = 0;
		int _iNumIndices = 0;
		int _iNumTriangles = 0;
		GLuint _iVBO = 0; //Vertex Buffer Object
		GLuint _iNBO = 0; //Normal Buffer Object
		GLuint _iIBO = 0; //Index Buffer Object

	public:
		TempModel();
		TempModel(const char* objFilename);
		~TempModel();
		void draw();
	};

}