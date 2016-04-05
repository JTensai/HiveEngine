#include "Unit.h"
#include <glm/glm.hpp>
#include <vector>

using namespace Hive;

Unit::Unit()
{
}

void Unit::init_unit(UnitHandle self, ActorHandle actor, DUnitHandle data, PlayerHandle player, glm::vec2 position)
{
	Unit::self = self;
	actor_handle = actor;
	data_handle = data;
	ai_handle = -1;

	player_owner = player;

	target = position;
	cached_position = position;

	cached_rotation = 270;

	DUnit* unit = DUnit::getItem(data_handle);
	Actor* actor_c = Actor::get_component(actor_handle);
	actor_c->set_position(position, unit->height);

	max_vitals = unit->vitalMax;
	cached_vitals = max_vitals;
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

	change_vitals(regen * delta);
	float diff = glm::distance(target, cached_position);
	float dist = speed * delta;
	if (diff != 0)
	{
		cached_rotation = std::atan2(target.y - cached_position.y, target.x - cached_position.x);
		if (diff < dist)
		{
			cached_position = target;
			actor->set_velocity(glm::vec2(0));
		}
		else
		{
			glm::vec2 velocity = glm::normalize(target - cached_position) * speed;
			actor->set_velocity(velocity);
			cached_position = cached_position + velocity * delta;
		}
	}

	actor->set_position(cached_position, height);
	actor->set_rotation(cached_rotation);
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

OrderResponse Unit::issue_order(Order& order)
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
	if (ability == nullptr) return OrderResponse::ABILITY_NOT_FOUND;
	if (ability->cooldown > 0) return OrderResponse::ABILITY_ON_COOLDOWN;
	if (ability->charges < ability->cost.charges.use) return OrderResponse::NOT_ENOUGH_CHARGES;
	Unit* target = nullptr;
	if (order.type == AbilityType::UNIT_TARGET && (target = Unit::get_component(order.targetUnit)) == nullptr) return OrderResponse::NO_TARGET;
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
	switch (order.type)
	{
	case AbilityType::INSTANT:
		break;
	case AbilityType::POINT_TARGET:
		effect_tree->setTargetLocation(order.targetPoint);
		break;
	case AbilityType::UNIT_TARGET:
		effect_tree->setTargetUnit(order.targetUnit);
		effect_tree->setTargetLocation(target->cached_position);
		effect_tree->setTargetPlayer(target->player_owner);
		break;
	default:
		throw UnknownOrderTypeException();
	}

	Effects::launchEffect(effect_tree);
}

void Unit::preupdate()
{
	std::vector<Unit*> units = std::vector<Unit*>();

	int i = 0;
	int num = 0;
	int cap = pool.capacity();
	int num_used = pool.get_num_in_use();
	for (; i < cap && num < num_used; ++i)
	{
		if (pool.is_used(i))
		{
			++num;
			units.push_back(pool.get(i));
		}
	}

	ServiceLocator::get_quadtree()->populate_tree(units);
	ServiceLocator::get_quadtree()->collide();//Ideally what gets done in this call is that units that are colliding 
		//have a flag set that will not allow them to update their location in the subsequent call to update_component.
	
}

void Unit::set_vitals(Vitals vitals)
{
	cached_vitals = vitals;

	if (cached_vitals.hp > max_vitals.hp) cached_vitals.hp = max_vitals.hp;
	if (cached_vitals.mana > max_vitals.mana) cached_vitals.mana = max_vitals.mana;

	/*if (cached_vitals.hp <= 0)
	{
		Unit::destroy_component(self);
		Actor::destroy_component(actor_handle);
		if (ai_handle != -1) AIComponent::destroy_component(ai_handle);
	}*/
}

void Unit::change_vitals(Vitals delta)
{
	cached_vitals = cached_vitals + delta;

	if (cached_vitals.hp > max_vitals.hp) cached_vitals.hp = max_vitals.hp;
	if (cached_vitals.mana > max_vitals.mana) cached_vitals.mana = max_vitals.mana;

	/*if (cached_vitals.hp <= 0)
	{
		Unit::destroy_component(self);
		Actor::destroy_component(actor_handle);
		if (ai_handle != -1) AIComponent::destroy_component(ai_handle);
	}*/
}

Unit::~Unit()
{
}
