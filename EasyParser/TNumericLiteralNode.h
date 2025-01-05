#pragma once

#include "TASTNode.h"

struct TNumericLiteralNode : public TASTNode
{
	int value;

	TNumericLiteralNode(int val) : value(val) {};

	void Serialize(cereal::JSONOutputArchive& archive) const override
	{
		archive(CEREAL_NVP(type), CEREAL_NVP(value));
	}

private:
	std::string type = "NumericLiteral";
};