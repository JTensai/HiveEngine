#pragma once

#include <string>

#include "Data.h"
#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

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

	virtual int getModelHandle(const std::string filename) = 0;
	virtual Model* getModel(int handle) = 0;

	virtual Mesh* getMesh(int handle) = 0;

	virtual int getTextureHandle(const std::string filename) = 0;
	virtual Texture* getTexture(int handle) = 0;
};