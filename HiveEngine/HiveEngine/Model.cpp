#include "Model.h"

using namespace Hive;

Model::Model()
{
}

Model::Model(std::string filepath)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(shapes, materials, err, filepath.c_str());

	if (!err.empty())
	{
		throw std::exception(("Error loading model from: "+filepath+"; Err: "+err).c_str());
	}

	meshes = std::vector<Mesh*>(shapes.size());
	for (int i = 0; i < shapes.size(); i++)
	{
		meshes[i] = new Mesh(shapes[i].mesh);
	}
}

void Model::draw(GLuint shader_handle) const
{
	for (int i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->draw(shader_handle);
	}
}

Model::~Model()
{
	for (int i = 0; i < meshes.size(); ++i)
	{
		if (meshes[i] != nullptr)
		{
			delete meshes[i];
		}
	}
}