#include "DataManager.h"

namespace Hive
{

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
		catch (IDataManager::DataErrorException e)
		{
			throw IDataManager::DataErrorException(std::string(filename) + ": " + e.err);
		}

		return 0;
	}

	DataManager::~DataManager()
	{
	}

	void DataManager::xmlFirstPass(XMLInterface& xmlif)
	{
		using std::placeholders::_1;
		typedef XMLInterface::XMLIterator XIter;

		XIter root = xmlif.begin();

		if (!root.isValid()) throw IDataManager::DataErrorException("Root invalid.");

		root.forEachChildOfName("Ability", std::bind(&DataManager::xmlFirstPassAbilities, this, _1));
		root.forEachChildOfName("Actor", std::bind(&DataManager::xmlFirstPassActors, this, _1));
		root.forEachChildOfName("Behavior", std::bind(&DataManager::xmlFirstPassBehaviors, this, _1));

		root.forEachChildOfName("EffectModifyUnit", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
		root.forEachChildOfName("EffectSearch", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
		root.forEachChildOfName("EffectSet", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
		root.forEachChildOfName("EffectSetBehavior", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
		root.forEachChildOfName("EffectSpawnUnit", std::bind(&DataManager::xmlFirstPassEffect, this, _1));
		root.forEachChildOfName("EffectSwitch", std::bind(&DataManager::xmlFirstPassEffect, this, _1));

		root.forEachChildOfName("Shader", std::bind(&DataManager::xmlFirstPassShaders, this, _1));
		root.forEachChildOfName("Texture", std::bind(&DataManager::xmlFirstPassTextures, this, _1));
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
	}

	void DataManager::xmlFirstPassAbilities(XMLInterface::XMLIterator xmliter)
	{
		DAbility ability;
		std::string id = xmliter.getID();
		DAbility::addItem(id, ability);
	}
	void DataManager::xmlFirstPassActors(XMLInterface::XMLIterator xmliter)
	{
		DActor actor;
		std::string id = xmliter.getID();
		DActor::addItem(id, actor);
	}
	void DataManager::xmlFirstPassBehaviors(XMLInterface::XMLIterator xmliter)
	{
		DBehavior behavior;
		std::string id = xmliter.getID();
		DBehavior::addItem(id, behavior);
	}

	void DataManager::xmlFirstPassEffect(XMLInterface::XMLIterator xmliter)
	{
		DEffect effect;
		std::string id = xmliter.getID();
		DEffect::addItem(id, effect);
	}

	void DataManager::xmlFirstPassShaders(XMLInterface::XMLIterator xmliter)
	{
		DShaderProgram shader;
		std::string id = xmliter.getID();
		DShaderProgram::addItem(id, shader);
	}
	void DataManager::xmlFirstPassTextures(XMLInterface::XMLIterator xmliter)
	{
		DTexture texture;
		std::string id = xmliter.getID();
		DTexture::addItem(id, texture);
	}
	void DataManager::xmlFirstPassModels(XMLInterface::XMLIterator xmliter)
	{
		DModel model;
		std::string id = xmliter.getID();
		DModel::addItem(id, model);
	}
	void DataManager::xmlFirstPassUnits(XMLInterface::XMLIterator xmliter)
	{
		DUnit unit;
		std::string id = xmliter.getID();
		DUnit::addItem(id, unit);
	}

	void DataManager::xmlFirstPassValidator(XMLInterface::XMLIterator xmliter)
	{
		DValidator validator;
		std::string id = xmliter.getID();
		DValidator::addItem(id, validator);
	}

	void DataManager::xmlSecondPass(XMLInterface& xmlif)
	{
		using std::placeholders::_1;
		typedef XMLInterface::XMLIterator XIter;

		XIter root = xmlif.begin();

		root.forEachChildOfName("Ability", std::bind(&DataManager::xmlSecondPassAbilities, this, _1));
		root.forEachChildOfName("Actor", std::bind(&DataManager::xmlSecondPassActors, this, _1));
		root.forEachChildOfName("Behavior", std::bind(&DataManager::xmlSecondPassBehaviors, this, _1));

		root.forEachChildOfName("EffectModifyUnit", std::bind(&DataManager::xmlSecondPassEffectModifyUnit, this, _1));
		root.forEachChildOfName("EffectSearch", std::bind(&DataManager::xmlSecondPassEffectSearch, this, _1));
		root.forEachChildOfName("EffectSet", std::bind(&DataManager::xmlSecondPassEffectSet, this, _1));
		root.forEachChildOfName("EffectSetBehavior", std::bind(&DataManager::xmlSecondPassEffectSetBehavior, this, _1));
		root.forEachChildOfName("EffectSpawnUnit", std::bind(&DataManager::xmlSecondPassEffectSpawnUnit, this, _1));
		root.forEachChildOfName("EffectSwitch", std::bind(&DataManager::xmlSecondPassEffectSwitch, this, _1));

		root.forEachChildOfName("Shader", std::bind(&DataManager::xmlSecondPassShaders, this, _1));
		root.forEachChildOfName("Texture", std::bind(&DataManager::xmlSecondPassTextures, this, _1));
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
	}

	void DataManager::xmlSecondPassAbilities(XMLInterface::XMLIterator xmliter)
	{
		typedef XMLInterface::XMLIterator XIter;
		DAbility* ability;

		std::string id = xmliter.getID();
		if (!DAbility::hasKey(id)) throw IDataManager::DataErrorException("Ability key missing during second pass: " + id);

		try
		{
			ability = DAbility::getItem(DAbility::getIndex(id));

			std::string parentId = xmliter.getParentID();

			if (!parentId.empty())
			{
				if (DAbility::hasKey(parentId))
				{
					int index = DAbility::getIndex(parentId);
					*ability = *(DAbility::getItem(index));
				}
				else
				{
					throw IDataManager::DataErrorException("Ability parent specified but not found: " + parentId);
				}
			}

			XIter iter;
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
					throw IDataManager::DataErrorException("Unkown ability type value encountered: " + val);
				}
			}
#pragma endregion

			iter = xmliter.getChildrenOfName("Name");
			if (iter.isValid()) ability->name = iter.getValue();

			iter = xmliter.getChildrenOfName("Tooltip");
			if (iter.isValid()) ability->tooltip = iter.getValue();

			iter = xmliter.getChildrenOfName("Icon");
			xmlParseTexture(iter, &ability->iconTextureHandle);

			iter = xmliter.getChildrenOfName("Cost");
			xmlParseCost(iter, &ability->cost);

			iter = xmliter.getChildrenOfName("Effects");
			xmlParseEffectList(iter, &ability->effects);

			iter = xmliter.getChildrenOfName("Range");
			if (iter.isValid()) ability->range = std::stof(iter.getValue());

			iter = xmliter.getChildrenOfName("TargetFilter");
			xmlParseUnitFilter(iter, &ability->targetFilter);
		}
		catch (IDataManager::DataErrorException e)
		{
			throw IDataManager::DataErrorException("Ability(" + id + ")::" + e.err);
		}
	}

	void DataManager::xmlSecondPassActors(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassBehaviors(XMLInterface::XMLIterator xmliter) {}

	void DataManager::xmlSecondPassEffectModifyUnit(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassEffectSearch(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassEffectSet(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassEffectSetBehavior(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassEffectSpawnUnit(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassEffectSwitch(XMLInterface::XMLIterator xmliter) {}

	void DataManager::xmlSecondPassShaders(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassTextures(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassModels(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassUnits(XMLInterface::XMLIterator xmliter) {}

	void DataManager::xmlSecondPassValidatorBehaviorCount(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassValidatorCombine(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassValidatorCompareVital(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassValidatorCondition(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassValidatorLocationRange(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassValidatorLocationPathable(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassValidatorFilterUnit(XMLInterface::XMLIterator xmliter) {}
	void DataManager::xmlSecondPassValidatorPlayer(XMLInterface::XMLIterator xmliter) {}

	void DataManager::xmlParseVitals(XMLInterface::XMLIterator iter, Vitals* vitals)
	{
		typedef XMLInterface::XMLIterator XIter;
		if (iter.isValid())
		{
			XIter subIter;

			subIter = iter.getChildrenOfName("HP");
			if (subIter.isValid()) vitals->hp = std::stof(subIter.getValue());

			subIter = iter.getChildrenOfName("Mana");
			if (subIter.isValid()) vitals->mana = std::stof(subIter.getValue());
		}
	}
	void DataManager::xmlParseCharges(XMLInterface::XMLIterator iter, Charges* charges)
	{
		typedef XMLInterface::XMLIterator XIter;
		if (iter.isValid())
		{
			XIter subIter;

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
	void DataManager::xmlParseCost(XMLInterface::XMLIterator iter, Cost* cost)
	{
		typedef XMLInterface::XMLIterator XIter;
		if (iter.isValid())
		{
			XIter subIter;

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
	void DataManager::xmlParseEffectList(XMLInterface::XMLIterator iter, EffectList* effects)
	{
		typedef XMLInterface::XMLIterator XIter;
		if (iter.isValid())
		{
			XIter subIter;
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
						throw IDataManager::DataErrorException("EffectInitial specified but not found: " + effectId);
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
						throw IDataManager::DataErrorException("EffectPeriodic specified but not found: " + effectId);
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
						throw IDataManager::DataErrorException("EffectFinal specified but not found: " + effectId);
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
						throw IDataManager::DataErrorException("EffectExpire specified but not found: " + effectId);
					}
				}
			}
#pragma endregion
		}
	}
	void DataManager::xmlParseFilter(XMLInterface::XMLIterator iter, Filter* filter)
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
				throw IDataManager::DataErrorException("Unknown value for filter: " + val);
			}
		}
	}
	void DataManager::xmlParseUnitFilter(XMLInterface::XMLIterator iter, UnitFilter* filter)
	{
		typedef XMLInterface::XMLIterator XIter;
		if (iter.isValid())
		{
			XIter subIter;

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

	void DataManager::xmlParseTexture(XMLInterface::XMLIterator iter, DTexture* texHandle)
	{
		//TODO: Textures handling may need to be very different, come back to this later.
		/*
		if (iter.isValid())
		{
			std::string texId = iter.getValue();
			if (!texId.empty())
			{
				if (_textures.hasKey(texId))
				{
					*texHandle = _textures.getIndex(texId);
				}
				else
				{
					throw IDataManager::DataErrorException("Texture specified but not found: " + texId);
				}
			}
		}
		*/
	}
	void DataManager::xmlParseModel(XMLInterface::XMLIterator iter, DModel* modelHandle)
	{
		//TODO:
	}
	void DataManager::xmlParseShader(XMLInterface::XMLIterator iter, DShaderProgram* shaderHandle)
	{
		//TODO:
	}
}