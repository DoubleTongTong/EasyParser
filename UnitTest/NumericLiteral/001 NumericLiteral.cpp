#include "pch.h"
#include "CppUnitTest.h"

#include "TParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserUnitTest
{
	TEST_CLASS(NumericLiteral)
	{
	public:
		TEST_METHOD(Integer)
		{
			TParser parser;
			std::string input = "123";

			auto ast = parser.Parse(input);

			std::ostringstream oss;
			{
				cereal::JSONOutputArchive archive(oss);
				ast->Serialize(archive);
			}

			std::string res = oss.str();
			Logger::WriteMessage(res.c_str());

			json result_json = json::parse(res);
			json expected_json = R"({"type":"NumericLiteral","value":123})"_json;

			Assert::IsTrue(result_json == expected_json, L"解析结果的 JSON 对象应该与预期的 JSON 对象相同");
		}
	};
}
