#include "include/pch.h"
#include "CppUnitTest.h"
#include "LuaValueConverter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LuaVisualizerTest
{
	TEST_CLASS(LuaValueConverterTest)
	{
	public:
		
		TEST_METHOD(TestValidInstructionCode)
		{
			constexpr char* EXPECTED_OPNAME = "MOVE";

			// POS_OP is the position of a Lua opcode
			// Because OP_MOVE is 0 this instruction will still be a 0, but it's good practice
			Instruction moveInstruct = OP_MOVE >> POS_OP;
			std::string instructName = LuaV::InstructionToString(moveInstruct);
			std::string opname = instructName.substr(0, strnlen_s(EXPECTED_OPNAME, 20));
			Assert::IsTrue(opname == EXPECTED_OPNAME, L"MOVE instruction name did not match expected value");
		}
	};
}
