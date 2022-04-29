#include "Serializer.hpp"

Serializer::Serializer(std::ostream& out)
    : out_(out)
{
}

void Serializer::print(const uint64_t& value)
{
	out_ << value;
}

void Serializer::print(const bool& value)
{
	out_ << (value ? "true" : "false");
}
