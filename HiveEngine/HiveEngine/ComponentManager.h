#pragma once

#include <algorithm>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "AbilityComponent.h"
#include "Actor.h"
#include "AIComponent.h"
#include "BehaviorComponent.h"
#include "MovementComponent.h"
#include "ParticleSystemComponent.h"
#include "VitalsComponent.h"
#include "IComponentManager.h"
#include "ObjectPool.h"

namespace Hive
{

	class ComponentManager : public IComponentManager
	{
	private:
		ObjectPool<AbilityComponent> abilityComponents;
		ObjectPool<Actor> actors;
		ObjectPool<AIComponent> aiComponents;
		ObjectPool<BehaviorComponent> behaviorComponents;
		ObjectPool<MovementComponent> movementComponents;
		ObjectPool<ParticleSystemComponent> particleSystemComponents;
		ObjectPool<PlayerInputComponent> playerInputComponents;
		ObjectPool<VitalsComponent> vitalsComponents;

	public:
		ComponentManager();

		AbilityComponent* getAbilityComponent(int id);
		AbilityComponent* newAbilityComponent();
		void deleteAbilityComponent(int id);

		Actor* getActor(int id);
		Actor* newActor();
		void deleteActor(int id);

		AIComponent* getAIComponent(int id);
		AIComponent* newAIComponent();
		void deleteAIComponent(int id);

		BehaviorComponent* getBehaviorComponent(int id);
		BehaviorComponent* newBehaviorComponent();
		void deleteBehaviorComponent(int id);

		MovementComponent* getMovementComponent(int id);
		MovementComponent* newMovementComponent();
		void deleteMovementComponent(int id);

		ParticleSystemComponent* getParticleSystemComponent(int id);
		ParticleSystemComponent* newParticleSystemComponent();
		void deleteParticleSystemComponent(int id);

		PlayerInputComponent* getPlayerInputComponent(int id);
		PlayerInputComponent* newPlayerInputComponent();
		void deletePlayerInputComponent(int id);

		VitalsComponent* getVitalsComponent(int id);
		VitalsComponent* newVitalsComponent();
		void deleteVitalsComponent(int id);

		void update(float delta);
		void draw(const glm::mat4& VP);

		~ComponentManager();
	};

}