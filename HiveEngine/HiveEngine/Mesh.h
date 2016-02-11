#pragma once
/*
 ***************************
 * Mesh
 * A mesh is a set of connected vertices in a model that use the same shader and texture.
 * A mesh is responsible for setting up the render environment specific to itself, and then drawing itself.
 * Functions should be exposed that will make the mesh release its GPU buffers.
 ***************************
 */

#include <vector>

#include <gl\glew.h>
#include <glm\glm.hpp>

namespace Hive
{

	class Mesh {
	private:
		std::vector<float> _data;
		int _numVerts;
		std::vector<int> _indices;

		int _shaderHandle;
		int _textureHandle;
		GLuint _VBO; //Vertex Buffer Object
		GLuint _IBO; //Index Buffer Object

		/*
		LoadBuffers should claim a vertex buffer and an index buffer on the GPU and then fill them with its data.
		return 0 on success, 1 on error
		*/
		int _loadBuffers();

	public:
		Mesh();

		/*
		draw should check that the buffers are valid, if not call _loadBuffers,
		it then tells OpenGL to use its shader,
		sets the necessary parameters on the shader,
		and finally tells OpenGL to draw _indices.size / 3 triangles.
		*/
		void draw(const glm::mat4& WVP);

		~Mesh();
	};

}