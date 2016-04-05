#pragma once

#include <stdexcept>

#include "Data.h"

namespace Hive
{
	enum class OrderResponse
	{
		OK = 0,
		ABILITY_NOT_FOUND,
		ABILITY_ON_COOLDOWN,
		NOT_ENOUGH_CHARGES,
		NOT_ENOUGH_MANA,
		NOT_ENOUGH_HP,
		NO_TARGET,
		TARGET_OUT_OF_RANGE,
		VALIDATOR_FAILED
	};
}