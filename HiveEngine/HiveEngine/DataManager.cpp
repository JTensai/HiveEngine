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
		throw DataErrorException(std::string(filename) + ": " + e.err);
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
	Material mat;
	std::string id = xmliter.getID();
	Material::addItem(id, mat);
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
	ParticleSystem system;
	std::string id = xmliter.getID();
	ParticleSystem::addItem(id, system);
}
void DataManager::xmlFirstPassParticleEmitter(XMLIterator xmliter)
{
	ParticleEmitter emitter;
	std::string id = xmliter.getID();
	ParticleEmitter::addItem(id, emitter);
}
//modules...
void DataManager::xmlFirstPassModuleSizeOverLife(XMLIterator xmliter)
{
	ModuleSizeOverLife module;
	std::string id = xmliter.getID();
	ModuleSizeOverLife::addItem(id, module);
}
void DataManager::xmlFirstPassModuleColorOverLife(XMLIterator xmliter)
{
	ModuleColorOverLife module;
	std::string id = xmliter.getID();
	ModuleColorOverLife::addItem(id, module);
}
void DataManager::xmlFirstPassModuleInitialRotation(XMLIterator xmliter)
{
	ModuleInitialRotation module;
	std::string id = xmliter.getID();
	ModuleInitialRotation::addItem(id, module);
}
void DataManager::xmlFirstPassModuleInitialRotationRate(XMLIterator xmliter)
{
	ModuleInitialRotationRate module;
	std::string id = xmliter.getID();
	ModuleInitialRotationRate::addItem(id, module);
}
void DataManager::xmlFirstPassModuleSubImageIndexOverLife(XMLIterator xmliter)
{
	ModuleSubImageIndexOverLife module;
	std::string id = xmliter.getID();
	ModuleSubImageIndexOverLife::addItem(id, module);
}
void DataManager::xmlFirstPassModuleSubImageIndexRandom(XMLIterator xmliter)
{
	ModuleSubImageIndexRandom module;
	std::string id = xmliter.getID();
	ModuleSubImageIndexRandom::addItem(id, module);
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
		throw DataErrorException("Ability(" + xmliter.getID() + ")::" + e.err);
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
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Actor(" + xmliter.getID() + ")::" + e.err);
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
		throw DataErrorException("Texture(" + xmliter.getID() + ")::" + e.err);
	}
}
void DataManager::xmlSecondPassMaterials(XMLIterator xmliter)
{
	Material* mat;
	try
	{
		copyParent<Material>(xmliter, &mat);

		XMLIterator iter;
		iter = xmliter.getChildrenOfName("DiffuseTexture");
		linkData<DTexture>(iter, &mat->diffuse_tex);
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Material(" + xmliter.getID() + ")::" + e.err);
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

		iter = xmliter.getChildrenOfName("Meshes");
		xmlParseMeshList(iter, &model->mesh_mat_handles);
	}
	catch (DataErrorException e)
	{
		throw DataErrorException("Model(" + xmliter.getID() + ")::" + e.err);
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
		throw DataErrorException("Unit(" + xmliter.getID() + ")::" + e.err);
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
	//TODO
}
void DataManager::xmlSecondPassParticleEmitter(XMLIterator xmliter)
{
	//TODO
}
// modules...
void DataManager::xmlSecondPassModuleSizeOverLife(XMLIterator xmliter)
{
	//TODO
}
void DataManager::xmlSecondPassModuleColorOverLife(XMLIterator xmliter)
{
	//TODO
}
void DataManager::xmlSecondPassModuleInitialRotation(XMLIterator xmliter)
{
	//TODO
}
void DataManager::xmlSecondPassModuleInitialRotationRate(XMLIterator xmliter)
{
	//TODO
}
void DataManager::xmlSecondPassModuleSubImageIndexOverLife(XMLIterator xmliter)
{
	//TODO
}
void DataManager::xmlSecondPassModuleSubImageIndexRandom(XMLIterator xmliter)
{
	//TODO
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

void DataManager::xmlParseMeshList(XMLIterator iter, std::vector<int>* mesh_mat_list)
{
	if (iter.isValid())
	{
		XMLIterator subIter = iter.getChildrenOfName("Mesh");
		while (subIter.isValid())
		{
			xmlParseMesh(subIter, mesh_mat_list);
			subIter = subIter.next();
		}
	}
}
void DataManager::xmlParseMesh(XMLIterator iter, std::vector<int>* mesh_mat_list)
{
	XMLIterator subIter = iter.getChildrenOfName("Material");
	if (subIter.isValid())
	{
		int mat;
		linkData<Material>(subIter, &mat);
		mesh_mat_list->push_back(mat);
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