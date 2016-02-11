#pragma once
/*
 ***************************
 * Model
 * A model is composed of one or more meshes.
 * One model object should exist for each model asset and every actor that needs to draw that model refers to the same model object.
 ***************************
 */

#include <vector>

#include <glm\glm.hpp>

#include "ServiceLocator.h"

namespace Hive
{

	class Model
	{
	private:
		std::vector<int> _meshHandles;

	public:
		Model();

		/*
		Draw iterates over the model's meshes and calls their draw functions, providing the world-view-perspective matrix needed to do so.
		*/
		void draw(const glm::mat4& WVP);

		~Model();
	};

}