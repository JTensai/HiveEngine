#pragma once
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <glm/vec3.hpp>
#include <tiny_obj_loader.h>
#include <stdio.h>
#include <iostream>


class Model {
private:
	float * _fVertData;
	unsigned short * _iIndexData;
	float * _fNormalData;
	int _iNumVerts;
	int _iNumIndices;
	int _iNumTriangles;
	GLuint _iVBO; //Vertex Buffer Object
	GLuint _iNBO; //Normal Buffer Object
	GLuint _iIBO; //Index Buffer Object

public:
	Model(const char* objFilename);
	~Model();
	void draw();
};