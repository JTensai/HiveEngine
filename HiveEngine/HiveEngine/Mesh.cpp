#include "Mesh.h"

using namespace Hive;

Mesh::Mesh(const tinyobj::mesh_t& mesh)
{
	int index;
	numVerts = mesh.positions.size() / 3;
	data.resize(numVerts * (3 + 3 + 2));
	for (int vert = 0; vert < numVerts; vert++)
	{
		index = vert * (3 + 3 + 2);
		//Copy positions
		for (int i = 0; i < 3; i++)
		{
			data[index + i] = mesh.positions[vert * 3 + i];
		}
		//Copy normals
		for (int i = 0; i < 3; i++)
		{
			if (mesh.normals.size() < (index + 1) * 3)
			{
				data[index + 3 + i] = 0;
			}
			else
			{
				data[index + 3 + i] = mesh.normals[vert * 3 + i];
			}
		}
		//Copy UVs
		for (int i = 0; i < 2; i++)
		{
			if (mesh.texcoords.size() < (index + 1) * 2)
			{
				data[index + 3 + 3 + i] = 0;
			}
			else
			{
				data[index + 3 + 3 + i] = mesh.texcoords[vert * 2 + i];
			}
		}
	}

	indices.resize(mesh.indices.size());
	//Copy Indices
	for (int i = 0; i < mesh.indices.size(); i++)
	{
		indices[i] = mesh.indices[i];
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw(const glm::mat4& WVP, GLuint shader_handle)
{
	glEnableVertexAttribArray(0); //Position
	glEnableVertexAttribArray(1); //Normal
	glEnableVertexAttribArray(2); //UV
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
		);
	glVertexAttribPointer(
		1,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),                  // stride
		(void*)(3 * sizeof(float))            // array buffer offset
		);
	glVertexAttribPointer(
		2,                  // attribute
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),                  // stride
		(void*)(6 * sizeof(float))            // array buffer offset
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

Mesh::~Mesh()
{
	if (VBO)
	{
		glDeleteBuffers(1, &VBO);
	}

	if (IBO)
	{
		glDeleteBuffers(1, &IBO);
	}
}