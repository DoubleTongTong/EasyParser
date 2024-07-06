#include "TTokenizer.h"
#include <assert.h>

const std::vector<std::pair<std::regex, TToken::Type>> TTokenizer::m_spec =
{
	{ std::regex("^\\s+"), TToken::WHITESPACE },
	{ std::regex("^//.*"), TToken::COMMENT },
	{ std::regex("^/\\*[\\s\\S]*?\\*/"), TToken::COMMENT },

	{ std::regex("^;"), TToken::SEMICOLON },
	{ std::regex("^\\{"), TToken::LBRACE },
	{ std::regex("^\\}"), TToken::RBRACE },
	{ std::regex("^\\("), TToken::LPAREN },
	{ std::regex("^\\)"), TToken::RPAREN },

	{ std::regex("^[+\\-]"), TToken::ADD_OP },
	{ std::regex("^[*/]"), TToken::MUL_OP },


	{ std::regex("^\\d+"), TToken::NUMBER },
	{ std::regex("^\"[^\"]*\""), TToken::STRING },
	{ std::regex("^'[^\"]*'"), TToken::STRING },
};

TToken::TToken(Type type, std::string value)
	: type(type),
	  value(value)
{
}


TTokenizer::TTokenizer()
	: m_str(""),
	  m_cursor(0)
{
}

void TTokenizer::Init(const std::string& str)
{
	m_str = str;
	m_cursor = 0;
}

bool TTokenizer::HasMoreTokens() const
{
	return m_cursor < m_str.length();
}

TToken TTokenizer::GetNextToken()
{
	while (HasMoreTokens())
	{
		bool matched = false;

		for (const auto& [regexp, tokenType] : m_spec)
		{
			std::sregex_iterator it(m_str.begin() + m_cursor, m_str.end(), regexp);
			std::sregex_iterator end;

			if (it != end)
			{
				std::smatch match = *it;

				if (match.position() == 0)
				{
					m_cursor += match.length();
					matched = true;

					if (tokenType == TToken::WHITESPACE || tokenType == TToken::COMMENT)
						break;

					return TToken(tokenType, match.str());
				}
			}
		}

		if (matched == false)
		{
			fprintf(stderr, "Unexpected token: %c\n", m_str[m_cursor]);
			assert(0 && "Unexpected token");
		}
	}

	return TToken(TToken::END, "");
}