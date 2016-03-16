#include "Effects.h"

using namespace Hive;

void Effects::launchEffect(EffectTree* effectTree)
{
	if (effectTree == nullptr) throw EffectException("Null effect passed to LaunchEffect");
	int id = effectTree->getEffect();
	if (id <= -1) throw EffectException("No effect specified.");

	try
	{
		DEffect* e = DEffect::getItem(id);
		switch (((DEffectBase*)e)->type)
		{
		case EffectType::MODIFY_UNIT:
			eModifyUnit(effectTree, (DEffectModifyUnit*)e);
			break;
		case EffectType::SEARCH:
			eSearch(effectTree, (DEffectSearch*)e);
			break;
		case EffectType::SET:
			eSet(effectTree, (DEffectSet*)e);
			break;
		case EffectType::SET_BEHAVIOR:
			eSetBehavior(effectTree, (DEffectSetBehavior*)e);
			break;
		case EffectType::SPAWN_UNIT:
			eSpawnUnit(effectTree, (DEffectSpawnUnit*)e);
			break;
		case EffectType::SWITCH:
			eSwitch(effectTree, (DEffectSwitch*)e);
			break;
		default:
			throw EffectException("Unrecognized effect type.");
		}
	}
	catch (const Exception& e)
	{
		throw EffectException("Error launching effect(" + std::to_string(id) + "): " + e.msg);
	}
}

void Effects::eModifyUnit(EffectTree* effectTree, DEffectModifyUnit* effect)
{
	try
	{
		EffectUnit eUnit = effect->unit;
		int iUnit = effectTree->getUnit(eUnit);
		Unit* unit = Unit::get_component(iUnit);
		if (unit == nullptr) throw EffectException("Could not get unit.");
		unit->set_vitals(unit->get_vitals() + effect->vitalsDelta);

		EffectTree::clean(effectTree);
	}
	catch (const Exception& e)
	{
		throw EffectException("Error in ModifyUnit effect: " + e.msg);
	}
}
void Effects::eSearch(EffectTree* effectTree, DEffectSearch* effect)
{
	throw UnimplementedException();
}
void Effects::eSet(EffectTree* effectTree, DEffectSet* set)
{
	std::vector<EffectTree*> new_effects;
	for (int i = 0; i < set->effectHandles.size(); i++)
	{
		EffectTree* et = effectTree->addChild();
		et->setEffect(set->effectHandles[i]);
		new_effects.push_back(et);
	}
	for (int i = 0; i < new_effects.size(); i++)
	{
		Effects::launchEffect(new_effects[i]);
	}
}
void Effects::eSetBehavior(EffectTree* effectTree, DEffectSetBehavior* effect)
{
	throw UnimplementedException();
}
void Effects::eSpawnUnit(EffectTree* effectTree, DEffectSpawnUnit* effect)
{
	try
	{
		int player = effectTree->getPlayer(effect->owner);
		int data = effect->unitDataHandle;
		glm::vec2 loc = effectTree->getLocation(effect->location);
		int unit = ServiceLocator::getInstance()->getComponentManager()->spawn_unit(loc, data, player);
		effectTree->setSpawnedUnit(unit);

		EffectTree::clean(effectTree);
	}
	catch (const Exception& e)
	{
		throw EffectException("Error in SpawnUnit effect: " + e.msg);
	}
}
void Effects::eSwitch(EffectTree* effectTree, DEffectSwitch* effect)
{
	throw UnimplementedException();
}
