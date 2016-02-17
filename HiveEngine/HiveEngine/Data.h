#pragma once

#include <string>
#include <vector>

namespace Hive
{

#pragma region Enums
	enum EffectUnitEnum {
		CASTER_UNIT,
		SOURCE_UNIT,
		TARGET_UNIT,
		NONE_UNIT
	};

	enum EffectLocationEnum {
		CASTER_LOCATION,
		SOURCE_LOCATION,
		TARGET_LOCATION,
		NONE_LOCATION
	};

	enum EffectPlayerEnum {
		CASTER_PLAYER,
		SOURCE_PLAYER,
		TARGET_PLAYER,
		NEUTRAL_PLAYER,
		HOSTILE_PLAYER,
		NONE_PLAYER
	};

	enum Filter {
		ALLOWED,
		REQUIRED,
		EXCLUDED
	};

	enum EffectType {
		MODIFY_UNIT,
		SET,
		SET_BEHAVIOR,
		SEARCH,
		SPAWN_UNIT,
		SWITCH
	};

	enum CompareMethod {
		EQ,
		GT,
		GTE,
		LT,
		LTE,
		NEQ
	};

	enum VitalEnum {
		HP,
		MANA
	};

	enum VitalCompareMethod {
		CURRENT,
		DELTA,
		MAX,
		FRACTION
	};

	enum ValidatorType {
		BEHAVIOR_COUNT,
		COMBINE,
		COMPARE_VITAL,
		CONDITION,
		FILTER_UNIT,
		LOCATION_PATHABLE,
		LOCATION_RANGE,
		PLAYER
	};

	enum ValidatorCombineType {
		AND,
		OR,
		XOR
	};

	enum AbilityType {
		INSTANT,
		POINT_TARGET,
		UNIT_TARGET
	};
#pragma endregion
#pragma region Structs
	struct EffectList {
		int effectInitial;
		int effectPeriodic;
		int effectFinal;
		int effectExpire;
	};

	struct EffectUnit {
		int effectHandle;
		EffectUnitEnum unit;
	};

	struct EffectLocation {
		int effectHandle;
		EffectLocationEnum location;
	};

	struct EffectPlayer {
		int effectHandle;
		EffectPlayerEnum player;
	};

	struct Vitals {
		float
			hp,
			mana;
	};

	struct UnitFilter {
		Filter
			dead,
			invulnerable,
			missile,
			self,
			ally,
			enemy,
			neutral;
	};

	struct Charges {
		int
			max,
			start,
			use,
			regen;
		float cooldown;
	};

	struct Cost {
		Vitals vitals;
		Vitals vitalFraction;
		Charges charges;
		float cooldown;
	};

	struct Attributes {
		bool missile;
	};

	struct ValidatorConditionCase {
		int ifValidator;
		int thenValidator;
	};

	struct EffectSwitchCase {
		int ifValidator;
		int thenEffect;
	};
#pragma endregion

#pragma region Units
	struct DUnit {
		std::string name;
		Vitals
			vitalMax,
			vitalRegen;

		float speed;
		float collisionRadius;

		Attributes attributes;

		int actorDataHandle;
		std::vector<int> behaviorHandles;
		std::vector<int> abilityHandles;
	};
#pragma endregion

#pragma region Actors
	struct DActor {
		int modelHandle;
	};
#pragma endregion

#pragma region Abilities
	struct DAbility {
		AbilityType type;
		std::string name;
		std::string tooltip;
		int iconTextureHandle;
		Cost cost;
		EffectList effects;
		float range;
		UnitFilter targetFilter;
	};
#pragma endregion

#pragma region Behaviors
	struct DBehavior {
		std::string name;
		std::string tooltip;
		int iconTextureHandle;
		bool isVisible;
		Vitals
			vitalDelta,
			vitalRegenDelta;

		float
			duration,
			speedMultiplier;

		EffectList effects;
	};
#pragma endregion

#pragma region Validators
	struct DValidatorBase {
		ValidatorType type;
		bool negated;
	};

	struct DValidatorBehaviorCount : DValidatorBase {
		int behaviorDataHandle;
		CompareMethod method;
		int constant;
	};

	struct DValidatorCombine : DValidatorBase {
		ValidatorCombineType combineType;
		std::vector<int> handles;
	};

	struct DValidatorCompareVital : DValidatorBase {
		EffectUnit unit;
		VitalEnum vital;
		VitalCompareMethod vitalCompareMethod;
		CompareMethod method;
		EffectUnit unitToCompareTo;
		float constant;
	};
	struct DValidatorCondition : DValidatorBase {
		std::vector<ValidatorConditionCase> cases;
		int elseHandle;
	};
	struct DValidatorLocationRange : DValidatorBase {
		EffectLocation sourceLocation;
		EffectLocation destinationLocation;
		CompareMethod method;
		float constant;
	};
	struct DValidatorLocationPathable : DValidatorBase {
		EffectLocation location;
	};
	struct DValidatorFilterUnit : DValidatorBase {
		EffectUnit unit;
		UnitFilter filter;
		EffectUnit unitToFilterBy;
		EffectPlayer playerToFilterBy;
	};
	struct DValidatorPlayer : DValidatorBase {
		EffectPlayer player;
		EffectPlayer playerToCompareTo;
	};

	union DValidator {
		DValidatorBase dBase;
		DValidatorBehaviorCount dBehaviorCount;
		DValidatorCombine dCombine;
		DValidatorCompareVital dCompareVital;
		DValidatorCondition dCondition;
		DValidatorFilterUnit dFilterUnit;
		DValidatorLocationPathable dLocationPathable;
		DValidatorLocationRange dLocationRange;
		DValidatorPlayer dPlayer;

		DValidator() {}
		DValidator(const DValidator& o)
		{
			switch (o.dBase.type)
			{
			case BEHAVIOR_COUNT:
				dBehaviorCount = o.dBehaviorCount;
				break;
			case COMBINE:
				dCombine = o.dCombine;
				break;
			case COMPARE_VITAL:
				dCompareVital = o.dCompareVital;
				break;
			case CONDITION:
				dCondition = o.dCondition;
				break;
			case FILTER_UNIT:
				dFilterUnit = o.dFilterUnit;
				break;
			case LOCATION_PATHABLE:
				dLocationPathable = o.dLocationPathable;
				break;
			case LOCATION_RANGE:
				dLocationRange = o.dLocationRange;
				break;
			case PLAYER:
				dPlayer = o.dPlayer;
				break;
			}
		}
		~DValidator() {}
	};
#pragma endregion

#pragma region Effects
	struct DEffectBase {
		EffectType type;
		int validatorHandle;
	};

	struct DEffectModifyUnit : DEffectBase {
		EffectUnit unit;
		Vitals vitalsDelta;
	};

	struct DEffectSearch : DEffectBase {
		EffectLocation location;
		float radius;
		UnitFilter filter;
	};

	struct DEffectSet : DEffectBase {
		std::vector<int> effectHandles;
	};

	struct DEffectSetBehavior : DEffectBase {
		EffectUnit unit;
		int behaviorDataHandle;
		int amount;
		bool relative;
	};

	struct DEffectSpawnUnit : DEffectBase {
		int unitDataHandle;
		EffectPlayer owner;
		EffectLocation location;
	};

	struct DEffectSwitch : DEffectBase {
		std::vector<EffectSwitchCase> cases;
		int elseEffectHandle;
	};

	union DEffect {
		DEffectBase dBase;
		DEffectModifyUnit dModifyUnit;
		DEffectSearch dSearch;
		DEffectSet dSet;
		DEffectSetBehavior dSetBehavior;
		DEffectSpawnUnit dSpawnUnit;
		DEffectSwitch dSwitch;

		DEffect() {}
		DEffect(const DEffect& o)
		{
			switch (o.dBase.type)
			{
			case MODIFY_UNIT:
				dModifyUnit = o.dModifyUnit;
				break;
			case SEARCH:
				dSearch = o.dSearch;
				break;
			case SET:
				dSet = o.dSet;
				break;
			case SET_BEHAVIOR:
				dSetBehavior = o.dSetBehavior;
				break;
			case SPAWN_UNIT:
				dSpawnUnit = o.dSpawnUnit;
				break;
			case SWITCH:
				dSwitch = o.dSwitch;
				break;
			}
		}
		~DEffect() {}
	};
#pragma endregion

}