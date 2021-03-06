#include "Deserializer.hpp"

Deserializer::Deserializer(std::istream& in)
    : in_(in)
{
}

Error Deserializer::load(uint64_t& value)
{
	std::string uintFieldAsText;
	in_ >> uintFieldAsText;
	for (auto& elem : uintFieldAsText)
		if (!std::isdigit(elem))
			return Error::CorruptedArchive;
	try {
		value = std::stoull(uintFieldAsText);
	} catch (std::invalid_argument&) {
		return Error::CorruptedArchive;
	} catch (std::out_of_range&) {
		return Error::CorruptedArchive;
	}
	return Error::NoError;
}

Error Deserializer::load(bool& value)
{
	std::string boolFieldAsText;
	in_ >> boolFieldAsText;
	if (boolFieldAsText == "true")
		value = true;
	else if (boolFieldAsText == "false")
		value = false;
	else
		return Error::CorruptedArchive;
	return Error::NoError;
}
