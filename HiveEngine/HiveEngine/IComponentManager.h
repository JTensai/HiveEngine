#pragma once

#include "AbilityComponent.h"
#include "Actor.h"
#include "AIComponent.h"
#include "BehaviorComponent.h"
#include "MovementComponent.h"
#include "ParticleSystemComponent.h"
#include "VitalsComponent.h"

class IComponentManager {
public:
	virtual AbilityComponent* getAbilityComponent(int id) { return 0; }
	virtual AbilityComponent* newAbilityComponent() { return 0; }
	virtual void deleteAbilityComponent(int id) {}

	virtual Actor* getActor(int id) { return 0; }
	virtual Actor* newActor() { return 0; }
	virtual void deleteActor(int id) {}

	virtual AIComponent* getAIComponent(int id) { return 0; }
	virtual AIComponent* newAIComponent() { return 0; }
	virtual void deleteAIComponent(int id) {}

	virtual BehaviorComponent* getBehaviorComponent(int id) { return 0; }
	virtual BehaviorComponent* newBehaviorComponent() { return 0; }
	virtual void deleteBehaviorComponent(int id) {}

	virtual MovementComponent* getMovementComponent(int id) { return 0; }
	virtual MovementComponent* newMovementComponent() { return 0; }
	virtual void deleteMovementComponent(int id) {}

	virtual ParticleSystemComponent* getParticleSystemComponent(int id) { return 0; }
	virtual ParticleSystemComponent* newParticleSystemComponent() { return 0; }
	virtual void deleteParticleSystemComponent(int id) {}

	virtual VitalsComponent* getVitalsComponent(int id) { return 0; }
	virtual VitalsComponent* newVitalsComponent() { return 0; }
	virtual void deleteVitalsComponent(int id) {}

	virtual void update(float delta) {}
	virtual void draw() {}
};