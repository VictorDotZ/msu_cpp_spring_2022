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

	bool isSeparator(const char& character);

private:
	std::function<void(std::string&)> stringTokenCallback = nullptr;
	std::function<void(uint64_t)> digitTokenCallback = nullptr;
	std::function<void()> startCallback = nullptr;
	std::function<void()> endCallback = nullptr;
};