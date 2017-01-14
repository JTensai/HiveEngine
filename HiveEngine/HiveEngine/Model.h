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
#include <glm/vec3.hpp>
#include <tiny_obj_loader.h>

#include "Data.h"
#include "ServiceLocator.h"
#include "Mesh.h"

namespace Hive
{
	class Model
	{
	private:
		std::vector<MeshHandle> meshes;

	public:
		Model(std::string filepath);

		int get_num_meshes() const;
		MeshHandle get_mesh(int mesh) const;

		~Model();
	};
}