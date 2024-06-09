#include "TParser.h"
#include "test_utils.h"
#include <assert.h>

std::vector<std::function<void(TTestFunc)>> tests =
{
	LiteralsTest,
	StatementListTest,
};

void Test(const std::string& input, std::unique_ptr<TASTNode> expected)
{
	TParser parser;
	auto ast = parser.Parse(input);

	if (ast->Equals(expected.get()) == false)
	{
		std::cerr << "Test failed.\nExpected:\n";
		expected->Print(std::cerr);
		std::cerr << "\nGot:\n";
		ast->Print(std::cerr);

		assert(0);
	}
}


int main()
{
#if 0
	std::string program = R"(
		/**
		 * This is a comment
		 */
		'Hello';
		// Number
		42;
	)";

	TParser parser;
	auto ast = parser.Parse(program);
	ast->Print(std::cout);
#endif

	// Auto Test
#if 1
	for (auto& test : tests)
	{
		test(Test);
	}
#endif
	return 0;
}