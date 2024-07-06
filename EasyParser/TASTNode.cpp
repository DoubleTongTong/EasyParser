#include "TASTNode.h"

std::string TIndent(int level)
{
    return std::string(level * 2, ' ');
}

TASTNode::~TASTNode()
{
}

TProgram::TProgram(std::unique_ptr<TASTNode> body)
    : m_body(std::move(body))
{
}

void TProgram::Print(std::ostream& out, int level) const
{
    std::string ind = TIndent(level);
    std::string indInner = TIndent(level + 1);

    out << ind << "{\n";
    out << indInner << "\"type\": \"Program\",\n";
    out << indInner << "\"body\":\n";
    m_body->Print(out, level + 1);
    out << ind << "}\n";
}

bool TProgram::Equals(const TASTNode* other) const
{
    const TProgram* program = dynamic_cast<const TProgram*>(other);

    if (program == NULL)
        return false;

    if (m_body.get() == NULL || program->m_body.get() == NULL)
        return m_body.get() == program->m_body.get();

    return m_body->Equals(program->m_body.get());
}

TStatementList::TStatementList(std::vector<std::unique_ptr<TASTNode>> statements)
    : m_statements(std::move(statements))
{
}

void TStatementList::AddStatement(std::unique_ptr<TASTNode> stmt)
{
    m_statements.push_back(std::move(stmt));
}

void TStatementList::Print(std::ostream& out, int level) const
{
    std::string ind = TIndent(level);
    std::string indInner = TIndent(level + 1);

    out << ind << "[\n";

    for (int i = 0; i < m_statements.size(); i++)
    {
        m_statements[i]->Print(out, level + 1);
        if (i != m_statements.size() - 1)
            out << ",\n";
    }

    out << "\n";

    out << ind << "]\n";
}

bool TStatementList::Equals(const TASTNode* other) const
{
    const TStatementList* statementList = dynamic_cast<const TStatementList*>(other);

    if (statementList == NULL)
        return false;

    if (m_statements.size() != statementList->m_statements.size())
        return false;

    for (int i = 0; i < m_statements.size(); i++)
    {
        if (m_statements[i]->Equals(statementList->m_statements[i].get()) == false)
            return false;
    }

    return true;
}

TBlockStatement::TBlockStatement(std::unique_ptr<TASTNode> body)
    : m_body(std::move(body))
{
}

void TBlockStatement::Print(std::ostream& out, int level) const
{
    std::string ind = TIndent(level);
    std::string indInner = TIndent(level + 1);

    out << ind << "{\n";
    out << indInner << "\"type\": \"BlockStatement\",\n";
    out << indInner << "\"body\":\n";
    m_body->Print(out, level + 1);
    out << ind << "}";
}

bool TBlockStatement::Equals(const TASTNode* other) const
{
    const TBlockStatement* blockStatement = dynamic_cast<const TBlockStatement*>(other);

    if (blockStatement == NULL)
        return false;

    if (m_body.get() == NULL || blockStatement->m_body.get() == NULL)
        return m_body.get() == blockStatement->m_body.get();

    return m_body->Equals(blockStatement->m_body.get());
}

void TEmptyStatement::Print(std::ostream& out, int level) const
{
    std::string ind = TIndent(level);
    std::string indInner = TIndent(level + 1);

    out << ind << "{\n";
    out << indInner << "\"type\": \"EmptyStatement\"\n";
    out << ind << "}";
}

bool TEmptyStatement::Equals(const TASTNode* other) const
{
    return dynamic_cast<const TEmptyStatement*>(other) != NULL;
}

TExpressionStatement::TExpressionStatement(std::unique_ptr<TASTNode> expr)
    : m_expression(std::move(expr))
{
}

void TExpressionStatement::Print(std::ostream& out, int level) const
{
    std::string ind = TIndent(level);
    std::string indInner = TIndent(level + 1);

    out << ind << "{\n";
    out << indInner << "\"type\": \"ExpressionStatement\",\n";
    out << indInner << "\"expression\":\n";
    m_expression->Print(out, level + 1); out << "\n";
    out << ind << "}";
}

bool TExpressionStatement::Equals(const TASTNode* other) const
{
    const TExpressionStatement* expressionStatement = dynamic_cast<const TExpressionStatement*>(other);

    if (expressionStatement == NULL)
        return false;

    if (m_expression.get() == NULL || expressionStatement->m_expression.get() == NULL)
        return m_expression.get() == expressionStatement->m_expression.get();

    return m_expression->Equals(expressionStatement->m_expression.get());
}

TBinaryExpression::TBinaryExpression(const std::string& op,
    std::unique_ptr<TASTNode> left,
    std::unique_ptr<TASTNode> right)
    : m_op(op), m_left(std::move(left)), m_right(std::move(right))
{
}

void TBinaryExpression::Print(std::ostream& out, int level) const
{
    std::string ind = TIndent(level);
    std::string indInner = TIndent(level + 1);

    out << ind << "{\n";
    out << indInner << "\"type\": \"BinaryExpression\",\n";
    out << indInner << "\"operator\": \"" << m_op << "\",\n";
    out << indInner << "\"left\":\n";
    m_left->Print(out, level + 1); out << ",\n";
    out << indInner << "\"right\":\n";
    m_right->Print(out, level + 1); out << "\n";
    out << ind << "}";
}

bool TBinaryExpression::Equals(const TASTNode* other) const
{
    const TBinaryExpression* binaryExpression = dynamic_cast<const TBinaryExpression*>(other);

    if (binaryExpression == NULL)
        return false;

    if (m_op != binaryExpression->m_op)
        return false;

    auto areEqual = [](const std::unique_ptr<TASTNode>& lhs, const std::unique_ptr<TASTNode>& rhs)
    {
            if (lhs.get() == NULL && rhs.get() == NULL) return true;
            if (lhs.get() == NULL || rhs.get() == NULL) return false;
            return lhs->Equals(rhs.get());
    };

    return areEqual(m_left, binaryExpression->m_left) &&
           areEqual(m_right, binaryExpression->m_right);
}


TNumericLiteral::TNumericLiteral(const std::variant<int, double>& val)
	: m_value(val)
{
}

void TNumericLiteral::Print(std::ostream& out, int level) const
{
    std::string ind = TIndent(level);
    std::string indInner = TIndent(level + 1);

	std::visit([&out, &ind, &indInner](auto&& arg) {
        out << ind << "{\n";
        out << indInner << "\"type\": \"NumericLiteral\",\n";
        out << indInner << "\"value\": " << arg << "\n";
        out << ind << "}";
		}, m_value);
}

bool TNumericLiteral::Equals(const TASTNode* other) const
{
    const TNumericLiteral* numericLiteral = dynamic_cast<const TNumericLiteral*>(other);

    return numericLiteral && m_value == numericLiteral->m_value;
}

TStringLiteral::TStringLiteral(const std::string& val)
    : m_value(val)
{
}

void TStringLiteral::Print(std::ostream& out, int level) const
{
    std::string ind = TIndent(level);
    std::string indInner = TIndent(level + 1);

    out << ind << "{\n";
    out << indInner << "\"type\": \"StringLiteral\",\n";
    out << indInner << "\"value\": " << "\"" << m_value << "\"" << "\n";
    out << ind << "}\n";
}

bool TStringLiteral::Equals(const TASTNode* other) const
{
    const TStringLiteral* stringLiteral = dynamic_cast<const TStringLiteral*>(other);

    return stringLiteral && m_value == stringLiteral->m_value;
}