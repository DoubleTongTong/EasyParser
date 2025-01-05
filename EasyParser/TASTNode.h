#pragma once

#include "pch.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"

struct TASTNode
{
	virtual ~TASTNode() = default;
	virtual void Serialize(cereal::JSONOutputArchive& archive) const = 0;
};