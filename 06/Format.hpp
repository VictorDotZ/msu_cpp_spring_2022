#pragma once

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

class ValueError : public std::exception {
public:
	const char* what() const noexcept override
	{
		return "there is no '<<' stdout for value in {}";
	}
};

class TemplateStringWrongFormat : std::exception {
public:
	explicit TemplateStringWrongFormat(std::string what)
	    : m_what(std::move(what))
	{
	}

	const char* what() const noexcept override
	{
		return m_what.c_str();
	}

private:
	std::string m_what;
};

class ArgumentMissing : std::exception {
public:
	explicit ArgumentMissing(std::string what)
	    : m_what(std::move(what))
	{
	}

	const char* what() const noexcept override
	{
		return m_what.c_str();
	}

private:
	std::string m_what;
};

std::string formatHelper(const std::string& s, const size_t& len)
{
	(void)len;
	return s;
}

template <typename T, typename... Args>
std::string formatHelper(const std::string& s, const size_t& len, const T& arg, const Args&... args)
{
	std::basic_ostringstream<char> result;
	const size_t n = (len - 1) - sizeof...(Args);
	size_t inserted = 0;

	for (size_t i = 0; i < s.length(); ++i) {
		if (s[i] == '}')
			throw TemplateStringWrongFormat("} before {");

		if (s[i] == '{') {
			i++;
			std::stringstream currentTemplate;
			while (s[i] != '}' && i < s.length()) {
				if (std::isdigit(s[i])) {
					currentTemplate << s[i++];

				} else {
					throw TemplateStringWrongFormat("Incorrect positional number");
				}
			}

			if (s[i] != '}')
				throw TemplateStringWrongFormat("No paired }");

			uint64_t argumentPosition;
			try {
				argumentPosition = std::stoull(currentTemplate.str());
			} catch (std::invalid_argument& e) {
				throw TemplateStringWrongFormat("Incorrect positional number");
			} catch (std::out_of_range& e) {
				throw TemplateStringWrongFormat("Incorrect positional number");
			}

			if (argumentPosition == n) {
				try {
					result << arg;
				} catch (std::exception& e) {
					throw ValueError();
				}
				inserted++;
			} else {
				if (argumentPosition > len - 1) {
					throw ArgumentMissing("Args too little");
				}
				result << "{" << argumentPosition << "}";
			}
		} else {
			if (s[i] != '\0')
				result << s[i];
		}
	}

	if (inserted == 0)
		throw ArgumentMissing("Args too many");

	std::string res = result.str();
	return formatHelper(res, len, args...);
}

template <typename... Args>
std::string format(const std::string& s, const Args&... args)
{
	return formatHelper(s, sizeof...(Args), args...);
}
