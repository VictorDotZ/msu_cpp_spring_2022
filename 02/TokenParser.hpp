#pragma once
#include <functional>
#include <string>

using UnconditionalCallback = std::function<void()>;
using DigitTokenCallback = std::function<void(uint64_t)>;
using StringTokenCallback = std::function<void(std::string&)>;

class TokenParser {
public:
	void setStartCallback(UnconditionalCallback callback);
	void setEndCallback(UnconditionalCallback callback);
	void setDigitTokenCallback(DigitTokenCallback callback);
	void setStringTokenCallback(StringTokenCallback callback);

	void parse(const std::string& str);

	bool isSeparator(const char& character);

private:
	StringTokenCallback stringTokenCallback = nullptr;
	DigitTokenCallback digitTokenCallback = nullptr;
	UnconditionalCallback startCallback = nullptr;
	UnconditionalCallback endCallback = nullptr;
};