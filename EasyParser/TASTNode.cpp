#include "TASTNode.h"

TASTNode::~TASTNode()
{
}

TNumericLiteral::TNumericLiteral(const std::variant<int, double>& val)
	: m_value(val)
{
}

void TNumericLiteral::Print(std::ostream& out) const
{
	std::visit([&out](auto&& arg) {
        out << "{\n";
        out << "  \"type\": \"NumericLiteral\",\n";
        out << "  \"value\": " << arg << "\n";
        out << "}";
		}, m_value);
}