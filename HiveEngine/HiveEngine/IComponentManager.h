#pragma once
/*
 ***************************
 * Component Manager
 * The component manager is responsible for tracking all the components that make up the entities in the game world.
 * These components should be stored contiguously in memory by type to enable cache-friendly iteration for update and draw calls, which are the responsiblity of the component manager.
 ***************************
 */

#include <glm\glm.hpp>

namespace Hive
{
	class IComponentManager
	{
	public:
		virtual void initialize() = 0;
		virtual void load() = 0;
		virtual void update_free(float delta) = 0;
		virtual void update_fixed(float delta) = 0;
		virtual int spawn_unit(glm::vec2 position, int dunit_handle, int player) = 0;
		virtual int spawn_ai_unit(glm::vec2 position, int dunit_handle, int player) = 0;
		virtual void attach_player_input(int unit_handle) = 0;
		virtual void draw(const glm::mat4& VP) = 0;

		virtual ~IComponentManager() {}
	};
}