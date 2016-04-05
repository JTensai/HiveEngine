#pragma once
/*
 ***************************
 * Player Input Component
 * This component is the "AI controller" for the player's unit.
 * It is responsible for sending movement to the movement component and ability orders to the ability component.
 * It is likely that early in development this component's update routine will fix the game camera to it's entity's actor location.
 * At this stage of development there should never be more than one of these components at a time.
 ***************************
 */

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>

#include "Unit.h"
#include "ServiceLocator.h"

namespace Hive
{

	class PlayerInputComponent
	{
	private:
		UnitHandle player_unit_handle;
		DAbilityHandle left_click;
		DAbilityHandle right_click;

	public:
		PlayerInputComponent();
		void setPlayerHandle(UnitHandle handle);
		void update(float delta);
		void onleft();
		void onright();
		~PlayerInputComponent();
	};

}