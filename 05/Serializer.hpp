#pragma once
#include "Error.hpp"
#include <ostream>

class Serializer {
public:
	explicit Serializer(std::ostream& out);

	template <class T>
	Error save(T& object)
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
		print(std::forward<T>(value));
		return Error::NoError;
	}

	template <class T, class... Args>
	Error process(T&& value, Args&&... args)
	{
		print(std::forward<T>(value));
		out_ << Separator;
		return process(std::forward<Args>(args)...);
	}

	void print(const uint64_t& value);
	void print(const bool& value);

	std::ostream& out_;
	static constexpr char Separator = ' ';
};