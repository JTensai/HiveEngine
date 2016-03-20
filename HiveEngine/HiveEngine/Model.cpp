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

	meshes = std::vector<int>(shapes.size());
	for (int i = 0; i < shapes.size(); i++)
	{
		try
		{
			meshes[i] = Mesh::new_mesh(shapes[i].mesh);
		}
		catch (const AssetLoadException& e)
		{
			throw AssetLoadException("Error loading model from: \"" + filepath + "\"; Error occured in mesh " + std::to_string(i) + "; Err: " + e.msg);
		}
	}
}

int Model::get_num_meshes() const
{
	return meshes.size();
}

int Model::get_mesh(int mesh) const
{
	if (mesh < 0 || mesh > meshes.size()) throw std::out_of_range("Mesh out of range.");
	return meshes[mesh];
}

Model::~Model()
{
	//TODO make meshes more dynamic, right now they can't be unloaded
}