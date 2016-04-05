#pragma once

#include <string>
#include <vector>

#include <glm\glm.hpp>

#include "DataCollection.h"
#include "Asset.h"
#include "Exceptions.h"

namespace Hive
{
#pragma region Typedefs
	//typedef int Handle; This is defined in DataCollection.h

	typedef Handle DAbilityHandle;
	typedef Handle DActorHandle;
	typedef Handle DBehaviorHandle;
	typedef Handle DEffectHandle;
	typedef Handle DMaterialHandle;
	typedef Handle DModelHandle;
	typedef Handle DUnitHandle;
	typedef Handle DTextureHandle;
	typedef Handle DValidatorHandle;
	typedef Handle DUIElementHandle;

	typedef Handle ActorHandle;
	typedef Handle AIHandle;
	typedef Handle MeshHandle;
	typedef Handle UnitHandle;
	typedef Handle PlayerHandle;
	

	const PlayerHandle LOCAL_PLAYER = 0;
	const PlayerHandle NEUTRAL_PLAYER = 1;
	const PlayerHandle HOSTILE_PLAYER = 2;
#pragma endregion
#pragma region Enums
	enum class EffectUnitEnum {
		CASTER_UNIT,
		SOURCE_UNIT,
		TARGET_UNIT,
		SPAWNED_UNIT,
		NONE_UNIT
	};

	enum class EffectLocationEnum {
		CASTER_LOCATION,
		SOURCE_LOCATION,
		TARGET_LOCATION,
		NONE_LOCATION
	};

	enum class EffectPlayerEnum {
		CASTER_PLAYER,
		SOURCE_PLAYER,
		TARGET_PLAYER,
		LOCAL_PLAYER,
		NEUTRAL_PLAYER,
		HOSTILE_PLAYER,
		NONE_PLAYER
	};

	enum class Filter {
		ALLOWED,
		REQUIRED,
		EXCLUDED
	};

	enum class EffectType {
		MODIFY_UNIT,
		SET,
		SET_BEHAVIOR,
		SEARCH,
		SPAWN_UNIT,
		SWITCH
	};

	enum class CompareMethod {
		EQ,
		GT,
		GTE,
		LT,
		LTE,
		NEQ
	};

	enum class VitalEnum {
		HP,
		MANA
	};

	enum class VitalCompareMethod {
		CURRENT,
		DELTA,
		MAX,
		FRACTION
	};

	enum class ValidatorType {
		BEHAVIOR_COUNT,
		COMBINE,
		COMPARE_VITAL,
		CONDITION,
		FILTER_UNIT,
		LOCATION_PATHABLE,
		LOCATION_RANGE,
		PLAYER
	};

	enum class ValidatorCombineType {
		AND,
		OR,
		XOR
	};

	enum class AbilityType {
		INSTANT,
		POINT_TARGET,
		UNIT_TARGET
	};

	enum class ActorEvent {
		ACTOR_CREATED,
		ACTOR_DESTROYED,
		ABILITY_STAGE,
		BEHAVIOR_STAGE,
		UNIT_EVENT
	};

	enum class AbilityStages {
		START_CAST,
		FINISH_CAST,
		START_CHANNEL,
		FINISH_CHANNEL,
		FINISHED,
		ANY
	};

	enum class BehaviorStages {
		INITIAL,
		PERIOD,
		EXPIRED,
		REFRESHED,
		FINAL,
		ANY
	};

	enum class UnitEvent {
		BIRTH,
		DEATH,
		REVIVE
	};

	enum class ActorAction {
		CREATE_ACTOR,
		DESTROY_ACTOR,
		SET_SCALE
	};

#pragma endregion
#pragma region Structs
	struct Order
	{
		DAbilityHandle ability_handle;
		AbilityType type;
		UnitHandle targetUnit;
		glm::vec2 targetPoint;
	};

	struct EffectList
	{
		DEffectHandle effectInitial;
		DEffectHandle effectPeriodic;
		DEffectHandle effectFinal;
		DEffectHandle effectExpire;
	};

	struct EffectUnit
	{
		DEffectHandle effectHandle;
		EffectUnitEnum unit;
	};

	struct EffectLocation
	{
		DEffectHandle effectHandle;
		EffectLocationEnum location;
	};

	struct EffectPlayer
	{
		DEffectHandle effectHandle;
		EffectPlayerEnum player;
	};

	struct Vitals
	{
		float
			hp,
			mana;

		Vitals operator-() const { return Vitals{ -hp, -mana }; }
		Vitals operator*(float f) const { return Vitals{ hp * f, mana * f }; }
		Vitals operator+(const Vitals& o) const { return Vitals{ hp + o.hp, mana + o.mana }; }
		Vitals operator-(const Vitals& o) const { return *this + -o; }
		bool operator>(const Vitals& o) const { return hp > o.hp && mana > o.mana; }
		bool operator>=(const Vitals& o) const { return hp >= o.hp && mana >= o.mana; }
		bool operator<(const Vitals& o) const { return hp < o.hp && mana < o.mana; }
		bool operator<=(const Vitals& o) const { return hp <= o.hp && mana <= o.mana; }
		bool operator==(const Vitals& o) const { return hp == o.hp && mana == o.mana; }
		void operator*=(float f) { hp *= f; mana *= f; }
		void operator+=(const Vitals& o) { hp += o.hp; mana += o.mana; }
	};

	struct UnitFilter
	{
		Filter
			dead,
			invulnerable,
			missile,
			self,
			ally,
			enemy,
			neutral;
	};

	struct Charges
	{
		int
			max,
			start,
			use,
			regen;
		float cooldown;
	};

	struct Cost
	{
		Vitals vitals;
		Vitals vitalFraction;
		Charges charges;
		float cooldown;
	};

	struct Attributes
	{
		bool missile;
	};

	struct ValidatorConditionCase
	{
		DValidatorHandle ifValidator;
		DValidatorHandle thenValidator;
	};

	struct EffectSwitchCase
	{
		DValidatorHandle ifValidator;
		DEffectHandle thenEffect;
	};

	struct AbilityInstance
	{
		DAbilityHandle ability;
		float cooldown;
		int charges;
		float charge_cooldown;
		Cost cost;
	};

	struct BehaviorInstance
	{
		//TODO
	};
#pragma endregion

#pragma region Units
	class DUnit : public DataCollection<DUnit>
	{
	public:
		std::string name;
		Vitals
			vitalMax,
			vitalRegen;

		float height;
		float speed;
		float collisionRadius;

		Attributes attributes;

		DActorHandle actorDataHandle;
		std::vector<DBehaviorHandle> behaviorHandles;
		std::vector<DAbilityHandle> abilityHandles;
	};
#pragma endregion

#pragma region Abilities
	class DAbility : public DataCollection<DAbility>
	{
	public:
		AbilityType type;
		std::string name;
		std::string tooltip;
		DTextureHandle iconTextureHandle;
		Cost cost;
		Charges charges;
		EffectList effects;
		float range;
		UnitFilter targetFilter;
	};
#pragma endregion

#pragma region Actors
	class DActor : public DataCollection<DActor>
	{
	public:
		DModelHandle dModelHandle;
		DMaterialHandle dMaterialHandle;
	};
#pragma endregion

#pragma region Behaviors
	class DBehavior : public DataCollection<DBehavior>
	{
	public:
		std::string name;
		std::string tooltip;
		DTextureHandle icon_texture_handle;
		bool is_visible;
		Vitals
			vital_delta,
			vital_regen_delta;

		float
			duration,
			period,
			speed_multiplier;
		int stack_decay;
		int max_periods;
		EffectList effects;
	};
#pragma endregion

#pragma region Validators
	struct DValidatorBase {
		ValidatorType type;
		bool negated;
	};

	struct DValidatorBehaviorCount : DValidatorBase {
		DBehaviorHandle behaviorDataHandle;
		CompareMethod method;
		int constant;
	};

	struct DValidatorCombine : DValidatorBase {
		ValidatorCombineType combineType;
		std::vector<DValidatorHandle> handles;
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
		DValidatorHandle elseHandle;
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

	union DValidatorUnion {
		DValidatorBase dBase;
		DValidatorBehaviorCount dBehaviorCount;
		DValidatorCombine dCombine;
		DValidatorCompareVital dCompareVital;
		DValidatorCondition dCondition;
		DValidatorFilterUnit dFilterUnit;
		DValidatorLocationPathable dLocationPathable;
		DValidatorLocationRange dLocationRange;
		DValidatorPlayer dPlayer;

		DValidatorUnion() {}
		DValidatorUnion(const DValidatorUnion& o)
		{
			switch (o.dBase.type)
			{
			case ValidatorType::BEHAVIOR_COUNT:
				dBehaviorCount = o.dBehaviorCount;
				break;
			case ValidatorType::COMBINE:
				dCombine = o.dCombine;
				break;
			case ValidatorType::COMPARE_VITAL:
				dCompareVital = o.dCompareVital;
				break;
			case ValidatorType::CONDITION:
				dCondition = o.dCondition;
				break;
			case ValidatorType::FILTER_UNIT:
				dFilterUnit = o.dFilterUnit;
				break;
			case ValidatorType::LOCATION_PATHABLE:
				dLocationPathable = o.dLocationPathable;
				break;
			case ValidatorType::LOCATION_RANGE:
				dLocationRange = o.dLocationRange;
				break;
			case ValidatorType::PLAYER:
				dPlayer = o.dPlayer;
				break;
			}
		}
		~DValidatorUnion() {}
	};

	class DValidator : public DataCollection<DValidator>
	{
	public:
		DValidatorUnion u;
	};
#pragma endregion

#pragma region Effects
	struct DEffectBase {
		EffectType type;
		DValidatorHandle validatorHandle;
	};

	struct DEffectModifyUnit : DEffectBase {
		EffectUnit unit;
		Vitals vitalsDelta;
	};

	struct DEffectSearch : DEffectBase {
		EffectLocation location;
		float radius;
		DEffectHandle effect;
		UnitFilter filter;
	};

	struct DEffectSet : DEffectBase {
		std::vector<DEffectHandle> effectHandles;
	};

	struct DEffectSetBehavior : DEffectBase {
		EffectUnit unit;
		DBehaviorHandle behaviorDataHandle;
		int amount;
		bool relative;
	};

	struct DEffectSpawnUnit : DEffectBase {
		DUnitHandle unitDataHandle;
		EffectPlayer owner;
		EffectLocation location;
	};

	struct DEffectSwitch : DEffectBase {
		std::vector<EffectSwitchCase> cases;
		DEffectHandle elseEffectHandle;
	};

	union DEffectUnion {
		DEffectBase dBase;
		DEffectModifyUnit dModifyUnit;
		DEffectSearch dSearch;
		DEffectSet dSet;
		DEffectSetBehavior dSetBehavior;
		DEffectSpawnUnit dSpawnUnit;
		DEffectSwitch dSwitch;

		DEffectUnion() {}
		DEffectUnion(const DEffectUnion& o)
		{
			switch (o.dBase.type)
			{
			case EffectType::MODIFY_UNIT:
				dModifyUnit = o.dModifyUnit;
				break;
			case EffectType::SEARCH:
				dSearch = o.dSearch;
				break;
			case EffectType::SET:
				dSet = o.dSet;
				break;
			case EffectType::SET_BEHAVIOR:
				dSetBehavior = o.dSetBehavior;
				break;
			case EffectType::SPAWN_UNIT:
				dSpawnUnit = o.dSpawnUnit;
				break;
			case EffectType::SWITCH:
				dSwitch = o.dSwitch;
				break;
			}
		}

		DEffectUnion operator=(const DEffectUnion& o)
		{
			switch (o.dBase.type)
			{
			case EffectType::MODIFY_UNIT:
				dModifyUnit = o.dModifyUnit;
				break;
			case EffectType::SEARCH:
				dSearch = o.dSearch;
				break;
			case EffectType::SET:
				dSet = o.dSet;
				break;
			case EffectType::SET_BEHAVIOR:
				dSetBehavior = o.dSetBehavior;
				break;
			case EffectType::SPAWN_UNIT:
				dSpawnUnit = o.dSpawnUnit;
				break;
			case EffectType::SWITCH:
				dSwitch = o.dSwitch;
				break;
			}
			return *this;
		}
		~DEffectUnion() {}
	};

	class DEffect : public DataCollection<DEffect>
	{
	public:
		DEffectUnion u;
	};
#pragma endregion



#pragma region UI
	class DUIElement : public DataCollection<DUIElement>
	{
	public:
		glm::vec2 position;
		glm::vec2 size;
		int z_index;
		DTextureHandle texture;
	};

#pragma endregion

#pragma region Assets
	class Model;
	//typedef DataCollection<AssetData<Model>> DModel;
	class DModel : public AssetData<Model, DModel>, public DataCollection<DModel> {};

	class Texture;
	//typedef DataCollection<AssetData<Texture>> DTexture;
	class DTexture : public AssetData<Texture, DTexture>, public DataCollection<DTexture> {};
#pragma endregion

}