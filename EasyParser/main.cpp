#include "TParser.h"

int main()
{
	std::string program = "42.12";

	TParser parser;
	auto ast = parser.Parse(program);
	ast->Print(std::cout);

	return 0;
}