#include "EffectTree.h"

using namespace Hive;

void EffectTree::clean(EffectTree* effectTree)
{
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

EffectTree* EffectTree::findEffect(int effect)
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

EffectTree* EffectTree::findEffectDown(int effect)
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

int EffectTree::setEffect(int effect)
{
	EffectTree::effect = effect;
	return effect;
}
int EffectTree::getEffect()
{
	return effect;
}

int EffectTree::setCastingUnit(int castingUnit)
{
	EffectTree::castingUnit = castingUnit;
	return castingUnit;
}
int EffectTree::getCastingUnit(int effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->castingUnit == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->castingUnit == -1) throw EffectTreeException("Unable to get casting unit.");
	return ptr->castingUnit;
}

int EffectTree::setCastingPlayer(int castingPlayer)
{
	EffectTree::castingPlayer = castingPlayer;
	return castingPlayer;
}
int EffectTree::getCastingPlayer(int effect)
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
glm::vec2 EffectTree::getCasterLocation(int effect)
{
	EffectTree* ptr = findEffect(effect);
	while (!ptr->hasCasterLocation && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (!ptr->hasCasterLocation) throw EffectTreeException("Unable to get caster location.");
	return ptr->casterLocation;
}

int EffectTree::setSourceUnit(int sourceUnit)
{
	EffectTree::sourceUnit = sourceUnit;
	return sourceUnit;
}
int EffectTree::getSourceUnit(int effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->sourceUnit == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->sourceUnit == -1) throw EffectTreeException("Unable to get source unit.");
	return ptr->sourceUnit;
}

int EffectTree::setSourcePlayer(int sourcePlayer)
{
	EffectTree::sourcePlayer = sourcePlayer;
	return sourcePlayer;
}
int EffectTree::getSourcePlayer(int effect)
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
glm::vec2 EffectTree::getSourceLocation(int effect)
{
	EffectTree* ptr = findEffect(effect);
	while (!ptr->hasSourceLocation && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (!ptr->hasSourceLocation) throw EffectTreeException("Unable to get source location.");
	return ptr->sourceLocation;
}

int EffectTree::setTargetUnit(int targetUnit)
{
	EffectTree::targetUnit = targetUnit;
	return targetUnit;
}
int EffectTree::getTargetUnit(int effect)
{
	EffectTree* ptr = findEffect(effect);
	while (ptr->targetUnit == -1 && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (ptr->targetUnit == -1) throw EffectTreeException("Unable to get target unit.");
	return ptr->targetUnit;
}

int EffectTree::setTargetPlayer(int targetPlayer)
{
	EffectTree::targetPlayer = targetPlayer;
	return targetPlayer;
}
int EffectTree::getTargetPlayer(int effect)
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
glm::vec2 EffectTree::getTargetLocation(int effect)
{
	EffectTree* ptr = findEffect(effect);
	while (!ptr->hasTargetLocation && ptr->parent != nullptr)
	{
		ptr = ptr->parent;
	}
	if (!ptr->hasTargetLocation) throw EffectTreeException("Unable to get target location.");
	return ptr->targetLocation;
}

int EffectTree::setSpawnedUnit(int spawnedUnit)
{
	EffectTree::spawnedUnit = spawnedUnit;
	return spawnedUnit;
}
int EffectTree::getSpawnedUnit(int effect)
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


int EffectTree::getUnit(EffectUnit unit)
{
	switch (unit.unit)
	{
	case EffectUnitEnum::CASTER_UNIT:
		return getCastingUnit(unit.effectHandle);
	case EffectUnitEnum::SOURCE_UNIT:
		return getSourceUnit(unit.effectHandle);
	case EffectUnitEnum::TARGET_UNIT:
		return getTargetUnit(unit.effectHandle);
	case EffectUnitEnum::SPAWNED_UNIT:
		return getSpawnedUnit(unit.effectHandle);
	case EffectUnitEnum::NONE_UNIT:
		throw EffectTreeException("Attempting to get NONE unit.");
	default:
		throw EffectTreeException("Unrecognized unit enum.");
	}
}

int EffectTree::getPlayer(EffectPlayer player)
{
	switch (player.player)
	{
	case EffectPlayerEnum::CASTER_PLAYER:
		return getCastingPlayer(player.effectHandle);
	case EffectPlayerEnum::SOURCE_PLAYER:
		return getSourcePlayer(player.effectHandle);
	case EffectPlayerEnum::TARGET_PLAYER:
		return getTargetPlayer(player.effectHandle);
	case EffectPlayerEnum::NONE_PLAYER:
		throw EffectTreeException("Attempting to get NONE player.");
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
	switch (loc.location)
	{
	case EffectLocationEnum::CASTER_LOCATION:
		return getCasterLocation(loc.effectHandle);
	case EffectLocationEnum::SOURCE_LOCATION:
		return getSourceLocation(loc.effectHandle);
	case EffectLocationEnum::TARGET_LOCATION:
		return getTargetLocation(loc.effectHandle);
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
