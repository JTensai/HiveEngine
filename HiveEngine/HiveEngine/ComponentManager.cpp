#include "ComponentManager.h"
#define C_SIZE 100

ComponentManager::ComponentManager()
{
	abilityComponents = ObjectPool<AbilityComponent>(C_SIZE);
	actors = ObjectPool<Actor>(C_SIZE);
	aiComponents = ObjectPool<AIComponent>(C_SIZE);
	behaviorComponents = ObjectPool<BehaviorComponent>(C_SIZE);
	movementComponents = ObjectPool<MovementComponent>(C_SIZE);
	particleSystemComponents = ObjectPool<ParticleSystemComponent>(C_SIZE);
	vitalsComponents = ObjectPool<VitalsComponent>(C_SIZE);
}

void ComponentManager::update(float delta)
{
	for (int i = 0; i < C_SIZE; ++i) abilityComponents.get(i)->update(delta);
	for (int i = 0; i < C_SIZE; ++i) actors.get(i)->update(delta);
	for (int i = 0; i < C_SIZE; ++i) aiComponents.get(i)->update(delta);
	for (int i = 0; i < C_SIZE; ++i) behaviorComponents.get(i)->update(delta);
	for (int i = 0; i < C_SIZE; ++i) movementComponents.get(i)->update(delta);
	for (int i = 0; i < C_SIZE; ++i) particleSystemComponents.get(i)->update(delta);
	for (int i = 0; i < C_SIZE; ++i) vitalsComponents.get(i)->update(delta);
}

void ComponentManager::draw()
{
	for (int i = 0; i < C_SIZE; ++i) actors.get(i)->draw();
	for (int i = 0; i < C_SIZE; ++i) particleSystemComponents.get(i)->draw();
}

ComponentManager::~ComponentManager()
{
}