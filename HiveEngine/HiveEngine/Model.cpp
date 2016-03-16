#include "Model.h"

using namespace Hive;

Model::Model(std::string filepath, DModel* data)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;

	if (!tinyobj::LoadObj(shapes, materials, err, filepath.c_str()))
	{
		throw AssetLoadException("Error loading model from: \"" + filepath + "\"; Err: " + err);
	}

	int missing_mat = Material::getIndex("MISSING_MATERIAL");
	meshes = std::vector<Mesh*>(shapes.size());
	for (int i = 0; i < shapes.size(); i++)
	{
		try
		{
			int mat_id;
			if (data->mesh_mat_handles.size() <= i)
			{
				mat_id = missing_mat;
			}
			else
			{
				mat_id = data->mesh_mat_handles[i];
			}

			meshes[i] = new Mesh(shapes[i].mesh, mat_id);
		}
		catch (const AssetLoadException& e)
		{
			throw AssetLoadException("Error loading model from: \"" + filepath + "\"; Error occured in mesh " + std::to_string(i) + "; Err: " + e.msg);
		}
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