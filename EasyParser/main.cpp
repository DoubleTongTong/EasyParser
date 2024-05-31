#include "TParser.h"

int main()
{
	std::string program = R"(
		/**
		 * This is a comment
		 */
		'Hello'
	)";

	TParser parser;
	auto ast = parser.Parse(program);
	ast->Print(std::cout);

	return 0;
}