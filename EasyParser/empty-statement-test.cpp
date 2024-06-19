#include "test_utils.h"

void EmptyStatementTest(TTestFunc testFunc)
{
	testFunc(
		R"(

			;
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TEmptyStatement>()
					);
					return vec;
				}()
			)
		));

	std::cout << "Empty Statement Test Pass!\n";
}