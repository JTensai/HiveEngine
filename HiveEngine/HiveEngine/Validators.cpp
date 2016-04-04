#include "Validators.h"

using namespace Hive;

bool Validators::validate(EffectTree* effectTree, DValidator* validator)
{
	switch (validator->u.dBase.type)
	{
	case ValidatorType::BEHAVIOR_COUNT:
		return validate(effectTree, (DValidatorBehaviorCount*) &(validator->u));
		break;
	case ValidatorType::COMBINE:
		return validate(effectTree, (DValidatorCombine*)&(validator->u));
		break;
	case ValidatorType::COMPARE_VITAL:
		return validate(effectTree, (DValidatorCompareVital*)&(validator->u));
		break;
	case ValidatorType::CONDITION:
		return validate(effectTree, (DValidatorCondition*)&(validator->u));
		break;
	case ValidatorType::FILTER_UNIT:
		return validate(effectTree, (DValidatorFilterUnit*)&(validator->u));
		break;
	case ValidatorType::LOCATION_PATHABLE:
		return validate(effectTree, (DValidatorLocationPathable*)&(validator->u));
		break;
	case ValidatorType::LOCATION_RANGE:
		return validate(effectTree, (DValidatorLocationRange*)&(validator->u));
		break;
	case ValidatorType::PLAYER:
		return validate(effectTree, (DValidatorPlayer*)&(validator->u));
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