#pragma once
/*
 ***************************
 * Particle System Component
 * The particle system component is used control one or more particle emitters without needing dozens of other components.
 * It is responsible for spawning, updating, destroying, and drawing all of its particles.
 ***************************
 */

#include <glm\glm.hpp>

namespace Hive
{

	class ParticleSystemComponent
	{
	public:
		ParticleSystemComponent();
		void update(float delta);
		void draw(const glm::mat4& VP);
		~ParticleSystemComponent();
	};

}