#pragma once

#include <vector>
#include <stdexcept>
#include <string>

#include <glm\glm.hpp>

#include "Exceptions.h"
#include "Data.h"
#include "Unit.h"

namespace Hive
{
	class EffectTree
	{
	private:
		DEffectHandle effect;

		UnitHandle castingUnit;
		PlayerHandle castingPlayer;
		bool hasCasterLocation;
		glm::vec2 casterLocation;

		UnitHandle sourceUnit;
		PlayerHandle sourcePlayer;
		bool hasSourceLocation;
		glm::vec2 sourceLocation;

		UnitHandle targetUnit;
		PlayerHandle targetPlayer;
		bool hasTargetLocation;
		glm::vec2 targetLocation;

		UnitHandle spawnedUnit;

		EffectTree* parent;
		std::vector<EffectTree*> children;
		int activeReferences;

		EffectTree* findEffect(DEffectHandle effect);
		EffectTree* findEffectDown(DEffectHandle effect);

	public:
		static void clean(EffectTree* effectTree);

		EffectTree();

		DEffectHandle setEffect(DEffectHandle effect);
		DEffectHandle getEffect();
		UnitHandle setCastingUnit(UnitHandle castingUnit);
		UnitHandle getCastingUnit(DEffectHandle effect);
		PlayerHandle setCastingPlayer(PlayerHandle castingPlayer);
		PlayerHandle getCastingPlayer(DEffectHandle effect);
		glm::vec2 setCasterLocation(glm::vec2 casterLocation);
		glm::vec2 getCasterLocation(DEffectHandle effect);
		UnitHandle setSourceUnit(UnitHandle sourceUnit);
		UnitHandle getSourceUnit(DEffectHandle effect);
		PlayerHandle setSourcePlayer(PlayerHandle sourcePlayer);
		PlayerHandle getSourcePlayer(DEffectHandle effect);
		glm::vec2 setSourceLocation(glm::vec2 sourceLocation);
		glm::vec2 getSourceLocation(DEffectHandle effect);
		UnitHandle setTargetUnit(UnitHandle targetUnit);
		UnitHandle getTargetUnit(DEffectHandle effect);
		PlayerHandle setTargetPlayer(PlayerHandle targetPlayer);
		PlayerHandle getTargetPlayer(DEffectHandle effect);
		glm::vec2 setTargetLocation(glm::vec2 targetLocation);
		glm::vec2 getTargetLocation(DEffectHandle effect);
		UnitHandle setSpawnedUnit(UnitHandle spawnedUnit);
		UnitHandle getSpawnedUnit(DEffectHandle effect);

		UnitHandle getUnit(EffectUnit unit);
		PlayerHandle getPlayer(EffectPlayer player);
		glm::vec2 getLocation(EffectLocation loc);

		EffectTree* addChild();

		~EffectTree();
	};
}