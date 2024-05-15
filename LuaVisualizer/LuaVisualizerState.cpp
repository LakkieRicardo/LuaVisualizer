#include "include/LuaVisualizerState.h"
#include "include/LuaValueConverter.h"

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

void LuaV::LuaVisualizerState::DoSingleInstruction()
{
	m_vmState.MarkInvalid();
	luaV_dosingleinstruct(m_L);
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

Instruction LuaV::LuaVisualizerState::GetNextInstruction() const
{
	if (!m_execState.is_prepared)
	{
		throw std::runtime_error("Lua function has not yet been called using LuaDebugState::BeginCallExecution");
	}

	return *(m_execState.pc + 1);
}

const StackValue* LuaV::LuaVisualizerState::GetValueInStack(int offset) const
{
	return m_execState.base + offset;
}

TValue* LuaV::LuaVisualizerState::GetUpValue(int index) const
{
	return m_execState.cl->upvals[index]->v;
}

TValue* LuaV::LuaVisualizerState::GetConstant(int index) const
{
	return m_execState.k + index;
}

std::string LuaV::LuaVisualizerState::GetConstantAsString(int index) const
{
	TString* strVal = tsvalue(GetConstant(index));
	return strVal->contents;
}