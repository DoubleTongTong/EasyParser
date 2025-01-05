#pragma once

#include "TASTNode.h"
#include "TNumericLiteralNode.h"

#ifdef TPARSER_EXPORTS
#define TPARSER_API __declspec(dllexport)
#else
#define TPARSER_API __declspec(dllimport)
#endif

class TPARSER_API TParser
{
	std::string input;

public:
	std::unique_ptr<TASTNode> Parse(const std::string& src);

private:
	std::unique_ptr<TASTNode> NumericLiteral();

	std::unique_ptr<TASTNode> Program();
};