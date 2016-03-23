#include "DataManager.h"
#include "ParticleSystemData.h"

using namespace Hive;

DataManager::DataManager()
{
}

int DataManager::loadCoreData()
{
	return loadXMLData("resources/core.xml");
}
int DataManager::loadXMLData(char* filename)
{
	try
	{
		XMLInterface xi(filename);

		xmlFirstPass(xi);
		xmlSecondPass(xi);
	}
	catch (DataErrorException e)
	{
		throw DataErrorException(std::string(filename) + ": " + e.msg);
	}

	return 0;
}

DataManager::~DataManager()
{
}

void DataManager::xmlFirstPass(XMLInterface& xmlif)
{
	using std::placeholders::_1;

	XMLIterator root = xmlif.begin();

	if (!root.isValid()) throw DataErrorException("Root invalid.");

	root.forEachChildOfName("Ability", std::bind(&DataManager::xmlFirstPassAbilities, this, _1));
	root.forEachChildOfName("Actor", std::bind(&DataManager::xmlFirstPassActors, this, _1));
	root.forEachChildOfName("Behavior", std::bind(&DataManager::xmlFirstPassBehaviors, this, _1));

	root.forEachChildOfName("EffectModifyUnit", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
	root.forEachChildOfName("EffectSearch", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
	root.forEachChildOfName("EffectSet", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
	root.forEachChildOfName("EffectSetBehavior", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
	root.forEachChildOfName("EffectSpawnUnit", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
	root.forEachChildOfName("EffectSwitch", std::bind(&DataManager::xmlFirstPassEffect, this, _1));

	root.forEachChildOfName("Texture", std::bind(&DataManager::xmlFirstPassTextures, this, _1));
	root.forEachChildOfName("Material", std::bind(&DataManager::xmlFirstPassMaterials, this, _1));
	root.forEachChildOfName("Model", std::bind(&DataManager::xmlFirstPassModels, this, _1));
	root.forEachChildOfName("Unit", std::bind(&DataManager::xmlFirstPassUnits, this, _1));

	root.forEachChildOfName("ValidatorBehaviorCount", std::bind(&DataManager::xmlFirstPassValidator, this, _1));
	root.forEachChildOfName("ValidatorCombine", std::bind(&DataManager::xmlFirstPassValidator, this, _1));
	root.forEachChildOfName("ValidatorCompareVital", std::bind(&DataManager::xmlFirstPassValidator, this, _1));
	root.forEachChildOfName("ValidatorCondition", std::bind(&DataManager::xmlFirstPassValidator, this, _1));
	root.forEachChildOfName("ValidatorLocationRange", std::bind(&DataManager::xmlFirstPassValidator, this, _1));
	root.forEachChildOfName("ValidatorLocationPathable", std::bind(&DataManager::xmlFirstPassValidator, this, _1));
	root.forEachChildOfName("ValidatorFilterUnit", std::bind(&DataManager::xmlFirstPassValidator, this, _1));
	root.forEachChildOfName("ValidatorValidatorPlayer", std::bind(&DataManager::xmlFirstPassValidator, this, _1));

	root.forEachChildOfName("ParticleSystem", std::bind(&DataManager::xmlFirstPassParticleSystem, this, _1));
	root.forEachChildOfName("ParticleEmitter", std::bind(&DataManager::xmlFirstPassParticleEmitter, this, _1));
	// modules...
	root.forEachChildOfName("ModuleSizeOverLife", std::bind(&DataManager::xmlFirstPassModuleSizeOverLife, this, _1));
	root.forEachChildOfName("ModuleColorOverLife", std::bind(&DataManager::xmlFirstPassModuleColorOverLife, this, _1));
	root.forEachChildOfName("ModuleInitialRotation", std::bind(&DataManager::xmlFirstPassModuleInitialRotation, this, _1));
	root.forEachChildOfName("ModuleInitialRotationRate", std::bind(&DataManager::xmlFirstPassModuleInitialRotationRate, this, _1));
	root.forEachChildOfName("ModuleSubImageIndexOverLife", std::bind(&DataManager::xmlFirstPassModuleSubImageIndexOverLife, this, _1));
	root.forEachChildOfName("ModuleSubImageIndexRandom", std::bind(&DataManager::xmlFirstPassModuleSubImageIndexRandom, this, _1));
}

void DataManager::xmlFirstPassAbilities(XMLIterator xmliter)
{
	DAbility ability;
	std::string id = xmliter.getID();
	DAbility::addItem(id, ability);
}
void DataManager::xmlFirstPassActors(XMLIterator xmliter)
{
	DActor actor;
	std::string id = xmliter.getID();
	DActor::addItem(id, actor);
}
void DataManager::xmlFirstPassBehaviors(XMLIterator xmliter)
{
	DBehavior behavior;
	std::string id = xmliter.getID();
	DBehavior::addItem(id, behavior);
}

void DataManager::xmlFirstPassEffect(XMLIterator xmliter)
{
	DEffect effect;
	std::string id = xmliter.getID();
	DEffect::addItem(id, effect);
}

void DataManager::xmlFirstPassTextures(XMLIterator xmliter)
{
	DTexture texture;
	std::string id = xmliter.getID();
	DTexture::addItem(id, texture);
}
void DataManager::xmlFirstPassMaterials(XMLIterator xmliter)
{
	DMaterial mat;
	std::string id = xmliter.getID();
	DMaterial::addItem(id, mat);
}
void DataManager::xmlFirstPassModels(XMLIterator xmliter)
{
	DModel model;
	std::string id = xmliter.getID();
	DModel::addItem(id, model);
}
void DataManager::xmlFirstPassUnits(XMLIterator xmliter)
{
	DUnit unit;
	std::string id = xmliter.getID();
	DUnit::addItem(id, unit);
}

void DataManager::xmlFirstPassValidator(XMLIterator xmliter)
{
	DValidator validator;
	std::string id = xmliter.getID();
	DValidator::addItem(id, validator);
}

void DataManager::xmlFirstPassParticleSystem(XMLIterator xmliter)
{
	DParticleSystem system;
	std::string id = xmliter.getID();
	DParticleSystem::addItem(id, system);
}
void DataManager::xmlFirstPassParticleEmitter(XMLIterator xmliter)
{
	DParticleEmitter emitter;
	std::string id = xmliter.getID();
	DParticleEmitter::addItem(id, emitter);
}
//modules...
void DataManager::xmlFirstPassModuleSizeOverLife(XMLIterator xmliter)
{
	DModuleSizeOverLife module;
	std::string id = xmliter.getID();
	DModuleSizeOverLife::addItem(id, module);
}
void DataManager::xmlFirstPassModuleColorOverLife(XMLIterator xmliter)
{
	DModuleColorOverLife module;
	std::string id = xmliter.getID();
	DModuleColorOverLife::addItem(id, module);
}
void DataManager::xmlFirstPassModuleInitialRotation(XMLIterator xmliter)
{
	DModuleInitialRotation module;
	std::string id = xmliter.getID();
	DModuleInitialRotation::addItem(id, module);
}
void DataManager::xmlFirstPassModuleInitialRotationRate(XMLIterator xmliter)
{
	DModuleInitialRotationRate module;
	std::string id = xmliter.getID();
	DModuleInitialRotationRate::addItem(id, module);
}
void DataManager::xmlFirstPassModuleSubImageIndexOverLife(XMLIterator xmliter)
{
	DModuleSubImageIndexOverLife module;
	std::string id = xmliter.getID();
	DModuleSubImageIndexOverLife::addItem(id, module);
}
void DataManager::xmlFirstPassModuleSubImageIndexRandom(XMLIterator xmliter)
{
	DModuleSubImageIndexRandom module;
	std::string id = xmliter.getID();
	DModuleSubImageIndexRandom::addItem(id, module);
}

void DataManager::xmlSecondPass(XMLInterface& xmlif)
{
	using std::placeholders::_1;

	XMLIterator root = xmlif.begin();

	root.forEachChildOfName("Ability", std::bind(&DataManager::xmlSecondPassAbilities, this, _1));
	root.forEachChildOfName("Actor", std::bind(&DataManager::xmlSecondPassActors, this, _1));
	root.forEachChildOfName("Behavior", std::bind(&DataManager::xmlSecondPassBehaviors, this, _1));

	root.forEachChildOfName("EffectModifyUnit", std::bind(&DataManager::xmlSecondPassEffectModifyUnit, this, _1));
	root.forEachChildOfName("EffectSearch", std::bind(&DataManager::xmlSecondPassEffectSearch, this, _1));
	root.forEachChildOfName("EffectSet", std::bind(&DataManager::xmlSecondPassEffectSet, this, _1));
	root.forEachChildOfName("EffectSetBehavior", std::bind(&DataManager::xmlSecondPassEffectSetBehavior, this, _1));
	root.forEachChildOfName("EffectSpawnUnit", std::bind(&DataManager::xmlSecondPassEffectSpawnUnit, this, _1));
	root.forEachChildOfName("EffectSwitch", std::bind(&DataManager::xmlSecondPassEffectSwitch, this, _1));

	root.forEachChildOfName("Texture", std::bind(&DataManager::xmlSecondPassTextures, this, _1));
	root.forEachChildOfName("Material", std::bind(&DataManager::xmlSecondPassMaterials, this, _1));
	root.forEachChildOfName("Model", std::bind(&DataManager::xmlSecondPassModels, this, _1));
	root.forEachChildOfName("Unit", std::bind(&DataManager::xmlSecondPassUnits, this, _1));

	root.forEachChildOfName("ValidatorBehaviorCount", std::bind(&DataManager::xmlSecondPassValidatorBehaviorCount, this, _1));
	root.forEachChildOfName("ValidatorCombine", std::bind(&DataManager::xmlSecondPassValidatorCombine, this, _1));
	root.forEachChildOfName("ValidatorCompareVital", std::bind(&DataManager::xmlSecondPassValidatorCompareVital, this, _1));
	root.forEachChildOfName("ValidatorCondition", std::bind(&DataManager::xmlSecondPassValidatorCondition, this, _1));
	root.forEachChildOfName("ValidatorLocationRange", std::bind(&DataManager::xmlSecondPassValidatorLocationRange, this, _1));
	root.forEachChildOfName("ValidatorLocationPathable", std::bind(&DataManager::xmlSecondPassValidatorLocationPathable, this, _1));
	root.forEachChildOfName("ValidatorFilterUnit", std::bind(&DataManager::xmlSecondPassValidatorFilterUnit, this, _1));
	root.forEachChildOfName("ValidatorValidatorPlayer", std::bind(&DataManager::xmlSecondPassValidatorPlayer, this, _1));

	root.forEachChildOfName("ParticleSystem", std::bind(&DataManager::xmlSecondPassParticleSystem, this, _1));
	root.forEachChildOfName("ParticleEmitter", std::bind(&DataManager::xmlSecondPassParticleEmitter, this, _1));
	// modules...
	root.forEachChildOfName("ModuleSizeOverLife", std::bind(&DataManager::xmlSecondPassModuleSizeOverLife, this, _1));
	root.forEachChildOfName("ModuleColorOverLife", std::bind(&DataManager::xmlSecondPassModuleColorOverLife, this, _1));
	root.forEachChildOfName("ModuleInitialRotation", std::bind(&DataManager::xmlSecondPassModuleInitialRotation, this, _1));
	root.forEachChildOfName("ModuleInitialRotationRate", std::bind(&DataManager::xmlSecondPassModuleInitialRotationRate, this, _1));
	root.forEachChildOfName("ModuleSubImageIndexOverLife", std::bind(&DataManager::xmlSecondPassModuleSubImageIndexOverLife, this, _1));
	root.forEachChildOfName("ModuleSubImageIndexRandom", std::bind(&DataManager::xmlSecondPassModuleSubImageIndexRandom, this, _1));
}

void DataManager::xmlSecondPassAbilities(XMLIterator xmliter)
{
	DAbility* ability;
	try
	{
		copyParent<DAbility>(xmliter, &ability);

		XMLIterator iter;
#pragma region Type
		iter = xmliter.getChildrenOfName("Type");
		if (iter.isValid())
		{
			std::string val = iter.getValue();
			if (!val.compare("INSTANT")) //If they are the same the function retuns 0
			{
				ability->type = AbilityType::INSTANT;
			}
			else if (!val.compare("POINT_TARGET"))
			{
				ability->type = AbilityType::POINT_TARGET;
			}
			else if (!val.compare("UNIT_TARGET"))
			{
				ability->type = AbilityType::UNIT_TARGET;
			}
			else
			{
				throw DataErrorException("Unkown ability type value encountered: " + val);
			}
		}
#pragma endregion

		iter = xmliter.getChildrenOfName("Name");
		if (iter.isValid()) ability->name = iter.getValue();

		iter = xmliter.getChildrenOfName("Tooltip");
		if (iter.isValid()) ability->tooltip = iter.getValue();

		iter = xmliter.getChildrenOfName("Icon");
		linkData<DTexture>(iter, &ability->iconTextureHandle);

		iter = xmliter.getChildrenOfName("Cost");
		xmlParseCost(iter, &ability->cost);

		iter = xmliter.getChildrenOfName("Effects");
		xmlParseEffectList(iter, &ability->effects);

		iter = xmliter.getChildrenOfName("Range");
		if (iter.isValid()) ability->range = std::stof(iter.getValue());

		iter = xmliter.getChildrenOfName("TargetFilter");
		xmlParseUnitFilter(iter, &ability->targetFilter);
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Ability(" + xmliter.getID() + ")::" + e.msg);
	}
}

void DataManager::xmlSecondPassActors(XMLIterator xmliter)
{
	DActor* actor;
	try
	{
		copyParent<DActor>(xmliter, &actor);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("Model");
		linkData<DModel>(iter, &actor->dModelHandle);

		iter = xmliter.getChildrenOfName("Material");
		linkData<DMaterial>(iter, &actor->dMaterialHandle);
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Actor(" + xmliter.getID() + ")::" + e.msg);
	}
}
void DataManager::xmlSecondPassBehaviors(XMLIterator xmliter) {}

void DataManager::xmlSecondPassEffectModifyUnit(XMLIterator xmliter) {}
void DataManager::xmlSecondPassEffectSearch(XMLIterator xmliter) {}
void DataManager::xmlSecondPassEffectSet(XMLIterator xmliter) {}
void DataManager::xmlSecondPassEffectSetBehavior(XMLIterator xmliter) {}
void DataManager::xmlSecondPassEffectSpawnUnit(XMLIterator xmliter) {}
void DataManager::xmlSecondPassEffectSwitch(XMLIterator xmliter) {}

void DataManager::xmlSecondPassTextures(XMLIterator xmliter)
{
	DTexture* texture;
	try
	{
		copyParent<DTexture>(xmliter, &texture);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("File");
		if (iter.isValid()) texture->setFilepath(iter.getValue());
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Texture(" + xmliter.getID() + ")::" + e.msg);
	}
}
void DataManager::xmlSecondPassMaterials(XMLIterator xmliter)
{
	DMaterial* mat;
	try
	{
		copyParent<DMaterial>(xmliter, &mat);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("DiffuseTexture");
		linkData<DTexture>(iter, &mat->diffuse_tex);
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Material(" + xmliter.getID() + ")::" + e.msg);
	}
}
void DataManager::xmlSecondPassModels(XMLIterator xmliter)
{
	DModel* model;
	try
	{
		copyParent<DModel>(xmliter, &model);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("File");
		if (iter.isValid()) model->setFilepath(iter.getValue());
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Model(" + xmliter.getID() + ")::" + e.msg);
	}
}
void DataManager::xmlSecondPassUnits(XMLIterator xmliter)
{
	DUnit* unit;
	try
	{
		copyParent<DUnit>(xmliter, &unit);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("VitalMax");
		xmlParseVitals(iter, &unit->vitalMax);

		iter = xmliter.getChildrenOfName("VitalRegen");
		xmlParseVitals(iter, &unit->vitalRegen);

		iter = xmliter.getChildrenOfName("Speed");
		if (iter.isValid()) { unit->speed = std::stof(iter.getValue()); }

		iter = xmliter.getChildrenOfName("Attributes");
		xmlParseAttributes(iter, &unit->attributes);

		iter = xmliter.getChildrenOfName("Actor");
		linkData<DActor>(iter, &unit->actorDataHandle);

		iter = xmliter.getChildrenOfName("Height");
		if (iter.isValid()) { unit->height = std::stof(iter.getValue()); }

		iter = xmliter.getChildrenOfName("Abilities");
		xmlParseAbilityList(iter, &unit->abilityHandles);

		iter = xmliter.getChildrenOfName("Behaviors");
		xmlParseAbilityList(iter, &unit->behaviorHandles);
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Unit(" + xmliter.getID() + ")::" + e.msg);
	}
}

void DataManager::xmlSecondPassValidatorBehaviorCount(XMLIterator xmliter) {}
void DataManager::xmlSecondPassValidatorCombine(XMLIterator xmliter) {}
void DataManager::xmlSecondPassValidatorCompareVital(XMLIterator xmliter) {}
void DataManager::xmlSecondPassValidatorCondition(XMLIterator xmliter) {}
void DataManager::xmlSecondPassValidatorLocationRange(XMLIterator xmliter) {}
void DataManager::xmlSecondPassValidatorLocationPathable(XMLIterator xmliter) {}
void DataManager::xmlSecondPassValidatorFilterUnit(XMLIterator xmliter) {}
void DataManager::xmlSecondPassValidatorPlayer(XMLIterator xmliter) {}

void DataManager::xmlSecondPassParticleSystem(XMLIterator xmliter)
{
	DParticleSystem* pSystem;
	try
	{
		copyParent<DParticleSystem>(xmliter, &pSystem);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("Emitters");
		if (iter.isValid())
		{
			iter = iter.getChildrenOfName("ParticleEmitter");
			while (iter.isValid())
			{
				int temp_handle;
				linkData<DParticleEmitter>(iter, &temp_handle);
				pSystem->emitters_handles.push_back(temp_handle);
				iter = iter.next();
			}
		}
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("ParticleSystem(" + xmliter.getID() + ")::" + e.msg);
	}
}
void DataManager::xmlSecondPassParticleEmitter(XMLIterator xmliter)
{
	DParticleEmitter* emitter;
	try
	{
		copyParent<DParticleEmitter>(xmliter, &emitter);

		XMLIterator iter;
		XMLIterator subiter;

		float x;
		float y;
		float z;

		iter = xmliter.getChildrenOfName("BaseVariables");
		if (iter.isValid())
		{
			subiter = iter.getChildrenOfName("EmitterName");
			if (iter.isValid()) emitter->emitterName = subiter.getValue();

			subiter = iter.getChildrenOfName("BlendingMode");
			if (iter.isValid()) emitter->blendingMode = subiter.getValue();

			subiter = iter.getChildrenOfName("Texture");
			if (subiter.isValid())
			{
				int temp_handle;
				linkData<DTexture>(subiter, &temp_handle);
				emitter->texture_handle = temp_handle;
			}

			subiter = iter.getChildrenOfName("EmitterLocalOrigin");
			if (subiter.isValid())
			{
				XMLIterator subsubiter = subiter.getChildrenOfName("X");
				if (subsubiter.isValid()) emitter->emitterLocalOrigin.x = stof(subsubiter.getValue());
				XMLIterator subsubiter = subiter.getChildrenOfName("Y");
				if (subsubiter.isValid()) emitter->emitterLocalOrigin.y = stof(subsubiter.getValue());
				XMLIterator subsubiter = subiter.getChildrenOfName("Z");
				if (subsubiter.isValid()) emitter->emitterLocalOrigin.z = stof(subsubiter.getValue());
			}

			subiter = iter.getChildrenOfName("Lifetime");
			if (subiter.isValid())
			{
				XMLIterator subsubiter = subiter.getChildrenOfName("Min");
				if (subsubiter.isValid()) emitter->lifetime.x = stof(subsubiter.getValue());
				XMLIterator subsubiter = subiter.getChildrenOfName("Max");
				if (subsubiter.isValid()) emitter->lifetime.y = stof(subsubiter.getValue());
			}

			subiter = iter.getChildrenOfName("InitialSize");
			if (subiter.isValid()) {
				XMLIterator subsubiter = subiter.getChildrenOfName("Min");
				if (subsubiter.isValid()) emitter->initialSize.x = stof(subsubiter.getValue());
				XMLIterator subsubiter = subiter.getChildrenOfName("Max");
				if (subsubiter.isValid()) emitter->initialSize.y = stof(subsubiter.getValue());
			}

			subiter = iter.getChildrenOfName("InitialVelocity");
			if (subiter.isValid())
			{
				XMLIterator subsubiter = subiter.getChildrenOfName("X");
				if (subsubiter.isValid()) emitter->initialVelocity.x = stof(subsubiter.getValue());
				XMLIterator subsubiter = subiter.getChildrenOfName("Y");
				if (subsubiter.isValid()) emitter->initialVelocity.y = stof(subsubiter.getValue());
				XMLIterator subsubiter = subiter.getChildrenOfName("Z");
				if (subsubiter.isValid()) emitter->initialVelocity.z = stof(subsubiter.getValue());
			}
		}
		iter = xmliter.getChildrenOfName("SpawnVariables");

		if (iter.isValid())
		{
			subiter = iter.getChildrenOfName("ConstantRate");
			if(subiter.isValid()) emitter->constantRate = std::stoi(subiter.getValue());

			subiter = iter.getChildrenOfName("Burst");
			if(subiter.isValid()) emitter->burst = std::stoi(subiter.getValue());

			subiter = iter.getChildrenOfName("Looping");
			if(subiter.isValid()) emitter->looping = std::stoi(subiter.getValue());

			subiter = iter.getChildrenOfName("EmitterDelay");
			if(subiter.isValid()) emitter->emitterDelay = std::stof(subiter.getValue());
		}
		iter = xmliter.getChildrenOfName("SubUVVariables");
		if (iter.isValid)
		{
			subiter = iter.getChildrenOfName("SubImagesHorizontal");
			if(subiter.isValid()) emitter->subImagesHorizontal = std::stoi(subiter.getValue());

			subiter = iter.getChildrenOfName("SubImagesVertical");
			if(subiter.isValid()) emitter->subImagesVertical = std::stoi(subiter.getValue());
		}
		iter = xmliter.getChildrenOfName("Modules");
		if (iter.isValid())
		{
			subiter = iter.getChildrenOfName("ModuleSizeOverLife");
			if (subiter.isValid())
			{
				int temp_handle;
				linkData<DModule>(subiter, &temp_handle);
				emitter->modules_handles.push_back(temp_handle); 
			}

			subiter = iter.getChildrenOfName("ModuleColorOverLife");
			if (subiter.isValid())
			{
				int temp_handle;
				linkData<DModule>(subiter, &temp_handle);
				emitter->modules_handles.push_back(temp_handle);
			}

			subiter = iter.getChildrenOfName("ModuleInitialRotation");
			if (subiter.isValid())
			{
				int temp_handle;
				linkData<DModule>(subiter, &temp_handle);
				emitter->modules_handles.push_back(temp_handle);
			}

			subiter = iter.getChildrenOfName("ModuleInitialRotationRate");
			if (subiter.isValid())
			{
				int temp_handle;
				linkData<DModule>(subiter, &temp_handle);
				emitter->modules_handles.push_back(temp_handle);
			}

			subiter = iter.getChildrenOfName("ModuleSubImageIndexOverLife");
			if (subiter.isValid())
			{
				int temp_handle;
				linkData<DModule>(subiter, &temp_handle);
				emitter->modules_handles.push_back(temp_handle);
			}

			subiter = iter.getChildrenOfName("ModuleSubImageIndexRandom");
			if (subiter.isValid())
			{
				int temp_handle;
				linkData<DModule>(subiter, &temp_handle);
				emitter->modules_handles.push_back(temp_handle);
			}
		}
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("ParticleEmitter(" + xmliter.getID() + ")::" + e.msg);
	}
}
void DataManager::xmlSecondPassModuleSizeOverLife(XMLIterator xmliter)
{
	DModuleSizeOverLife* module;
	try
	{
		copyParent<DModuleSizeOverLife>(xmliter, &module);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("ScaleMultiplier");
		if (iter.isValid())
		{
			XMLIterator subiter = iter.getChildrenOfName("Beginning");
			if (subiter.isValid()) module->beinningFactor = std::stof(subiter.getValue());
			subiter = iter.getChildrenOfName("End");
			if (subiter.isValid()) module->endFactor = std::stof(subiter.getValue());
		}
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("ModuleSizeOverLife(" + xmliter.getID() + ")::" + e.err);
	}
}
void DataManager::xmlSecondPassModuleColorOverLife(XMLIterator xmliter)
{
	DModuleColorOverLife* module;
	try
	{
		copyParent<DModuleColorOverLife>(xmliter, &module);

		XMLIterator iter;
		XMLIterator subiter;
		XMLIterator subsubiter;
		float r;
		float g;
		float b;
		float a;

		iter = xmliter.getChildrenOfName("ColorMultiplier");
		if (iter.isValid())
		{
			subiter = iter.getChildrenOfName("Beginning");
			if (subiter.isValid()) {
				subsubiter = subiter.getChildrenOfName("R");
				if (subsubiter.isValid()) module->beginningColor.r = std::stof(subsubiter.getValue());
				subsubiter = subiter.getChildrenOfName("G");
				if (subsubiter.isValid()) module->beginningColor.g = std::stof(subsubiter.getValue());
				subsubiter = subiter.getChildrenOfName("B");
				if (subsubiter.isValid()) module->beginningColor.b = std::stof(subsubiter.getValue());
				subsubiter = subiter.getChildrenOfName("A");
				if (subsubiter.isValid()) module->beginningColor.a = std::stof(subsubiter.getValue());
			}
			subiter = iter.getChildrenOfName("End");
			if (subiter.isValid()) {
				subsubiter = subiter.getChildrenOfName("R");
				if (subsubiter.isValid()) module->endColor.r = std::stof(subsubiter.getValue());
				subsubiter = subiter.getChildrenOfName("G");
				if (subsubiter.isValid()) module->endColor.g = std::stof(subsubiter.getValue());
				subsubiter = subiter.getChildrenOfName("B");
				if (subsubiter.isValid()) module->endColor.b = std::stof(subsubiter.getValue());
				subsubiter = subiter.getChildrenOfName("A");
				if (subsubiter.isValid()) module->endColor.a = std::stof(subsubiter.getValue());
			}
		}
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("ModuleColorOverLife(" + xmliter.getID() + ")::" + e.err);
	}
}
void DataManager::xmlSecondPassModuleInitialRotation(XMLIterator xmliter)
{
	DModuleInitialRotation* module;
	try
	{
		copyParent<DModuleInitialRotation>(xmliter, &module);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("Min");
		if(iter.isValid()) module->min = stof(iter.getValue());

		iter = xmliter.getChildrenOfName("Max");
		if(iter.isValid()) module->max = stof(iter.getValue());
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("ModuleInitialRotation(" + xmliter.getID() + ")::" + e.err);
	}
}
void DataManager::xmlSecondPassModuleInitialRotationRate(XMLIterator xmliter)
{
	DModuleInitialRotationRate* module;
	try
	{
		copyParent<DModuleInitialRotationRate>(xmliter, &module);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("Min");
		if(iter.isValid()) module->min = stof(iter.getValue());

		iter = xmliter.getChildrenOfName("Max");
		if(iter.isValid()) module->max = stof(iter.getValue());
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("ModuleInitialRotationRate(" + xmliter.getID() + ")::" + e.err);
	}
}
void DataManager::xmlSecondPassModuleSubImageIndexOverLife(XMLIterator xmliter)
{
	DModuleSubImageIndexOverLife* module;
	try
	{
		copyParent<DModuleSubImageIndexOverLife>(xmliter, &module);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("Beginning");
		if(iter.isValid()) module->beginningIndex = stof(iter.getValue());

		iter = xmliter.getChildrenOfName("End");
		if(iter.isValid()) module->endIndex = stof(iter.getValue());
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("ModuleSubImageIndexOverLife(" + xmliter.getID() + ")::" + e.err);
	}
}
void DataManager::xmlSecondPassModuleSubImageIndexRandom(XMLIterator xmliter)
{
	DModuleSubImageIndexRandom* module;
	try
	{
		copyParent<DModuleSubImageIndexRandom>(xmliter, &module);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("Min");
		if(iter.isValid()) module->min = stof(iter.getValue());

		iter = xmliter.getChildrenOfName("Max");
		if(iter.isValid()) module->max = stof(iter.getValue());
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("ModuleSubImageIndexRandom(" + xmliter.getID() + ")::" + e.err);
	}
}

void DataManager::xmlParseVitals(XMLIterator iter, Vitals* vitals)
{
	if (iter.isValid())
	{
		XMLIterator subIter;

		subIter = iter.getChildrenOfName("HP");
		if (subIter.isValid()) vitals->hp = std::stof(subIter.getValue());

		subIter = iter.getChildrenOfName("Mana");
		if (subIter.isValid()) vitals->mana = std::stof(subIter.getValue());
	}
}
void DataManager::xmlParseCharges(XMLIterator iter, Charges* charges)
{
	if (iter.isValid())
	{
		XMLIterator subIter;

		subIter = iter.getChildrenOfName("Max");
		if (subIter.isValid()) charges->max = std::stoi(subIter.getValue());

		subIter = iter.getChildrenOfName("Start");
		if (subIter.isValid()) charges->start = std::stoi(subIter.getValue());

		subIter = iter.getChildrenOfName("Use");
		if (subIter.isValid()) charges->use = std::stoi(subIter.getValue());

		subIter = iter.getChildrenOfName("Regen");
		if (subIter.isValid()) charges->regen = std::stoi(subIter.getValue());

		subIter = iter.getChildrenOfName("Cooldown");
		if (subIter.isValid()) charges->cooldown = std::stof(subIter.getValue());
	}
}
void DataManager::xmlParseCost(XMLIterator iter, Cost* cost)
{
	if (iter.isValid())
	{
		XMLIterator subIter;

		subIter = iter.getChildrenOfName("Vitals");
		xmlParseVitals(subIter, &cost->vitals);

		subIter = iter.getChildrenOfName("VitalFraction");
		xmlParseVitals(subIter, &cost->vitalFraction);

		subIter = iter.getChildrenOfName("Charges");
		xmlParseCharges(subIter, &cost->charges);

		subIter = iter.getChildrenOfName("Cooldown");
		if (subIter.isValid()) cost->cooldown = std::stof(subIter.getValue());
	}
}
void DataManager::xmlParseEffectList(XMLIterator iter, EffectList* effects)
{
	if (iter.isValid())
	{
		XMLIterator subIter;
#pragma region Initial
		subIter = iter.getChildrenOfName("EffectInitial");
		if (subIter.isValid())
		{
			std::string effectId = subIter.getValue();
			if (!effectId.empty())
			{
				if (DEffect::hasKey(effectId))
				{
					effects->effectInitial = DEffect::getIndex(effectId);
				}
				else
				{
					throw DataErrorException("EffectInitial specified but not found: " + effectId);
				}
			}
		}
#pragma endregion
#pragma region Periodic
		subIter = iter.getChildrenOfName("EffectPeriodic");
		if (subIter.isValid())
		{
			std::string effectId = subIter.getValue();
			if (!effectId.empty())
			{
				if (DEffect::hasKey(effectId))
				{
					effects->effectPeriodic = DEffect::getIndex(effectId);
				}
				else
				{
					throw DataErrorException("EffectPeriodic specified but not found: " + effectId);
				}
			}
		}
#pragma endregion
#pragma region Final
		subIter = iter.getChildrenOfName("EffectFinal");
		if (subIter.isValid())
		{
			std::string effectId = subIter.getValue();
			if (!effectId.empty())
			{
				if (DEffect::hasKey(effectId))
				{
					effects->effectFinal = DEffect::getIndex(effectId);
				}
				else
				{
					throw DataErrorException("EffectFinal specified but not found: " + effectId);
				}
			}
		}
#pragma endregion
#pragma region Expire
		subIter = iter.getChildrenOfName("EffectExpire");
		if (subIter.isValid())
		{
			std::string effectId = subIter.getValue();
			if (!effectId.empty())
			{
				if (DEffect::hasKey(effectId))
				{
					effects->effectExpire = DEffect::getIndex(effectId);
				}
				else
				{
					throw DataErrorException("EffectExpire specified but not found: " + effectId);
				}
			}
		}
#pragma endregion
	}
}
void DataManager::xmlParseFilter(XMLIterator iter, Filter* filter)
{
	if (iter.isValid())
	{
		std::string val = iter.getValue();
		if (!val.compare("ALLOWED")) //If they are the same the function retuns 0
		{
			*filter = Filter::ALLOWED;
		}
		else if (!val.compare("REQUIRED"))
		{
			*filter = Filter::REQUIRED;
		}
		else if (!val.compare("EXCLUDED"))
		{
			*filter = Filter::EXCLUDED;
		}
		else
		{
			throw DataErrorException("Unknown value for filter: " + val);
		}
	}
}
void DataManager::xmlParseUnitFilter(XMLIterator iter, UnitFilter* filter)
{
	if (iter.isValid())
	{
		XMLIterator subIter;

		subIter = iter.getChildrenOfName("Dead");
		xmlParseFilter(subIter, &filter->dead);

		subIter = iter.getChildrenOfName("Invulnerable");
		xmlParseFilter(subIter, &filter->invulnerable);

		subIter = iter.getChildrenOfName("Missile");
		xmlParseFilter(subIter, &filter->missile);

		subIter = iter.getChildrenOfName("Self");
		xmlParseFilter(subIter, &filter->self);

		subIter = iter.getChildrenOfName("Ally");
		xmlParseFilter(subIter, &filter->ally);

		subIter = iter.getChildrenOfName("Enemy");
		xmlParseFilter(subIter, &filter->enemy);

		subIter = iter.getChildrenOfName("Neutral");
		xmlParseFilter(subIter, &filter->neutral);
	}
}

void DataManager::xmlParseAttributes(XMLIterator iter, Attributes* attributes)
{
	if (iter.isValid())
	{
		XMLIterator subIter;
		subIter = iter.getChildrenOfName("Missile");
		if (subIter.isValid()) attributes->missile = (bool) std::stoi(subIter.getValue());
	}
}

void DataManager::xmlParseAbilityList(XMLIterator iter, std::vector<int>* abilities)
{
	if (iter.isValid())
	{
		XMLIterator subIter = iter.getChildrenOfName("Ability");
		while (subIter.isValid())
		{
			int tmp = -1;
			linkData<DAbility>(subIter, &tmp);
			if (tmp >= 0)
			{
				abilities->push_back(tmp);
			}
			else
			{
				throw DataErrorException("Error parsing ability list.");
			}
			subIter = subIter.next();
		}
	}
}
void DataManager::xmlParseBehaviorList(XMLIterator iter, std::vector<int>* behaviors)
{
	if (iter.isValid())
	{
		XMLIterator subIter = iter.getChildrenOfName("Behavior");
		while (subIter.isValid())
		{
			int tmp = -1;
			linkData<DBehavior>(subIter, &tmp);
			if (tmp >= 0)
			{
				behaviors->push_back(tmp);
			}
			else
			{
				throw DataErrorException("Error parsing behavior list.");
			}
			subIter = subIter.next();
		}
	}
}