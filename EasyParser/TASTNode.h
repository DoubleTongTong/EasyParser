#pragma once

#include <iostream>
#include <variant>
#include <string>
#include <memory>
#include <vector>

class TASTNode
{
public:
	virtual ~TASTNode();
	virtual void Print(std::ostream& out, int level = 0) const = 0;
	virtual bool Equals(const TASTNode* other) const = 0;
};

class TProgram : public TASTNode
{
	std::unique_ptr<TASTNode> m_body;

public:
	TProgram(std::unique_ptr<TASTNode> body);
	void Print(std::ostream& out, int level) const override;
	bool Equals(const TASTNode* other) const override;
};

class TStatementList : public TASTNode
{
	std::vector<std::unique_ptr<TASTNode>> m_statements;

public:
	TStatementList() = default;
	explicit TStatementList(std::vector<std::unique_ptr<TASTNode>> statements);
	void AddStatement(std::unique_ptr<TASTNode> stmt);

	void Print(std::ostream& out, int level) const override;
	bool Equals(const TASTNode* other) const override;
};

class TBlockStatement : public TASTNode
{
	std::unique_ptr<TASTNode> m_body;

public:
	explicit TBlockStatement(std::unique_ptr<TASTNode> body);

	void Print(std::ostream& out, int level) const override;
	bool Equals(const TASTNode* other) const override;
};

class TEmptyStatement : public TASTNode
{
public:
	TEmptyStatement() = default;

	void Print(std::ostream& out, int level) const override;
	bool Equals(const TASTNode* other) const override;
};

class TExpressionStatement : public TASTNode
{
	std::unique_ptr<TASTNode> m_expression;

public:
	TExpressionStatement(std::unique_ptr<TASTNode> expr);

	void Print(std::ostream& out, int level) const override;
	bool Equals(const TASTNode* other) const override;
};

class TBinaryExpression : public TASTNode
{
	std::string m_op;
	std::unique_ptr<TASTNode> m_left;
	std::unique_ptr<TASTNode> m_right;

public:
	TBinaryExpression(const std::string& op,
		              std::unique_ptr<TASTNode> left,
					  std::unique_ptr<TASTNode> right);

	void Print(std::ostream& out, int level) const override;
	bool Equals(const TASTNode* other) const override;
};

class TNumericLiteral : public TASTNode
{
	std::variant<int, double> m_value;

public:
	TNumericLiteral(const std::variant<int, double>& val);

	void Print(std::ostream& out, int level) const override;
	bool Equals(const TASTNode* other) const override;
};

class TStringLiteral : public TASTNode
{
	std::string m_value;

public:
	TStringLiteral(const std::string& val);

	void Print(std::ostream& out, int level) const override;
	bool Equals(const TASTNode* other) const override;
};