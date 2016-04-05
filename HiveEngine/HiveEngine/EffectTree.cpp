#include "EffectTree.h"

using namespace Hive;

void EffectTree::clean(EffectTree* effectTree)
{
	//TODO: this is not working properly, fix it.
	if (effectTree->activeReferences > 0)
	{
		for (int i = 0; i < effectTree->children.size(); i++)
		{
			clean(effectTree->children[i]);
		}
		if (effectTree->activeReferences <= 0)
		{
			if (effectTree->parent != nullptr)
			{
				effectTree->parent->activeReferences--;
			}
		}
	}

	EffectTree* ptr = effectTree;
	while (ptr->parent != nullptr) ptr = ptr->parent;

	if (ptr->activeReferences <= 0) delete ptr;
}

EffectTree::EffectTree()
{
	effect = -1;

	castingUnit = -1;
	castingPlayer = -1;

	sourceUnit = -1;
	sourcePlayer = -1;
	hasSourceLocation = false;
	sourceLocation = glm::vec2(0);

	targetUnit = -1;
	targetPlayer = -1;
	hasTargetLocation = false;
	targetLocation = glm::vec2(0);

	spawnedUnit = -1;

	parent = nullptr;

	children = std::vector<EffectTree*>();
	activeReferences = 0;
}

EffectTree* EffectTree::findEffect(DEffectHandle effect)
{
	EffectTree* ptr = this;
	if (effect == -1) return ptr;
	while (ptr->effect != effect && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->effect == effect) return ptr;
	//Reached root without finding node, search through children.

	EffectTree* ptr2 = nullptr;
	for (int i = 0; i < ptr->children.size(); i++)
	{
		ptr2 = ptr->children[i]->findEffectDown(effect);
		if (ptr2 != nullptr) return ptr2;
	}

	throw EffectTreeException("Specified effect(" + std::to_string(effect) + ") not found in effect tree.");
}

EffectTree* EffectTree::findEffectDown(DEffectHandle effect)
{
	if (EffectTree::effect == effect) return this;

	for (int i = 0; i < children.size(); i++)
	{
		EffectTree* ptr = nullptr;
		ptr = children[i]->findEffectDown(effect);
		if (ptr != nullptr) return ptr;
	}

	return nullptr;
}

DEffectHandle EffectTree::setEffect(DEffectHandle effect)
{
	EffectTree::effect = effect;
	return effect;
}
DEffectHandle EffectTree::getEffect()
{
	return effect;
}

UnitHandle EffectTree::setCastingUnit(UnitHandle castingUnit)
{
	EffectTree::castingUnit = castingUnit;
	return castingUnit;
}
UnitHandle EffectTree::getCastingUnit(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->castingUnit == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->castingUnit == -1) throw EffectTreeException("Unable to get casting unit.");
	return ptr->castingUnit;
}

PlayerHandle EffectTree::setCastingPlayer(PlayerHandle castingPlayer)
{
	EffectTree::castingPlayer = castingPlayer;
	return castingPlayer;
}
PlayerHandle EffectTree::getCastingPlayer(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->castingPlayer == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->castingPlayer == -1) throw EffectTreeException("Unable to get casting player.");
	return ptr->castingPlayer;
}

glm::vec2 EffectTree::setCasterLocation(glm::vec2 casterLocation)
{
	EffectTree::casterLocation = casterLocation;
	hasCasterLocation = true;
	return casterLocation;
}
glm::vec2 EffectTree::getCasterLocation(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (!ptr->hasCasterLocation && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (!ptr->hasCasterLocation) throw EffectTreeException("Unable to get caster location.");
	return ptr->casterLocation;
}

UnitHandle EffectTree::setSourceUnit(UnitHandle sourceUnit)
{
	EffectTree::sourceUnit = sourceUnit;
	return sourceUnit;
}
UnitHandle EffectTree::getSourceUnit(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->sourceUnit == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->sourceUnit == -1) throw EffectTreeException("Unable to get source unit.");
	return ptr->sourceUnit;
}

PlayerHandle EffectTree::setSourcePlayer(PlayerHandle sourcePlayer)
{
	EffectTree::sourcePlayer = sourcePlayer;
	return sourcePlayer;
}
PlayerHandle EffectTree::getSourcePlayer(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->sourcePlayer == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->sourcePlayer == -1) throw EffectTreeException("Unable to get source player.");
	return ptr->sourcePlayer;
}

glm::vec2 EffectTree::setSourceLocation(glm::vec2 sourceLocation)
{
	EffectTree::sourceLocation = sourceLocation;
	hasSourceLocation = true;
	return sourceLocation;
}
glm::vec2 EffectTree::getSourceLocation(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (!ptr->hasSourceLocation && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (!ptr->hasSourceLocation) throw EffectTreeException("Unable to get source location.");
	return ptr->sourceLocation;
}

UnitHandle EffectTree::setTargetUnit(UnitHandle targetUnit)
{
	EffectTree::targetUnit = targetUnit;
	return targetUnit;
}
UnitHandle EffectTree::getTargetUnit(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->targetUnit == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->targetUnit == -1) throw EffectTreeException("Unable to get target unit.");
	return ptr->targetUnit;
}

PlayerHandle EffectTree::setTargetPlayer(PlayerHandle targetPlayer)
{
	EffectTree::targetPlayer = targetPlayer;
	return targetPlayer;
}
PlayerHandle EffectTree::getTargetPlayer(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->targetPlayer == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->targetPlayer == -1) throw EffectTreeException("Unable to get target player.");
	return ptr->targetPlayer;
}

glm::vec2 EffectTree::setTargetLocation(glm::vec2 targetLocation)
{
	EffectTree::targetLocation = targetLocation;
	hasTargetLocation = true;
	return targetLocation;
}
glm::vec2 EffectTree::getTargetLocation(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (!ptr->hasTargetLocation && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (!ptr->hasTargetLocation) throw EffectTreeException("Unable to get target location.");
	return ptr->targetLocation;
}

UnitHandle EffectTree::setSpawnedUnit(UnitHandle spawnedUnit)
{
	EffectTree::spawnedUnit = spawnedUnit;
	return spawnedUnit;
}
UnitHandle EffectTree::getSpawnedUnit(DEffectHandle effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->spawnedUnit == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->spawnedUnit == -1) throw EffectTreeException("Unable to get spawned unit.");
	return ptr->spawnedUnit;
}

EffectTree* EffectTree::addChild()
{
	children.push_back(new EffectTree());
	activeReferences++;
	children.back()->parent = this;
	return children.back();
}


UnitHandle EffectTree::getUnit(EffectUnit unit)
{
	EffectTree* et = findEffect(unit.effectHandle);
	switch (unit.unit)
	{
	case EffectUnitEnum::CASTER_UNIT:
		return et->getCastingUnit(unit.effectHandle);
	case EffectUnitEnum::SOURCE_UNIT:
		return et->getSourceUnit(unit.effectHandle);
	case EffectUnitEnum::TARGET_UNIT:
		return et->getTargetUnit(unit.effectHandle);
	case EffectUnitEnum::SPAWNED_UNIT:
		return et->getSpawnedUnit(unit.effectHandle);
	case EffectUnitEnum::NONE_UNIT:
		throw EffectTreeException("Attempting to get NONE unit.");
	default:
		throw EffectTreeException("Unrecognized unit enum.");
	}
}

PlayerHandle EffectTree::getPlayer(EffectPlayer player)
{
	EffectTree* et = findEffect(player.effectHandle);
	switch (player.player)
	{
	case EffectPlayerEnum::CASTER_PLAYER:
		return et->getCastingPlayer(player.effectHandle);
	case EffectPlayerEnum::SOURCE_PLAYER:
		return et->getSourcePlayer(player.effectHandle);
	case EffectPlayerEnum::TARGET_PLAYER:
		return et->getTargetPlayer(player.effectHandle);
	case EffectPlayerEnum::NONE_PLAYER:
		throw EffectTreeException("Attempting to get NONE player.");
	case EffectPlayerEnum::LOCAL_PLAYER:
		//TODO if/when networking is incorporated this should grab synchronized id for local player.
		return LOCAL_PLAYER;
	case EffectPlayerEnum::NEUTRAL_PLAYER:
		return NEUTRAL_PLAYER;
	case EffectPlayerEnum::HOSTILE_PLAYER:
		return HOSTILE_PLAYER;
	default:
		throw EffectTreeException("Unrecognized player enum.");
	}
}

glm::vec2 EffectTree::getLocation(EffectLocation loc)
{
	EffectTree* et = findEffect(loc.effectHandle);
	switch (loc.location)
	{
	case EffectLocationEnum::CASTER_LOCATION:
		return et->getCasterLocation(loc.effectHandle);
	case EffectLocationEnum::SOURCE_LOCATION:
		return et->getSourceLocation(loc.effectHandle);
	case EffectLocationEnum::TARGET_LOCATION:
		return et->getTargetLocation(loc.effectHandle);
	case EffectLocationEnum::NONE_LOCATION:
		throw EffectTreeException("Attempting to get NONE location.");
	default:
		throw EffectTreeException("Unrecognized location enum.");
	}
}

EffectTree::~EffectTree()
{
	if (children.size() > 0)
	{
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i] != nullptr)
			{
				delete children[i];
			}
		}
	}
}
