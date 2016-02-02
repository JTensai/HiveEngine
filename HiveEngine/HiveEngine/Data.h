#pragma once

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
#pragma endregion

#pragma region Units
struct DUnit {
	char* name;
	Vitals
		vitalMax,
		vitalRegen;

	float speed;

	Attributes attributes;

	int actorDataHandle;
	int behaviorHandles[5];
	int abilityHandles[5];
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
	char* name;
	char* tooltip;
	int iconTextureHandle;
	Cost cost;
	int	effectInitialHandle;
	float range;
	UnitFilter targetFilter;
};
#pragma endregion

#pragma region Behaviors
struct DBehavior {
	char* name;
	char* tooltip;
	int iconTextureHandle;
	bool isVisible;
	Vitals
		vitalDelta,
		vitalRegenDelta;

	float
		duration,
		speedMultiplier;

	int
		effectInitialHandle,
		effectPeriodicHandle,
		effectFinalHandle,
		effectExpireHandle;
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
	int validatorAHandle;
	int validatorBHandle;
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
	int ifValidatorHandle;
	int thenValidatorHandle;
	int elseValidatorHandle;
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
	int effectHandles[5];
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
	int validatorHandle;
	int trueEffectHandle;
	int falseEffectHandle;
};

union DEffect {
	DEffectBase dBase;
	DEffectModifyUnit dModifyUnit;
	DEffectSearch dSearch;
	DEffectSet dSet;
	DEffectSetBehavior dSetBehavior;
	DEffectSpawnUnit dSpawnUnit;
	DEffectSwitch dSwitch;
};
#pragma endregion