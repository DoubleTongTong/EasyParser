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
        out << ind << "}\n";
		}, m_value);
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