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
				if (digitTokenCallback != nullptr) {
					uint64_t digitToken;
					try {
						digitToken = std::stoull(token);
						digitTokenCallback(digitToken);
					} catch (std::out_of_range& e) {
						stringTokenCallback(token);
					}
				}
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

void TokenParser::setStringTokenCallback(StringTokenCallback callback)
{
	stringTokenCallback = callback;
}

void TokenParser::setDigitTokenCallback(DigitTokenCallback callback)
{
	digitTokenCallback = callback;
}

void TokenParser::setStartCallback(UnconditionalCallback callback)
{
	startCallback = callback;
}

void TokenParser::setEndCallback(UnconditionalCallback callback)
{
	endCallback = callback;
}