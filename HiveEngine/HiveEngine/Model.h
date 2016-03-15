#pragma once
/*
 ***************************
 * Model
 * A model is composed of one or more meshes.
 * One model object should exist for each model asset and every actor that needs to draw that model refers to the same model object.
 ***************************
 */

#include <vector>
#include <stdio.h>
#include <iostream>
#include <stdexcept>

#include <glm\glm.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <glm/vec3.hpp>
#include <tiny_obj_loader.h>

#include "ServiceLocator.h"
#include "Data.h"
#include "Mesh.h"

namespace Hive
{
	class Model
	{
	private:
		std::vector<Mesh*> meshes;

	public:
		Model(std::string filepath, DModel* data);

		/*
		Draw iterates over the model's meshes and calls their draw functions, providing the world-view-perspective matrix needed to do so.
		*/
		void draw(GLuint shader_handle) const;

		~Model();
	};
}