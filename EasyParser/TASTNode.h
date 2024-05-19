#pragma once

#include <iostream>
#include <variant>
#include <string>
#include <memory>

class TASTNode
{
public:
	virtual ~TASTNode();
	virtual void Print(std::ostream& out, int level = 0) const = 0;
};

class TProgram : public TASTNode
{
	std::unique_ptr<TASTNode> m_body;

public:
	TProgram(std::unique_ptr<TASTNode> body);
	void Print(std::ostream& out, int level) const override;
};

class TNumericLiteral : public TASTNode
{
	std::variant<int, double> m_value;

public:
	TNumericLiteral(const std::variant<int, double>& val);

	void Print(std::ostream& out, int level) const override;
};

class TStringLiteral : public TASTNode
{
	std::string m_value;

public:
	TStringLiteral(const std::string& val);

	void Print(std::ostream& out, int level) const override;
};