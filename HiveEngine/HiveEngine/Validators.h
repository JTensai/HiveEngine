#pragma once

#include "Data.h"
#include "EffectTree.h"
#include "Exceptions.h"

namespace Hive
{
	class Validators
	{
	private:
		static bool validate(EffectTree* effectTree, DValidatorBehaviorCount* validator);
		static bool validate(EffectTree* effectTree, DValidatorCombine* validator);
		static bool validate(EffectTree* effectTree, DValidatorCompareVital* validator);
		static bool validate(EffectTree* effectTree, DValidatorCondition* validator);
		static bool validate(EffectTree* effectTree, DValidatorFilterUnit* validator);
		static bool validate(EffectTree* effectTree, DValidatorLocationPathable* validator);
		static bool validate(EffectTree* effectTree, DValidatorLocationRange* validator);
		static bool validate(EffectTree* effectTree, DValidatorPlayer* validator);
	public:
		static bool validate(EffectTree* effectTree, DValidator* validator);
	};
}