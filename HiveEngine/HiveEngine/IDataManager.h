#pragma once
/*
 ***************************
 * IDataManager
 * The data manager is responsible for loading game metadata in memory and exposing it to other systems.
 * Assets are also managed here, though this might change.
 * Currently vertex and fragment shaders should be compiled as they are referenced and only their handles are accessible to the other systems.
 * Models, meshes, and textures will also need special consideration.
 ***************************
 */

#include <string>
#include <exception>

#include "Data.h"
#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

namespace Hive
{
	//Forward declarations to prevent circular dependencies in #includes
	class Shader;
	class Model;
	class Mesh;
	class Texture;

	class IDataManager {
	public:
		virtual int loadCoreData() = 0;
		virtual int loadXMLData(char* filename) = 0;
	};

}