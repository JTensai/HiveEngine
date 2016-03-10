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

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

#include "Component.h"
#include "Unit.h"
#include "Model.h"

namespace Hive
{

	class Actor : public DrawableComponent<Actor>
	{
	private:
		static GLuint actor_shader_handle;
		glm::vec3 position;
		glm::vec3 spin;
		glm::vec3 rotation;
		glm::mat4 world_transform;
		int d_model_handle;

	public:
		Actor();

		void loadFromData(int handle);

		static void setShader(GLuint shader);
		static void predraw();
		static void postdraw();

		/*
		Update will handle things like the actor's animation and timed events.
		*/
		void update_component(float delta, bool is_a);

		/*
		Draw multiplies the given view-projection matrix by its own world transform and then calls its model's draw function passing the newly formed world-view-projection matrix.
		*/
		void draw_component(const glm::mat4& VP);

		~Actor();
	};

}