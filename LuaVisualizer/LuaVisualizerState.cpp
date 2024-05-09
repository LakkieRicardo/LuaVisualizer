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

lua_State* LuaV::LuaVisualizerState::GetLuaState() const
{
	return m_L;
}

const StackValue* LuaV::LuaVisualizerState::GetValueInStack(int offset) const
{
	return m_execState.base + offset;
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
	
	// Clear the arguments map if it was populated from a previous update
	iArgs.clear();

	// Depending on the opcode, populate the table with different instructions
	// Also, go through each operation with the same argument types together
	switch (GET_OPCODE(i)) {
	case OP_RETURN0:
		break;
	case OP_LOADKX:
	case OP_LOADFALSE:
	case OP_LFALSESKIP:
	case OP_LOADTRUE:
	case OP_CLOSE:
	case OP_TBC:
	case OP_RETURN1:
	case OP_VARARGPREP:
		iArgs.emplace("A", GETARG_A(i));
		break;
	case OP_MOVE:
	case OP_LOADNIL:
	case OP_GETUPVAL:
	case OP_SETUPVAL:
	case OP_UNM:
	case OP_BNOT:
	case OP_NOT:
	case OP_LEN:
	case OP_CONCAT:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("B", GETARG_B(i));
		break;
	case OP_LOADI:
	case OP_LOADF:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("sBx", GETARG_sBx(i));
		break;
	case OP_LOADK:
	case OP_FORLOOP:
	case OP_FORPREP:
	case OP_TFORPREP:
	case OP_TFORLOOP:
	case OP_CLOSURE:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("Bx", GETARG_Bx(i));
		break;
	case OP_GETTABUP:
	case OP_GETTABLE:
	case OP_GETI:
	case OP_GETFIELD:
	case OP_SETTABUP:
	case OP_SETTABLE:
	case OP_SETI:
	case OP_SETFIELD:
	case OP_SELF:
	case OP_ADDK:
	case OP_SUBK:
	case OP_MULK:
	case OP_MODK:
	case OP_POWK:
	case OP_DIVK:
	case OP_IDIVK:
	case OP_BANDK:
	case OP_BORK:
	case OP_BXORK:
	case OP_ADD:
	case OP_SUB:
	case OP_MUL:
	case OP_MOD:
	case OP_POW:
	case OP_DIV:
	case OP_IDIV:
	case OP_BAND:
	case OP_BOR:
	case OP_BXOR:
	case OP_SHL:
	case OP_SHR:
	case OP_MMBIN:
	case OP_CALL:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("B", GETARG_B(i));
		iArgs.emplace("C", GETARG_C(i));
		break;
	case OP_NEWTABLE:
	case OP_MMBINK:
	case OP_TAILCALL:
	case OP_RETURN:
	case OP_SETLIST:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("B", GETARG_B(i));
		iArgs.emplace("C", GETARG_C(i));
		iArgs.emplace("k", GETARG_k(i));
		break;
	case OP_ADDI:
	case OP_SHRI:
	case OP_SHLI:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("B", GETARG_B(i));
		iArgs.emplace("sC", GETARG_sC(i));
		break;
	case OP_MMBINI:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("sB", GETARG_sB(i));
		iArgs.emplace("C", GETARG_C(i));
		iArgs.emplace("k", GETARG_k(i));
		break;
	case OP_JMP:
		iArgs.emplace("sJ", GETARG_sJ(i));
		break;
	case OP_EQ:
	case OP_LT:
	case OP_LE:
	case OP_EQK:
	case OP_TESTSET:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("B", GETARG_B(i));
		iArgs.emplace("k", GETARG_k(i));
		break;
	case OP_TEST:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("k", GETARG_k(i));
		break;
	case OP_EXTRAARG:
		iArgs.emplace("Ax", GETARG_Ax(i));
		break;
	case OP_EQI:
	case OP_LTI:
	case OP_LEI:
	case OP_GTI:
	case OP_GEI:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("sB", GETARG_sB(i));
		iArgs.emplace("k", GETARG_k(i));
		break;
	case OP_TFORCALL:
	case OP_VARARG:
		iArgs.emplace("A", GETARG_A(i));
		iArgs.emplace("C", GETARG_C(i));
		break;
	}

	// Check if we have stack values to read
	// TODO unfinished

	if (base < L->ci->top)
	{
		for (StkId stkIdx = base; stkIdx < L->ci->top; stkIdx++)
		{
			//StackValue value = *stkIdx;
		}
	}

	valid = true;
}

void LuaV::LuaVMState::ClearVMState()
{
	valid = false;
	opCode = static_cast<OpCode>(NUM_OPCODES); // TODO is this the right kind of cast?
	opCodeName = "UNKNOWN";
	iArgs.clear();
	stackValues.clear();
}

void LuaV::LuaVMState::MarkInvalid()
{
	valid = false;
}
