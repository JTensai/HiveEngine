#pragma once

#include <string>
#include <stdexcept>
#include <vector>

#include <glm\glm.hpp>

#include "Data.h"
#include "EffectTree.h"
#include "Exceptions.h"
#include "Unit.h"
#include "IComponentManager.h"
#include "ServiceLocator.h"
#include "ObjectPool.h"

namespace Hive
{
	class EffectTree;

	class Effects
	{
	private:
		//Shouldn't need this any more, but I'm not going to delete it, just in case.
		//static std::vector<UnitHandle> get_units_in_area(glm::vec2 location, float radius);

		static void eModifyUnit(EffectTree* effectTree, DEffectModifyUnit* effect);
		static void eSearch(EffectTree* effectTree, DEffectSearch* effect);
		static void eSet(EffectTree* effectTree, DEffectSet* set);
		static void eSetBehavior(EffectTree* effectTree, DEffectSetBehavior* effect);
		static void eSpawnUnit(EffectTree* effectTree, DEffectSpawnUnit* effect);
		static void eSwitch(EffectTree* effectTree, DEffectSwitch* effect);

	public:
		static void launchEffect(EffectTree* effectTree);
	};
}

