#pragma once
/*
 ***************************
 * Component Manager
 * The component manager is responsible for tracking all the components that make up the entities in the game world.
 * These components should be stored contiguously in memory by type to enable cache-friendly iteration for update and draw calls, which are the responsiblity of the component manager.
 ***************************
 */

#include <glm\glm.hpp>

#include "AbilityComponent.h"
#include "Actor.h"
#include "AIComponent.h"
#include "BehaviorComponent.h"
#include "MovementComponent.h"
#include "ParticleSystemComponent.h"
#include "PlayerInputComponent.h"
#include "VitalsComponent.h"

class IComponentManager
{
public:
	virtual AbilityComponent* getAbilityComponent(int id) = 0;
	virtual AbilityComponent* newAbilityComponent() = 0;
	virtual void deleteAbilityComponent(int id) = 0;

	virtual Actor* getActor(int id) = 0;
	virtual Actor* newActor() = 0;
	virtual void deleteActor(int id) = 0;

	virtual AIComponent* getAIComponent(int id) = 0;
	virtual AIComponent* newAIComponent() = 0;
	virtual void deleteAIComponent(int id) = 0;

	virtual BehaviorComponent* getBehaviorComponent(int id) = 0;
	virtual BehaviorComponent* newBehaviorComponent() = 0;
	virtual void deleteBehaviorComponent(int id) = 0;

	virtual MovementComponent* getMovementComponent(int id) = 0;
	virtual MovementComponent* newMovementComponent() = 0;
	virtual void deleteMovementComponent(int id) = 0;

	virtual ParticleSystemComponent* getParticleSystemComponent(int id) = 0;
	virtual ParticleSystemComponent* newParticleSystemComponent() = 0;
	virtual void deleteParticleSystemComponent(int id) = 0;

	virtual PlayerInputComponent* getPlayerInputComponent(int id) = 0;
	virtual PlayerInputComponent* newPlayerInputComponent() = 0;
	virtual void deletePlayerInputComponent(int id) = 0;

	virtual VitalsComponent* getVitalsComponent(int id) = 0;
	virtual VitalsComponent* newVitalsComponent() = 0;
	virtual void deleteVitalsComponent(int id) = 0;

	virtual void update(float delta) = 0;
	virtual void draw(const glm::mat4& VP) = 0;
};