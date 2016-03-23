#pragma once

#include <string>
#include <stdexcept>

#include "Data.h"
#include "EffectTree.h"
#include "Exceptions.h"
#include "Unit.h"
#include "IComponentManager.h"
#include "ServiceLocator.h"

namespace Hive
{
	class Effects
	{
	private:
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

