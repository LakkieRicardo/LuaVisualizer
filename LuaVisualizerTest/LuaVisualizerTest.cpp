#include "include/pch.h"
#include "CppUnitTest.h"
#include "LuaValueConverter.h"
#include "LuaVisualizerState.h"
#include "include/ToStringSpecialization.h"

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
			std::string opname = instructName.substr(0, strnlen_s(EXPECTED_OPNAME, 50));
			Assert::IsTrue(opname == EXPECTED_OPNAME, L"MOVE instruction name did not match expected value");
		}

		TEST_METHOD(TestInvalidInstructionCode)
		{
			constexpr char* EXPECTED_OPNAME = "<unrecognized opcode>";
			
			// Should not be recognized as a valid instruction
			Instruction moveInstruct = NUM_OPCODES >> POS_OP;
			std::string instructName = LuaV::InstructionToString(moveInstruct);
			std::string opname = instructName.substr(0, strnlen_s(EXPECTED_OPNAME, 50));
			Assert::IsTrue(opname == EXPECTED_OPNAME, L"Unrecognized instruction name did not match expected value");
		}
	};

	/// <summary>
	/// Tests all the functionality when LuaVisualizerState::BeginCallExecution() is called.
	/// </summary>
	TEST_CLASS(LuaVisualizerStateTest)
	{

		LuaV::LuaVisualizerState m_State;

		TEST_METHOD_INITIALIZE(InitializeStateTest)
		{
			m_State.LoadLuaScript("TestData/LuaScripts/LogicScript.lua");
			m_State.BeginCallExecution();
		}

		TEST_METHOD_CLEANUP(CleanUpStateTest)
		{
			m_State.FinishCallExecution();
		}

		TEST_METHOD(TestScriptLoaded)
		{
			OpCode opcode = GET_OPCODE(m_State.GetNextInstruction());
			Assert::AreEqual(OP_VARARGPREP, opcode, L"GetNextInstruction() reported an unexpected first instruction");
		}

	};
}
