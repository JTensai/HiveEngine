#include "Unit.h"

using namespace Hive;

Unit::Unit()
{
}

void Unit::init_unit(int actor, int data, glm::vec2 position)
{
	actorHandle = actor;
	dataHandle = data;

	target = position;
	position_a = position;
	position_b = position;

	rotation_a = 270;
	rotation_b = 270;

	DUnit* unit = DUnit::getItem(dataHandle);
	Actor* actor_c = Actor::get_component(actorHandle);
	actor_c->set_position(position, unit->height);

	max_vitals = unit->vitalMax;
	vitals_a = max_vitals;
	vitals_b = max_vitals;
	regen = unit->vitalRegen;

	height = unit->height;

	speed = unit->speed;
}

void Unit::update_component(float delta, bool is_a)
{
	Actor* actor = Actor::get_component(actorHandle);

	new_position(is_a) = cached_position(is_a);
	new_rotation(is_a) = cached_rotation(is_a);
	new_vitals(is_a) = cached_vitals(is_a) + regen * delta;
	if (new_vitals(is_a).hp > max_vitals.hp) new_vitals(is_a).hp = max_vitals.hp;
	if (new_vitals(is_a).mana > max_vitals.mana) new_vitals(is_a).mana = max_vitals.mana;

	float diff = glm::distance(target, cached_position(is_a));
	float dist = speed * delta;
	if (diff != 0)
	{
		new_rotation(is_a) = std::atan2(target.y - cached_position(is_a).y, target.x - cached_position(is_a).x);
		if (diff < dist)
		{
			new_position(is_a) = target;
			actor->set_velocity(glm::vec2(0));
		}
		else
		{
			glm::vec2 velocity = glm::normalize(target - cached_position(is_a)) * speed;
			actor->set_velocity(velocity);
			new_position(is_a) = cached_position(is_a) + velocity * delta;
		}
	}

	actor->set_position(new_position(is_a), height);
	actor->set_rotation(new_rotation(is_a));
}

Unit::~Unit()
{
}
