#include "ComponentManager.h"
#define C_SIZE 100

namespace Hive
{

	ComponentManager::ComponentManager()
	{
		abilityComponents = ObjectPool<AbilityComponent>(C_SIZE);
		actors = ObjectPool<Actor>(C_SIZE);
		aiComponents = ObjectPool<AIComponent>(C_SIZE);
		behaviorComponents = ObjectPool<BehaviorComponent>(C_SIZE);
		movementComponents = ObjectPool<MovementComponent>(C_SIZE);
		particleSystemComponents = ObjectPool<ParticleSystemComponent>(C_SIZE);
		playerInputComponents = ObjectPool<PlayerInputComponent>(1);
		vitalsComponents = ObjectPool<VitalsComponent>(C_SIZE);
	}

	AbilityComponent* ComponentManager::getAbilityComponent(int id)
	{
		return NULL;
	}
	AbilityComponent* ComponentManager::newAbilityComponent()
	{
		return NULL;
	}
	void ComponentManager::deleteAbilityComponent(int id)
	{
	}

	Actor* ComponentManager::getActor(int id)
	{
		return NULL;
	}
	Actor* ComponentManager::newActor()
	{
		return NULL;
	}
	void ComponentManager::deleteActor(int id)
	{
	}

	AIComponent* ComponentManager::getAIComponent(int id)
	{
		return NULL;
	}
	AIComponent* ComponentManager::newAIComponent()
	{
		return NULL;
	}
	void ComponentManager::deleteAIComponent(int id)
	{
	}

	BehaviorComponent* ComponentManager::getBehaviorComponent(int id)
	{
		return NULL;
	}
	BehaviorComponent* ComponentManager::newBehaviorComponent()
	{
		return NULL;
	}
	void ComponentManager::deleteBehaviorComponent(int id)
	{
	}

	MovementComponent* ComponentManager::getMovementComponent(int id)
	{
		return NULL;
	}
	MovementComponent* ComponentManager::newMovementComponent()
	{
		return NULL;
	}
	void ComponentManager::deleteMovementComponent(int id)
	{
	}

	ParticleSystemComponent* ComponentManager::getParticleSystemComponent(int id)
	{
		return NULL;
	}
	ParticleSystemComponent* ComponentManager::newParticleSystemComponent()
	{
		return NULL;
	}
	void ComponentManager::deleteParticleSystemComponent(int id)
	{
	}


	PlayerInputComponent* ComponentManager::getPlayerInputComponent(int id)
	{
		return NULL;
	}
	PlayerInputComponent* ComponentManager::newPlayerInputComponent()
	{
		return NULL;
	}
	void ComponentManager::deletePlayerInputComponent(int id)
	{
	}

	VitalsComponent* ComponentManager::getVitalsComponent(int id)
	{
		return NULL;
	}
	VitalsComponent* ComponentManager::newVitalsComponent()
	{
		return NULL;
	}
	void ComponentManager::deleteVitalsComponent(int id)
	{
	}

	void ComponentManager::update(float delta)
	{
		for (int i = 0; i < C_SIZE; ++i) if (abilityComponents.used(i)) abilityComponents.get(i)->update(delta);
		for (int i = 0; i < C_SIZE; ++i) if (actors.used(i)) actors.get(i)->update(delta);
		for (int i = 0; i < C_SIZE; ++i) if (aiComponents.used(i)) aiComponents.get(i)->update(delta);
		for (int i = 0; i < C_SIZE; ++i) if (behaviorComponents.used(i)) behaviorComponents.get(i)->update(delta);
		for (int i = 0; i < C_SIZE; ++i) if (movementComponents.used(i)) movementComponents.get(i)->update(delta);
		for (int i = 0; i < C_SIZE; ++i) if (particleSystemComponents.used(i)) particleSystemComponents.get(i)->update(delta);
		if (playerInputComponents.used(0)) playerInputComponents.get(0)->update(delta);
		for (int i = 0; i < C_SIZE; ++i) if (vitalsComponents.used(i)) vitalsComponents.get(i)->update(delta);
	}

	void ComponentManager::draw(const glm::mat4& VP)
	{
		for (int i = 0; i < C_SIZE; ++i) if (actors.used(i)) actors.get(i)->draw(VP);
		for (int i = 0; i < C_SIZE; ++i) if (particleSystemComponents.used(i)) particleSystemComponents.get(i)->draw(VP);
	}

	ComponentManager::~ComponentManager()
	{
	}

}