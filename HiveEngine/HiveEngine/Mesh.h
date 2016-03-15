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

#include "Asset.h"
#include "Data.h"
#include "Material.h"

namespace Hive
{
	class Mesh {
	private:
		std::vector<float> data;
		int num_verts;
		std::vector<unsigned short> indices;

		int mat_id;

		GLuint VBO; //Vertex Buffer Object
		GLuint IBO; //Index Buffer Object

	public:
		Mesh(const tinyobj::mesh_t& mesh, int mat_id);

		void draw(GLuint shader_handle);

		~Mesh();
	};
}