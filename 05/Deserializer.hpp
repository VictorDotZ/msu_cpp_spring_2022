#pragma once
#include "Error.hpp"
#include <istream>

class Deserializer {
public:
	explicit Deserializer(std::istream& in);

	template <class T>
	Error load(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}

private:
	template <class T>
	Error process(T&& value)
	{
		if (load(std::forward<T>(value)) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		if (!in_.eof())
			return Error::CorruptedArchive;
		return Error::NoError;
	}

	template <class T, class... Args>
	Error process(T&& value, Args&&... args)
	{
		if (load(std::forward<T>(value)) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		if (process(std::forward<Args>(args)...) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		return Error::NoError;
	}

	Error load(uint64_t& value);

	Error load(bool& value);

	std::istream& in_;
};