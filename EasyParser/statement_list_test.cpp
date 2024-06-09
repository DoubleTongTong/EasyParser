#include "test_utils.h"

void StatementListTest(TTestFunc testFunc)
{
	testFunc(
		R"(
		/**
		 * This is a comment
		 */
		'hello';
		// Number
		42;
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TExpressionStatement>(
							std::make_unique<TStringLiteral>("hello")
						)
					);

					vec.push_back(
						std::make_unique<TExpressionStatement>(
							std::make_unique<TNumericLiteral>(42)
						)
					);
					return vec;
				}()
			)
		));

	std::cout << "Statement List Test Pass!\n";
}