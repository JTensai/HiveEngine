#include "Mesh.h"

using namespace Hive;

Mesh::Mesh(const tinyobj::mesh_t& mesh, int mat_id)
{
	int index;
	Mesh::mat_id = mat_id;

	if (mesh.positions.size() % 3 != 0) throw AssetLoadException("Position data incomplete.");
	if (mesh.texcoords.size() % 2 != 0) throw AssetLoadException("UV data incomplete.");
	if (mesh.normals.size() % 2 != 0) throw AssetLoadException("Normal data incomplete.");
	if (mesh.indices.size() % 3 != 0) throw AssetLoadException("Index data incomplete.");

	num_verts = mesh.positions.size() / 3;
	data.resize(num_verts * (3 + 2 + 3));
	for (int vert = 0; vert < num_verts; vert++)
	{
		index = vert * (3 + 2 + 3);
		// Copy positions
		for (int i = 0; i < 3; i++)
		{
			data[index + i] = mesh.positions[vert * 3 + i];
		}
		// Copy UVs
		for (int i = 0; i < 2; i++)
		{
			if (mesh.texcoords.size() < (vert + 1) * 2)
			{
				data[index + 3 + i] = 0;
			}
			else
			{
				data[index + 3 + i] = mesh.texcoords[vert * 2 + i];
			}
		}
		// Copy normals
		for (int i = 0; i < 3; i++)
		{
			if (mesh.normals.size() < (vert + 1) * 3)
			{
				// If normal data isn't available just use the normalized position.
				data[index + 3 + 2 + i] = mesh.positions[vert * 3 + i];
			}
			else
			{
				data[index + 3 + 2 + i] = mesh.normals[vert * 3 + i];
			}
		}
	}

	indices.resize(mesh.indices.size());
	// Copy Indices
	for (int i = 0; i < mesh.indices.size(); i++)
	{
		indices[i] = mesh.indices[i];
	}

	try
	{
		Material::getItem(mat_id)->bind(); //Ensure the textures are loaded and get it in memory
	}
	catch (const AssetLoadException& e)
	{
		throw AssetLoadException("Unable to load material: " + e.err);
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw(GLuint shader_handle)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(
		0,							// Positions are at 0. No particular reason for 0, but must match the layout in the shader.
		3,							// size
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		8 * sizeof(float),			// stride
		(void*)0					// array buffer offset
		);
	glVertexAttribPointer(
		1,							// UVs are at 1
		2,							// size
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		8 * sizeof(float),			// stride
		(void*)(3 * sizeof(float))	// array buffer offset
		);
	glVertexAttribPointer(
		2,							// Normals are at 2
		3,							// size
		GL_FLOAT,					// type
		GL_TRUE,					// normalized?
		8 * sizeof(float),			// stride
		(void*)(5 * sizeof(float))	// array buffer offset
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	Material::getItem(mat_id)->bind();

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}