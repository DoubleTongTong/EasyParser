#include "test_utils.h"

void BlockTest(TTestFunc testFunc)
{
	testFunc(
		R"(
		{
			"Hello";

			1234;
		}
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TBlockStatement>(
							std::make_unique<TStatementList>(
								[]() {
									std::vector<std::unique_ptr<TASTNode>> vec;
									vec.push_back(
										std::make_unique<TExpressionStatement>(
											std::make_unique<TStringLiteral>("Hello")
										)
									);

									vec.push_back(
										std::make_unique<TExpressionStatement>(
											std::make_unique<TNumericLiteral>(1234)
										)
									);
									return vec;
								}()
							)
						)
					);

					return vec;
				}()
			)
		));

	testFunc(
		R"(
		{
			"Hello";
			{
				1234;
			}
		}
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;
					vec.push_back(
						std::make_unique<TBlockStatement>(
							std::make_unique<TStatementList>(
								[]() {
									std::vector<std::unique_ptr<TASTNode>> vec;
									vec.push_back(
										std::make_unique<TExpressionStatement>(
											std::make_unique<TStringLiteral>("Hello")
										)
									);

									vec.push_back(
										std::make_unique<TBlockStatement>(
											std::make_unique<TStatementList>(
												[]() {
													std::vector<std::unique_ptr<TASTNode>> vec;

													vec.push_back(
														std::make_unique<TExpressionStatement>(
															std::make_unique<TNumericLiteral>(1234)
														)
													);
													return vec;
												}()
											)
										)
									);
									return vec;
								}()
							)
						)
					);

					return vec;
				}()
			)
		));

	testFunc(
		R"(
		{
		}
		)",
		std::make_unique<TProgram>(
			std::make_unique<TStatementList>(
				[]() {
					std::vector<std::unique_ptr<TASTNode>> vec;

					vec.push_back(
						std::make_unique<TBlockStatement>(
							std::make_unique<TStatementList>(
								[]() {
									std::vector<std::unique_ptr<TASTNode>> vec;
									return vec;
								}()
							)
						)
					);

					return vec;
				}()
			)
		));
	std::cout << "Block Test Pass!\n";
}