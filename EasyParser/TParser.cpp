#include "TParser.h"

#include <sstream>
#include <assert.h>

TParser::TParser()
{
}

std::unique_ptr<TASTNode> TParser::Parse(const std::string& str)
{
	m_str = str;

	return Program();
}

std::unique_ptr<TASTNode> TParser::Program()
{
	return NumericLiteral();
}

std::unique_ptr<TASTNode> TParser::NumericLiteral()
{
	int intVal;
	std::stringstream ssInt(m_str);
	ssInt >> intVal;
	if (!ssInt.fail() && ssInt.eof())
		return std::make_unique<TNumericLiteral>(intVal);

	double dblVal;
	std::stringstream ssDbl(m_str);
	ssDbl >> dblVal;
	if (!ssDbl.fail() && ssDbl.eof())
		return std::make_unique<TNumericLiteral>(dblVal);

	assert("Invalid numeric");
}