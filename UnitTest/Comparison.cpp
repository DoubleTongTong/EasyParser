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

			Assert::IsTrue(json1 == json2, L"�����ֶ�˳��ͬ��������ͬ�� JSON Ӧ�ñ���Ϊ���");
		}
	};
}
