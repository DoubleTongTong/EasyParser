#pragma once

#include <functional>
#include <memory>
#include "TASTNode.h"

using TTestFunc = std::function<void(const std::string&, std::unique_ptr<TASTNode>)>;

void LiteralsTest(TTestFunc testFunc);
void StatementListTest(TTestFunc testFunc);