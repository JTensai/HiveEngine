#pragma once

#include "AbilityComponent.h"
#include "Actor.h"
#include "AIComponent.h"
#include "BehaviorComponent.h"
#include "MovementComponent.h"
#include "ParticleSystemComponent.h"
#include "VitalsComponent.h"
#include "IComponentManager.h"
#include "ObjectPool.h"

class ComponentManager : public IComponentManager
{
private:
	ObjectPool<AbilityComponent> abilityComponents;
	ObjectPool<Actor> actors;
	ObjectPool<AIComponent> aiComponents;
	ObjectPool<BehaviorComponent> behaviorComponents;
	ObjectPool<MovementComponent> movementComponents;
	ObjectPool<ParticleSystemComponent> particleSystemComponents;
	ObjectPool<VitalsComponent> vitalsComponents;
public:
	ComponentManager();
	~ComponentManager();
};