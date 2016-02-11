#pragma once
/*
 ***************************
 * Movement Component
 * The movement component is responsible for changing an actor's location in the game world, pathing, and collision.
 * Movement components will be given locations that they are to move to by either an Ability Component via an AI component or directly from a player input component.
 * The movement component sees to it that the entity gets there.
 * The movement component notifies the entity's actor when movement is started, stopped, or the direction changes.
 * Methods should be exposed for other systems to query about the entity's movement state.
 ***************************
 */

namespace Hive
{

	class MovementComponent
	{
	private:
		int _actorHandle;
	public:
		MovementComponent();
		void update(float delta);
		~MovementComponent();
	};

}