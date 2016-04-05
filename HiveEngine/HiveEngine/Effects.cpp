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

std::vector<UnitHandle> Effects::get_units_in_area(glm::vec2 location, float radius)
{
	//TODO: use a better search method than going over every one.
	std::vector<UnitHandle> units = std::vector<UnitHandle>();
	const ObjectPool<Unit>& pool = Unit::view_pool();
	for (int i = 0, c = 0; c < pool.get_num_in_use(); i++)
	{
		if (!pool.is_used(i)) continue;

		c++;

		const Unit* unit = pool.c_get(i);
		glm::vec2 u_pos = unit->get_position();
		if (glm::distance(location, u_pos) < radius)
		{
			units.push_back(unit->get_handle());
		}
	}
	return units;
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
	try
	{
		glm::vec2 location = effectTree->getLocation(effect->location);
		std::vector<UnitHandle> units = get_units_in_area(location, effect->radius);
		std::vector<EffectTree*> children = std::vector<EffectTree*>(units.size());
		for (int i = 0; i < units.size(); i++)
		{
			Unit* unit = Unit::get_component(units[i]);
			//TODO: validate unit against filter.
			EffectTree* child = effectTree->addChild();

			child->setEffect(effect->effect);

			child->setTargetUnit(units[i]);
			child->setTargetPlayer(unit->get_player());
			child->setTargetLocation(unit->get_position());

			children[i] = child;
		}

		for (int i = 0; i < children.size(); i++)
		{
			launchEffect(children[i]);
		}

		EffectTree::clean(effectTree);
	}
	catch (const Exception& e)
	{
		throw EffectException("Error in Search effect: " + e.msg);
	}
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
		int unit = ServiceLocator::get_component_manager()->spawn_unit(loc, data, player);
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
