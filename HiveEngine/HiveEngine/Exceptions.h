#pragma once

#include <stdexcept>

namespace Hive
{
	class Exception : public std::exception
	{
	public:
		std::string msg;
	};

	class AssetLoadException : public Exception
	{
	public:
		AssetLoadException(std::string err) { msg = err; }
	};

	class DataErrorException : public Exception
	{
	public:
		DataErrorException(std::string err) { msg = err; }
	};

	class EffectException : public Exception
	{
	public:
		EffectException(std::string err) { msg = err; }
	};

	class EffectTreeException : public Exception
	{
	public:
		EffectTreeException(std::string err) { msg = err; }
	};

	class UnimplementedException : public Exception
	{
	public:
		UnimplementedException() { msg = "Unimplemented code hit."; }
		UnimplementedException(std::string err) { msg = err; }
	};
}