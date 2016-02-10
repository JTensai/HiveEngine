#pragma once

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
	void update(float delta);
	void draw();
	~ComponentManager();
};