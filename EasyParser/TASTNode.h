#pragma once

#include <iostream>
#include <variant>
#include <string>

class TASTNode
{
public:
	virtual ~TASTNode();
	virtual void Print(std::ostream& out) const = 0;
};

class TNumericLiteral : public TASTNode
{
	std::variant<int, double> m_value;

public:
	TNumericLiteral(const std::variant<int, double>& val);

	void Print(std::ostream& out) const override;
};