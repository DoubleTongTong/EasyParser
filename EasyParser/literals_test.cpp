#include "test_utils.h"

void LiteralsTest(TTestFunc testFunc)
{
	testFunc("42;", std::make_unique<TProgram>(
		std::make_unique<TStatementList>(
			[]() {
				std::vector<std::unique_ptr<TASTNode>> vec;
				vec.push_back(
					std::make_unique<TExpressionStatement>(
						std::make_unique<TNumericLiteral>(42)
					)
				);
				return vec;
			}()
		)
	));

	testFunc("\"hello\";", std::make_unique<TProgram>(
		std::make_unique<TStatementList>(
			[]() {
				std::vector<std::unique_ptr<TASTNode>> vec;
				vec.push_back(
					std::make_unique<TExpressionStatement>(
						std::make_unique<TStringLiteral>("hello")
					)
				);
				return vec;
			}()
		)
	));

	testFunc("'hello';", std::make_unique<TProgram>(
		std::make_unique<TStatementList>(
			[]() {
				std::vector<std::unique_ptr<TASTNode>> vec;
				vec.push_back(
					std::make_unique<TExpressionStatement>(
						std::make_unique<TStringLiteral>("hello")
					)
				);
				return vec;
			}()
		)
	));

	std::cout << "Literals Test Pass!\n";
}