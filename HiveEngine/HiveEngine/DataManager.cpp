#include "DataManager.h"

DataManager::DataManager()
{
}

int DataManager::loadCoreData()
{
	return 0;
}
int DataManager::loadXMLData(char* filename)
{
	return 0;
}

DAbility* DataManager::getAbilityData(int handle)
{
	return NULL;
}
DActor* DataManager::getActorData(int handle)
{
	return NULL;
}
DBehavior* DataManager::getBehaviorData(int handle)
{
	return NULL;
}
DEffect* DataManager::getEffectData(int handle)
{
	return NULL;
}
DUnit* DataManager::getUnitData(int handle)
{
	return NULL;
}
DValidator* DataManager::getValidatorData(int handle)
{
	return NULL;
}

int DataManager::getShaderHandle(const std::string vertexShader, const std::string fragmentShader)
{
	return 0;
}
Shader* DataManager::getShader(int handle)
{
	return NULL;
}

int DataManager::getModelHandle(const std::string filename)
{
	return 0;
}
Model* DataManager::getModel(int handle)
{
	return NULL;
}

Mesh* DataManager::getMesh(int handle)
{
	return NULL;
}

int DataManager::getTextureHandle(const std::string filename)
{
	return 0;
}
Texture* DataManager::getTexture(int handle)
{
	return NULL;
}

DataManager::~DataManager()
{
}