#include "include/LuaVisualizerState.h"
#include "include/LuaValueConverter.h"

#include <iostream>

using namespace LuaV;

LuaVisualizerState::LuaVisualizerState()
{
	m_execState = VisualizerExecState();
	m_execState.is_prepared = false;
	m_L = luaL_newstate();
	m_L->using_visualizer = true;
	m_L->exec_state = &m_execState;
	m_vmState = LuaVMState();
	m_vmState.ClearVMState();
}

LuaV::LuaVisualizerState::~LuaVisualizerState()
{
	lua_close(m_L);

}

void LuaV::LuaVisualizerState::LoadLuaScript(const std::string& filename)
{
	luaL_loadfile(m_L, filename.c_str());
}

void LuaV::LuaVisualizerState::BeginCallExecution()
{
	// Begin a call in the global context
	// Lua do some checks and run luaD_precall, setting us up to run the interpreter loop
	luaD_callnoyield(m_L, m_L->top - 1, -1);
}

void LuaV::LuaVisualizerState::FinishCallExecution()
{
	// Need to manually make a call to finish the execution because the initial luaD_callnoyield
	// shouldn't finish it on its own.
	luaV_finishexec(m_L);
}

Instruction LuaV::LuaVisualizerState::GetNextInstruction() const
{
	if (!m_execState.is_prepared)
	{
		throw std::runtime_error("Lua function has not yet been called using LuaDebugState::BeginCallExecution");
	}

	return *(m_execState.pc + 1);
}

void LuaV::LuaVisualizerState::DoSingleInstruction()
{
	m_vmState.ClearVMState();
	// TODO unfinished code

	m_vmState.UpdateVMState(m_L);
}

void LuaV::LuaVisualizerState::PrintInstructionsUntilReturn() const
{
	if (!m_execState.is_prepared)
	{
		throw std::runtime_error("Lua function has not yet been called using LuaDebugState::BeginCallExecution");
	}
	
	const Instruction* currentPC = m_execState.pc;
	Instruction currentInstruction = *currentPC;
	while (GET_OPCODE(currentInstruction) != OP_RETURN)
	{
		std::cout << InstructionToString(currentInstruction) << std::endl;
		currentInstruction = *(++currentPC);
	}
}

lua_State* LuaV::LuaVisualizerState::GetLuaState() const
{
	return m_L;
}

void LuaV::LuaVMState::UpdateVMState(lua_State* L)
{
	valid = false;

	Instruction i = *(L->exec_state->pc);
	opCode = GET_OPCODE(i);
	if (opCode < 0 || opCode >= NUM_OPCODES)
	{
		throw std::runtime_error("Found an invalid opcode");
	}

	opCodeName = opnames[opCode];
	StkId base = L->exec_state->base;
	regA = (base + GETARG_A(i))->val;
	// TODO Will need to handle every instruction separately
	// TODO copy function from LuaValueConverter?
	/*regB = (base + GETARG_B(i))->val;
	regC = (base + GETARG_C(i))->val;*/


	valid = true;
}

void LuaV::LuaVMState::ClearVMState()
{
	valid = false;
	opCode = static_cast<OpCode>(NUM_OPCODES); // TODO is this the right kind of cast?
	opCodeName = "UNKNOWN";
}