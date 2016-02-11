#pragma once
/*
 ***************************
 * AI Component
 * The AI Component is responsible for generating all movement and ability use of non-player controlled entities.
 * Ideally AI behavior will be specified through data, but for the immediate future perhaps one or two hardcoded programs can be selected from in the data.
 * The AI Component sends all of its orders to the entity's ability component, which will forward movement commands to the movement component.
 ***************************
 */

class AIComponent
{
public:
	AIComponent();
	void update(float delta);
	~AIComponent();
};

