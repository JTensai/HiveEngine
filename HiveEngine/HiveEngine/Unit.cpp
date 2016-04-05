#include "Unit.h"

using namespace Hive;

Unit::Unit()
{
}

void Unit::init_unit(UnitHandle self, ActorHandle actor, DUnitHandle data, PlayerHandle player, glm::vec2 position)
{
	Unit::self = self;
	actor_handle = actor;
	data_handle = data;

	player_owner = player;

	target = position;
	cached_position = position;
	new_position = position;

	cached_rotation = 270;
	new_rotation = 270;

	DUnit* unit = DUnit::getItem(data_handle);
	Actor* actor_c = Actor::get_component(actor_handle);
	actor_c->set_position(position, unit->height);

	max_vitals = unit->vitalMax;
	cached_vitals = max_vitals;
	new_vitals = max_vitals;
	regen = unit->vitalRegen;

	height = unit->height;

	speed = unit->speed;

	abilities = std::vector<AbilityInstance>(unit->abilityHandles.size());
	for (int i = 0; i < abilities.size(); i++)
	{
		abilities[i].ability = unit->abilityHandles[i];
		DAbility* ability = DAbility::getItem(abilities[i].ability);

		abilities[i].cost = ability->cost;
		abilities[i].charges = abilities[i].cost.charges.start;
		abilities[i].charge_cooldown = abilities[i].cost.charges.cooldown;
		abilities[i].cooldown = 0;
	}
}

void Unit::update_component(float delta)
{
	Actor* actor = Actor::get_component(actor_handle);

	update_abilities(delta);

	new_vitals = cached_vitals + regen * delta;
	if (new_vitals.hp > max_vitals.hp) new_vitals.hp = max_vitals.hp;
	if (new_vitals.mana > max_vitals.mana) new_vitals.mana = max_vitals.mana;

	float diff = glm::distance(target, cached_position);
	float dist = speed * delta;
	if (diff != 0)
	{
		new_rotation = std::atan2(target.y - cached_position.y, target.x - cached_position.x);
		if (diff < dist)
		{
			new_position = target;
			actor->set_velocity(glm::vec2(0));
		}
		else
		{
			glm::vec2 velocity = glm::normalize(target - cached_position) * speed;
			actor->set_velocity(velocity);
			new_position = cached_position + velocity * delta;
		}
	}

	actor->set_position(new_position, height);
	actor->set_rotation(new_rotation);

	cached_position = new_position;
	cached_rotation = new_rotation;
	cached_vitals = new_vitals;
}

void Unit::update_abilities(float delta)
{
	for (int i = 0; i < abilities.size(); i++)
	{
		AbilityInstance& ability = abilities[i];

		//Cooldown
		if (ability.cooldown != 0) ability.cooldown -= delta;

		//Charge cooldown
		if (ability.charges != ability.cost.charges.max)
		{
			if (ability.charge_cooldown > 0) ability.charge_cooldown -= delta;
			if (ability.charge_cooldown < 0)
			{
				ability.charge_cooldown = ability.cost.charges.cooldown;
				ability.charges += ability.cost.charges.regen;
				if ((ability.cost.charges.regen < 0 && ability.charges < ability.cost.charges.max) ||
					(ability.cost.charges.regen > 0 && ability.charges > ability.cost.charges.max))
				{
					ability.charges = ability.cost.charges.max;
				}
			}
		}
	}
}

void Unit::issue_order(Order& order)
{
	AbilityInstance* ability = nullptr;
	for (int i = 0; i < abilities.size(); i++)
	{
		if (abilities[i].ability == order.ability_handle)
		{
			ability = &abilities[i];
			break;
		}
	}
	if (ability == nullptr) throw AbilityNotFoundException();
	if (ability->cooldown > 0) throw AbilityOnCooldownException();
	if (ability->charges < ability->cost.charges.use) throw NotEnoughChargesException();
	//TODO: further validate unit's capability to use ability

	DAbility* dability = DAbility::getItem(ability->ability);

	//Pay cost
	ability->charges -= ability->cost.charges.use;
	ability->cooldown = ability->cost.cooldown;
	//TODO: pay vital cost

	EffectTree* effect_tree = new EffectTree();

	effect_tree->setEffect(dability->effects.effectInitial);

	effect_tree->setCastingUnit(self);
	effect_tree->setCastingPlayer(player_owner);
	effect_tree->setCasterLocation(cached_position);
	
	effect_tree->setSourceUnit(self);
	effect_tree->setSourcePlayer(player_owner);
	effect_tree->setSourceLocation(cached_position);

	Unit* target = nullptr;
	switch (order.type)
	{
	case AbilityType::INSTANT:
		break;
	case AbilityType::POINT_TARGET:
		effect_tree->setTargetLocation(order.targetPoint);
		break;
	case AbilityType::UNIT_TARGET:
		target = Unit::get_component(order.targetUnit);
		if (target == nullptr) throw NoTargetException();
		effect_tree->setTargetUnit(order.targetUnit);
		effect_tree->setTargetLocation(target->cached_position);
		effect_tree->setTargetPlayer(target->player_owner);
		break;
	default:
		throw UnknownOrderTypeException();
	}

	Effects::launchEffect(effect_tree);
}

Unit::~Unit()
{
}
