#pragma once

#include <vector>
#include <stdexcept>
#include <string>

#include <glm\glm.hpp>

#include "Exceptions.h"

namespace Hive
{
	class EffectTree
	{
	private:
		int effect;

		int castingUnit;
		int castingPlayer;

		int sourceUnit;
		int sourcePlayer;
		bool hasSourceLocation;
		glm::vec2 sourceLocation;

		int targetUnit;
		int targetPlayer;
		bool hasTargetLocation;
		glm::vec2 targetLocation;

		int spawnedUnit;

		EffectTree* parent;
		std::vector<EffectTree*> children;
		int activeReferences;

		EffectTree* findEffect(int effect);
		EffectTree* findEffectDown(int effect);

	public:
		static void clean(EffectTree* effectTree);

		EffectTree();

		int setEffect(int effect);
		int getEffect();
		int setCastingUnit(int castingUnit);
		int getCastingUnit(int effect);
		int setCastingPlayer(int castingPlayer);
		int getCastingPlayer(int effect);
		int setSourceUnit(int sourceUnit);
		int getSourceUnit(int effect);
		glm::vec2 setSourceLocation(glm::vec2 sourceLocation);
		glm::vec2 getSourceLocation(int effect);
		int setTargetUnit(int targetUnit);
		int getTargetUnit(int effect);
		int setTargetPlayer(int targetPlayer);
		int getTargetPlayer(int effect);
		glm::vec2 setTargetLocation(glm::vec2 targetLocation);
		glm::vec2 getTargetLocation(int effect);
		int setSpawnedUnit(int spawnedUnit);
		int getSpawnedUnit(int effect);

		EffectTree* addChild();

		~EffectTree();
	};
}