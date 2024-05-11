#pragma once

#include "TASTNode.h"

class TParser
{
	std::string m_str;
public:
	TParser();

	std::unique_ptr<TASTNode> Parse(const std::string& input);

private:
	std::unique_ptr<TASTNode> Program();
	std::unique_ptr<TASTNode> NumericLiteral();
};