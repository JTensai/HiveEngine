#pragma once

#include <stdexcept>

#include "Data.h"

namespace Hive
{
	class OrderException : public std::exception
	{
	public:
		virtual const char* what() const { return "Unable to issue order."; }
	};

	class AbilityNotFoundException : public OrderException
	{
	public:
		virtual const char* what() const { return "Ability not found."; }
	};

	class AbilityOnCooldownException : public OrderException
	{
	public:
		virtual const char* what() const { return "Ability on cooldown."; }
	};

	class NotEnoughChargesException : public OrderException
	{
	public:
		virtual const char* what() const { return "Not enough charges."; }
	};

	class NotEnoughManaException : public OrderException
	{
	public:
		virtual const char* what() const { return "Not enough mana."; }
	};

	class NotEnoughHPException : public OrderException
	{
	public:
		virtual const char* what() const { return "Not enough HP."; }
	};

	class NoTargetException : public OrderException
	{
	public:
		virtual const char* what() const { return "No target."; }
	};

	class TargetOutOfRangeException : public OrderException
	{
	public:
		virtual const char* what() const { return "Target out of range."; }
	};

	class ValidatorFailedException : public OrderException
	{
	private:
		const char* validator_msg;
	public:
		ValidatorFailedException(const char* validator_msg) : validator_msg(validator_msg) {}
		virtual const char* what() const { return validator_msg; }
	};
}