#pragma once
#include <functional>
#include <string>

class TokenParser {
public:
	void setStartCallback(std::function<void()> callback);
	void setEndCallback(std::function<void()> callback);
	void setDigitTokenCallback(std::function<void(uint64_t)> callback);
	void setStringTokenCallback(std::function<void(std::string&)> callback);

	void parse(const std::string& str);

private:
	std::function<void(std::string&)> stringTokenCallback;
	std::function<void(uint64_t)> digitTokenCallback;
	std::function<void()> startCallback;
	std::function<void()> endCallback;

	bool isSeparator(const char& character);
};