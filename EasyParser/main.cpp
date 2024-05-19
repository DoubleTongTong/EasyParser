#include "TParser.h"

int main()
{
	std::string program = "\"Hello world!\"";

	TParser parser;
	auto ast = parser.Parse(program);
	ast->Print(std::cout);

	return 0;
}