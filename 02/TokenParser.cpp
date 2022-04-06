#include "TokenParser.hpp"

void TokenParser::parse(const std::string& str)
{
	size_t start = 0;
	size_t end = 0;
	size_t digitsInSubstring = 0;

	if (startCallback != nullptr)
		startCallback();

	for (size_t i = 1; i < str.size() + 1; ++i) {
		if (isSeparator(str.c_str()[i - 1]) && !isSeparator(str.c_str()[i]))
			start = i;

		if (std::isdigit(str.c_str()[i - 1]))
			++digitsInSubstring;

		if (isSeparator(str.c_str()[i]) && !isSeparator(str.c_str()[i - 1])) {
			end = i;

			std::string token = str.substr(start, end - start);

			if (end - start == digitsInSubstring) {
				if (digitTokenCallback != nullptr)
					digitTokenCallback(std::stoull(token));
			} else {
				if (stringTokenCallback != nullptr)
					stringTokenCallback(token);
			}

			digitsInSubstring = 0;
		}
	}

	if (endCallback != nullptr)
		endCallback();
}

bool TokenParser::isSeparator(const char& character)
{
	return character == ' ' || character == '\t' || character == '\n' || character == '\0';
}

void TokenParser::setStringTokenCallback(std::function<void(std::string&)> callback)
{
	stringTokenCallback = callback;
}

void TokenParser::setDigitTokenCallback(std::function<void(uint64_t)> callback)
{
	digitTokenCallback = callback;
}

void TokenParser::setStartCallback(std::function<void()> callback)
{
	startCallback = callback;
}

void TokenParser::setEndCallback(std::function<void()> callback)
{
	endCallback = callback;
}