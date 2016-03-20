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
		static std::vector<Mesh*> meshes;
		Mesh(const tinyobj::mesh_t& mesh);

		std::vector<float> data;
		int num_verts;
		std::vector<unsigned short> indices;

		GLuint VBO; //Vertex Buffer Object
		GLuint IBO; //Index Buffer Object

	public:
		static Mesh* get_mesh(int index);
		static int new_mesh(const tinyobj::mesh_t& mesh);
		static void set_vertex_attributes();
		void bind();
		void draw() { glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0); }

		~Mesh();
	};
}