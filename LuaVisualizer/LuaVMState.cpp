#include "include/LuaVMState.h"

void LuaV::LuaVMState::UpdateVMInstruction(lua_State* L)
{
	instructionValid = false;

	Instruction i = *(L->exec_state->pc);
	instruction = i; // Update member field "instruction"
	OpCode opCode = GET_OPCODE(i);
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

	instructionValid = true;
}

void LuaV::LuaVMState::UpdateVMStack(lua_State* L)
{
	// If this value stays false, it means that there are no valid stack values
	// And the data is invalid
	stackValid = false;

	// Check if we have stack values to read
	if (L->exec_state->base < L->ci->top)
	{
		stackBase = nullptr;
		stackTop = nullptr;

		// stack top - bottom
		size_t stackSize = (L->ci->top - L->exec_state->base) * sizeof(StackValue);

		// Resize the stack
		delete[] localStack;
		localStack = new char[stackSize];

		std::memcpy(localStack, L->exec_state->base, stackSize);

		stackBase = reinterpret_cast<StkId>(localStack);
		stackTop = reinterpret_cast<StkId>(localStack) + stackSize;
		
		stackValid = true;
	}

}

void LuaV::LuaVMState::ClearVMState()
{
	MarkInvalid();
	instruction = static_cast<Instruction>(NUM_OPCODES);
	opCodeName = "UNKNOWN";
	iArgs.clear();
	delete[] localStack;
	localStack = nullptr;
	stackBase = nullptr;
	stackTop = nullptr;
}

void LuaV::LuaVMState::MarkInvalid()
{
	instructionValid = false;
	stackValid = false;
}