#include "pch.h"
#include "TParser.h"

std::unique_ptr<TASTNode> TParser::Parse(const std::string& src)
{
	input = src;
	return Program();
}

std::unique_ptr<TASTNode> TParser::NumericLiteral()
{
	int val = std::stoi(input);
	return std::make_unique<TNumericLiteralNode>(val);
}

std::unique_ptr<TASTNode> TParser::Program()
{
	return NumericLiteral();
}