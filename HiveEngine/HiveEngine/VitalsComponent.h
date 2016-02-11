#pragma once
/*
 ***************************
 * Vitals Component
 * This component is responsible for maintaining a unit's state and only units will have this component.
 * This includes things like a unit's hp, mana, attributes, and regeneration.
 * When a unit dies or is removed it is the responsibility of the vitals component to clean up after the expired entity, except for its actor, which it should notify.
 * The actor may have events to run, but should handle itself afterward.
 * Methods should be exposed to allow other systems to query and modify the unit's state.
 ***************************
 */

class VitalsComponent
{
public:
	VitalsComponent();
	void update(float delta);
	~VitalsComponent();
};

