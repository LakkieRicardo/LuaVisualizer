#include "include/LuaValueConverter.h"

std::string LuaV::InstructionToString(const Instruction& i)
{
	std::stringstream ss;
	OpCode opcode = GET_OPCODE(i);
	if (opcode >= NUM_OPCODES || opcode < 0)
	{
		return "<unrecognized opcode>";
	}
	ss << opnames[opcode] << ", ";
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
		ss << "A: " << GETARG_A(i);
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
		ss << "A: " << GETARG_A(i) << ", B: " << GETARG_B(i);
		break;
	case OP_LOADI:
	case OP_LOADF:
		ss << "A: " << GETARG_A(i) << ", sBx: " << GETARG_sBx(i);
		break;
	case OP_LOADK:
	case OP_FORLOOP:
	case OP_FORPREP:
	case OP_TFORPREP:
	case OP_TFORLOOP:
	case OP_CLOSURE:
		ss << "A: " << GETARG_A(i) << ", Bx: " << GETARG_Bx(i);
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
		ss << "A: " << GETARG_A(i) << ", B: " << GETARG_B(i) << ", C: " << GETARG_C(i);
		break;
	case OP_NEWTABLE:
	case OP_MMBINK:
	case OP_TAILCALL:
	case OP_RETURN:
	case OP_SETLIST:
		ss << "A: " << GETARG_A(i) << ", B: " << GETARG_B(i) << ", C: " << GETARG_C(i) << ", k: " << GETARG_k(i);
		break;
	case OP_ADDI:
	case OP_SHRI:
	case OP_SHLI:
		ss << "A: " << GETARG_A(i) << ", B: " << GETARG_B(i) << ", sC: " << GETARG_sC(i);
		break;
	case OP_MMBINI:
		ss << "A: " << GETARG_A(i) << ", sB: " << GETARG_sB(i) << ", C:" << GETARG_C(i) << ", k: " << GETARG_k(i);
		break;
	case OP_JMP:
		ss << "sJ: " << GETARG_sJ(i);
		break;
	case OP_EQ:
	case OP_LT:
	case OP_LE:
	case OP_EQK:
	case OP_TESTSET:
		ss << "A: " << GETARG_A(i) << ", B: " << GETARG_B(i) << ", k: " << GETARG_k(i);
		break;
	case OP_TEST:
		ss << "A: " << GETARG_A(i) << ", k: " << GETARG_k(i);
		break;
	case OP_EXTRAARG:
		ss << "Ax: " << GETARG_Ax(i);
		break;
	case OP_EQI:
	case OP_LTI:
	case OP_LEI:
	case OP_GTI:
	case OP_GEI:
		ss << "A: " << GETARG_A(i) << ", sB: " << GETARG_sB(i) << ", k: " << GETARG_k(i);
		break;
	case OP_TFORCALL:
	case OP_VARARG:
		ss << "A: " << GETARG_A(i) << ", C:" << GETARG_C(i);
		break;
	default:
		ss << "<unrecognized opcode>";
	}

	return ss.str();
}

std::string LuaV::StackVarToString(const StkId idx)
{
	return StackVarToString(&idx->val);
}

std::string LuaV::StackVarToString(const TValue* value)
{
	lu_byte type = value->tt_;
	std::stringstream ss;
	char* strval; // Used if reading contents of string
	switch (type)
	{
	case LUA_TNIL:
		return "nil";
	case LUA_TBOOLEAN:
		return l_isfalse(value) ? "true" : "false";
		break;
	case LUA_TNUMBER:
		lua_Number numValue;
		tonumber(value, &numValue);
		ss << numValue;
		break;
		case LUA_TSTRING:
			strval = svalue(value);
			ss << strval;
			break;
		case LUA_TTABLE:
		case LUA_TFUNCTION:
		case LUA_TUSERDATA:
		case LUA_TTHREAD:
		case LUA_TLIGHTUSERDATA:
			// Print the address of this data
			// TODO: Print the number of elements in tables
			// TODO: Print function metadata
			// TODO: Print thread metadata
			ss << value;
			break;
	default:
		return "undefined";
	}

	return ss.str();
}

OpCode LuaV::GetInstructionOpCode(Instruction i)
{
	return GET_OPCODE(i);
}