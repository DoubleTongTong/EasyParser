#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace JsonUnitTest
{
	TEST_CLASS(Comparison)
	{
	public:
		TEST_METHOD(CompareWithDifferentOrder)
		{
			json json1 = json::parse(R"({"name": "Alice", "age": 30})");
			json json2 = json::parse(R"({"age": 30, "name": "Alice"})");

			Assert::IsTrue(json1 == json2, L"两个字段顺序不同但内容相同的 JSON 应该被视为相等");
		}
	};
}
