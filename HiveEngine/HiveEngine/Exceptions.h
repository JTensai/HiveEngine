#pragma once

#include <stdexcept>

namespace Hive
{
	class Exception : public std::exception
	{
	public:
		std::string msg;
		virtual const char* what() const { return "Unknown exception."; }
	};

	class AssetLoadException : public Exception
	{
	public:
		AssetLoadException(std::string err) { msg = err; }
		virtual const char* what() const { return "Asset load exception."; }
	};

	class DataErrorException : public Exception
	{
	public:
		DataErrorException(std::string err) { msg = err; }
		virtual const char* what() const { return "Data error exception."; }
	};

	class EffectException : public Exception
	{
	public:
		EffectException(std::string err) { msg = err; }
		virtual const char* what() const { return "Effect exception."; }
	};

	class EffectTreeException : public Exception
	{
	public:
		EffectTreeException(std::string err) { msg = err; }
		virtual const char* what() const { return "Effect tree exception."; }
	};

	class UnimplementedException : public Exception
	{
	public:
		UnimplementedException() { msg = "Unimplemented code hit."; }
		UnimplementedException(std::string err) { msg = err; }
		virtual const char* what() const { return "Unimplemented exception."; }
	};

	class ValidatorException : public Exception
	{
	public:
		ValidatorException(std::string err) { msg = err; }
		virtual const char* what() const { return "Validator exception."; }
	};
}