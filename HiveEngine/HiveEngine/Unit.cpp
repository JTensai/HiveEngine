#include "Unit.h"

using namespace Hive;

Unit::Unit()
{
}

void Unit::init_unit(ActorHandle actor, DUnitHandle data, PlayerHandle player, glm::vec2 position)
{
	actorHandle = actor;
	dataHandle = data;

	player_owner = player;

	target = position;
	cached_position = position;
	new_position = position;

	cached_rotation = 270;
	new_rotation = 270;

	DUnit* unit = DUnit::getItem(dataHandle);
	Actor* actor_c = Actor::get_component(actorHandle);
	actor_c->set_position(position, unit->height);

	max_vitals = unit->vitalMax;
	cached_vitals = max_vitals;
	new_vitals = max_vitals;
	regen = unit->vitalRegen;

	height = unit->height;

	speed = unit->speed;
}

void Unit::update_component(float delta)
{
	Actor* actor = Actor::get_component(actorHandle);

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

Unit::~Unit()
{
}
