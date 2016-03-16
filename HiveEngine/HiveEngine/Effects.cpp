#include "Effects.h"

using namespace Hive;

void Effects::launchEffect(EffectTree* effectTree)
{
	if (effectTree == nullptr) throw EffectException("Null effect passed to LaunchEffect");
	int id = effectTree->getEffect();
	if (id <= -1) throw EffectException("No effect specified.");

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

void Effects::eModifyUnit(EffectTree* effectTree, DEffectModifyUnit* effect)
{
	throw UnimplementedException();
}
void Effects::eSearch(EffectTree* effectTree, DEffectSearch* effect)
{
	throw UnimplementedException();
}
void Effects::eSet(EffectTree* effectTree, DEffectSet* set)
{
	throw UnimplementedException();
}
void Effects::eSetBehavior(EffectTree* effectTree, DEffectSetBehavior* effect)
{
	throw UnimplementedException();
}
void Effects::eSpawnUnit(EffectTree* effectTree, DEffectSpawnUnit* effect)
{
	throw UnimplementedException();
}
void Effects::eSwitch(EffectTree* effectTree, DEffectSwitch* effect)
{
	throw UnimplementedException();
}
