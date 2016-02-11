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

		virtual DAbility* getAbilityData(int handle) = 0;
		virtual DActor* getActorData(int handle) = 0;
		virtual DBehavior* getBehaviorData(int handle) = 0;
		virtual DEffect* getEffectData(int handle) = 0;
		virtual DUnit* getUnitData(int handle) = 0;
		virtual DValidator* getValidatorData(int handle) = 0;

		virtual int getShaderHandle(const std::string vertexShader, const std::string fragmentShader) = 0;
		virtual Shader* getShader(int handle) = 0;
		virtual GLuint getVertexShader(int handle) = 0;
		virtual GLuint getFragmentShader(int handle) = 0;

		virtual int getModelHandle(const std::string filename) = 0;
		virtual Model* getModel(int handle) = 0;

		virtual Mesh* getMesh(int handle) = 0;

		virtual int getTextureHandle(const std::string filename) = 0;
		virtual Texture* getTexture(int handle) = 0;
	};

}