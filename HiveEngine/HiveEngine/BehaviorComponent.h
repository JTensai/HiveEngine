#pragma once
/*
 ***************************
 * Behavior Component
 * The behavior component is responsible for maintaining and updating any behaviors on its owning entity.
 * Methods should be exposed to allow other systems to query the entity's behaviors and their states.
 ***************************
 */

class BehaviorComponent
{
public:
	BehaviorComponent();
	void update(float delta);
	~BehaviorComponent();
};

