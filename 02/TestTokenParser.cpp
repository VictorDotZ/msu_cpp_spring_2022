#include "TokenParser.hpp"

#include <iostream>

void callback1(const std::string& str)
{
	std::cout << str << std::endl;
}

void callback2(uint64_t digit)
{
	std::cout << digit << std::endl;
}

int main()
{

	TokenParser* parser = new TokenParser();

	std::string str = "hello\t \t123  \nworld";

	parser->setStringTokenCallback(callback1);
	parser->setDigitTokenCallback(callback2);
	parser->setStartCallback([]() {});
	parser->setEndCallback([]() {});

	parser->parse(str);

	delete parser;
	return 0;
}