#include "Validators.h"

using namespace Hive;

bool Validators::validate(EffectTree* effectTree, DValidator* validator)
{
	switch (validator->u.dBase.type)
	{
	case ValidatorType::BEHAVIOR_COUNT:
		return validate(effectTree, &(validator->u.dBehaviorCount));
		break;
	case ValidatorType::COMBINE:
		return validate(effectTree, &(validator->u.dCombine));
		break;
	case ValidatorType::COMPARE_VITAL:
		return validate(effectTree, &(validator->u.dCompareVital));
		break;
	case ValidatorType::CONDITION:
		return validate(effectTree, &(validator->u.dCondition));
		break;
	case ValidatorType::FILTER_UNIT:
		return validate(effectTree, &(validator->u.dFilterUnit));
		break;
	case ValidatorType::LOCATION_PATHABLE:
		return validate(effectTree, &(validator->u.dLocationPathable));
		break;
	case ValidatorType::LOCATION_RANGE:
		return validate(effectTree, &(validator->u.dLocationRange));
		break;
	case ValidatorType::PLAYER:
		return validate(effectTree, &(validator->u.dPlayer));
		break;
	default:
		throw ValidatorException("Unknown validator type encountered.");
	}
}

bool Validators::validate(EffectTree* effectTree, DValidatorBehaviorCount* validator)
{
	throw UnimplementedException();
}

bool Validators::validate(EffectTree* effectTree, DValidatorCombine* validator)
{
	throw UnimplementedException();
}

bool Validators::validate(EffectTree* effectTree, DValidatorCompareVital* validator)
{
	throw UnimplementedException();
}

bool Validators::validate(EffectTree* effectTree, DValidatorCondition* validator)
{
	throw UnimplementedException();
}

bool Validators::validate(EffectTree* effectTree, DValidatorFilterUnit* validator)
{
	throw UnimplementedException();
}

bool Validators::validate(EffectTree* effectTree, DValidatorLocationPathable* validator)
{
	throw UnimplementedException();
}

bool Validators::validate(EffectTree* effectTree, DValidatorLocationRange* validator)
{
	throw UnimplementedException();
}

bool Validators::validate(EffectTree* effectTree, DValidatorPlayer* validator)
{
	throw UnimplementedException();
}