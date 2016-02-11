#pragma once

#include "AbilityComponent.h"
#include "Actor.h"
#include "AIComponent.h"
#include "BehaviorComponent.h"
#include "MovementComponent.h"
#include "ParticleSystemComponent.h"
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

	virtual VitalsComponent* getVitalsComponent(int id) = 0;
	virtual VitalsComponent* newVitalsComponent() = 0;
	virtual void deleteVitalsComponent(int id) = 0;

	virtual void update(float delta) = 0;
	virtual void draw() = 0;
};