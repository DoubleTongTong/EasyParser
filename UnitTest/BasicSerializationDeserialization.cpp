#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CerealUnitTest
{
	class CustomClass
	{
	public:
		std::string name;
		int value;

		CustomClass() : name(""), value(0) {}
		CustomClass(const std::string& name, int value) : name(name), value(value) {}

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(name), CEREAL_NVP(value));
		}
	};

	TEST_CLASS(CustomSerialization)
	{
	public:
		TEST_METHOD(SerializeCustomClass)
		{
			CustomClass obj("Test", 42);
			std::ostringstream oss;

			{
				cereal::JSONOutputArchive archive(oss);
				archive(cereal::make_nvp("CustomClass", obj));
			}

			Logger::WriteMessage(("序列化:" + oss.str()).c_str());

			Assert::IsFalse(oss.str().empty(), L"序列化结果为空");
		}

		TEST_METHOD(DeserializeCustomClass)
		{
			std::string jsonStr = R"(
			{
				"CustomClass": {
					"name": "Test",
					"value": 42
				}
			})";

			std::istringstream iss(jsonStr);
			CustomClass obj;

			{
				cereal::JSONInputArchive archive(iss);
				archive(cereal::make_nvp("CustomClass", obj));
			}

			Assert::AreEqual(std::string("Test"), obj.name, L"反序列化的 name 不匹配");
			Assert::AreEqual(42, obj.value, L"反序列化的 value 不匹配");
		}
	};
}
