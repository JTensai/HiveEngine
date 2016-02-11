#pragma once
/*
 ***************************
 * Actor
 * This contains all data, and handles all logic, relating to an entity's physical location in the game world.
 * This includes rendering the entity in the game world.
 * Actors will have an event/message board system whereby they can be notified when events regarding their entity occur.
 * This event system will be used to play animations, spawn other actors, spawn particle systems, destroy the actor, etc.
 * Methods should be exposed for other systems to query about the entity's location, rotation, etc.
 * When a unit dies it notifies its actor.
 * It is then the responsibility of the actor to destroy itself.
 * This is because the actor may have some events it needs to take care of before it is destroyed.
 ***************************
 */

#include <glm/glm.hpp>

class Actor
{
private:
	glm::mat4 _worldTransform;
	int _modelHandle;

public:
	Actor();

	/*
	Draw multiplies the given view-projection matrix by its own world transform and then calls its model's draw function passing the newly formed world-view-projection matrix.
	*/
	void draw(const glm::mat4& VP);

	/*
	Update will handle things like the actor's animation and timed events.
	*/
	void update(float delta);

	~Actor();
};

