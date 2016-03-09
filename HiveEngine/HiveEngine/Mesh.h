#pragma once
/*
 ***************************
 * Mesh
 * A mesh is a set of connected vertices in a model that use the same shader and texture.
 * A mesh is responsible for setting up the render environment specific to itself, and then drawing itself.
 * Functions should be exposed that will make the mesh release its GPU buffers.
 ***************************
 */

#include <stdexcept>
#include <vector>

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <tiny_obj_loader.h>

namespace Hive
{
	class Mesh {
	private:
		std::vector<float> data;
		int numVerts;
		std::vector<int> indices;

		GLuint VBO = -1; //Vertex Buffer Object
		GLuint IBO = -1; //Index Buffer Object

	public:
		Mesh(const tinyobj::mesh_t& mesh);

		void draw(const glm::mat4& WVP, GLuint shader_handle);

		~Mesh();
	};
}