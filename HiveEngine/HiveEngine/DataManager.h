#pragma once

#include "IDataManager.h"
#include "DataCollection.h"

namespace Hive
{

	class DataManager : public IDataManager
	{
	private:
		DataCollection<DAbility> _dAbilities;
		DataCollection<DActor> _dActors;
		DataCollection<DBehavior> _dBehaviors;
		DataCollection<DEffect> _dEffects;
		DataCollection<DUnit> _dUnits;
		DataCollection<DValidator> _dValidators;

		DataCollection<Shader> _shaders;
		DataCollection<GLuint> _vertexShaders;
		DataCollection<GLuint> _fragmentShaders;
		DataCollection<Texture> _textures;
		DataCollection<Mesh> _meshes;
		DataCollection<Model> _models;

	public:
		DataManager();

		int loadCoreData();
		int loadXMLData(char* filename);

		DAbility* getAbilityData(int handle);
		DActor* getActorData(int handle);
		DBehavior* getBehaviorData(int handle);
		DEffect* getEffectData(int handle);
		DUnit* getUnitData(int handle);
		DValidator* getValidatorData(int handle);

		int getShaderHandle(const std::string vertexShader, const std::string fragmentShader);
		Shader* getShader(int handle);
		GLuint getVertexShader(int handle);
		GLuint getFragmentShader(int handle);

		int getModelHandle(const std::string filename);
		Model* getModel(int handle);

		Mesh* getMesh(int handle);

		int getTextureHandle(const std::string filename);
		Texture* getTexture(int handle);

		~DataManager();
	};

}