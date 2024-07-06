#include "test_utils.h"

void MathTest(TTestFunc testFunc)
{
	testFunc(
		R"(
		1 + 2;
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TExpressionStatement>(
							std::make_unique<TBinaryExpression>("+",
								std::make_unique<TNumericLiteral>(1),
								std::make_unique<TNumericLiteral>(2))
						)
					);

					return vec;
				}()
			)
		));

	testFunc(
		R"(
		1 + 2 - 3;
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TExpressionStatement>(
							std::make_unique<TBinaryExpression>("-",
								std::make_unique<TBinaryExpression>("+",
									std::make_unique<TNumericLiteral>(1),
									std::make_unique<TNumericLiteral>(2)),
								std::make_unique<TNumericLiteral>(3))
						)
					);

					return vec;
				}()
			)
		));

	testFunc(
		R"(
		1 * 2;
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TExpressionStatement>(
							std::make_unique<TBinaryExpression>("*",
								std::make_unique<TNumericLiteral>(1),
								std::make_unique<TNumericLiteral>(2))
						)
					);

					return vec;
				}()
					)
		));

	testFunc(
		R"(
		1 + 2 * 3;
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TExpressionStatement>(
							std::make_unique<TBinaryExpression>("+",
								std::make_unique<TNumericLiteral>(1),
								std::make_unique<TBinaryExpression>("*",
									std::make_unique<TNumericLiteral>(2),
									std::make_unique<TNumericLiteral>(3))
							)
						)
					);

					return vec;
				}()
					)
		));

	testFunc(
		R"(
		(1 + 2) * 3;
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TExpressionStatement>(
							std::make_unique<TBinaryExpression>("*",
								std::make_unique<TBinaryExpression>("+",
									std::make_unique<TNumericLiteral>(1),
									std::make_unique<TNumericLiteral>(2)),
								std::make_unique<TNumericLiteral>(3)
							)
						)
					);

					return vec;
				}()
					)
		));

	std::cout << "Math Test Pass!\n";

}