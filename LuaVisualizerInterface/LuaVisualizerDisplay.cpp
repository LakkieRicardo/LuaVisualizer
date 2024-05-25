#include "include/LuaVisualizerDisplay.h"

/*
  This file contains all of the functions for writing the VM status as
  strings in a command line console. 
*/

void PrintStackValues(const LuaV::LuaVisualizerState& vizer)
{
	std::cout << "Register\tAddress\t\t\tValue";

	for (StkId stkIdx = vizer.GetStackBase(); stkIdx < vizer.GetStackTop(); stkIdx++)
	{
		size_t registerOffset = stkIdx - vizer.GetStackBase();
		std::cout << "\nR[" << registerOffset << "]\t\t" << stkIdx << "\t" << LuaV::StackVarToString(stkIdx);
	}

	std::cout << std::endl;
}

void PrintInstructionArgs(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer)
{
	const auto& iArgs = vmState.GetLastInstructionArgs();
	int argA, argB, argC, argsC;
	std::string argsCAsString;
	switch (vmState.GetLastOperation())
	{
	case OP_GETTABUP:
		argA = iArgs.at("A");
		argB = iArgs.at("B");
		argC = iArgs.at("C");
		std::cout << ",\tR[" << argA << "] = ";
		std::cout << "UpValue[" << argB << "][\"" << vizer.GetConstantAsString(argC) << "\"]";
		break;
	case OP_SETTABUP:
		argA = iArgs.at("A");
		argB = iArgs.at("B");
		argC = iArgs.at("C");
		std::cout << ",\tUpValue[" << argA << "][\"" << vizer.GetConstantAsString(argB) << "\"] = ";
		if (TESTARG_k(vmState.GetLastInstruction()))
		{
			std::cout << LuaV::StackVarToString(vizer.GetConstant(argC));
		}
		else
		{
			std::cout << LuaV::StackVarToString(vmState.GetStackBase() + argC);
		}
		break;

	/*
	  These instructions are simple operations, such as adding, multiplication, bitwise operations, etc.

	  They should be printed as:

	  OP_ADD, R[n] = n + n

	  The values for the operations need to be read from the VM state so that they're the values at the
	  time of execution. However, when actually printing the stack, they need to be directly read from
	  the Lua VM because the user needs to know what the current state of the data is.
	*/

	case OP_ADDI:
		argA = iArgs.at("A");
		argB = iArgs.at("B");
		argsC = iArgs.at("sC");
		argsCAsString = argsC;
		std::cout << SimpleOpAsString("+", argA, GetStackVarAsString(vmState, argB), argsCAsString);
		break;
	case OP_ADDK:
		break;
	case OP_SUBK:
		break;
	case OP_MULK:
		break;
	case OP_MODK:
		break;
	case OP_POWK:
		break;
	case OP_DIVK:
		break;
	case OP_IDIVK:
		break;
	case OP_BANDK:
		break;
	case OP_BORK:
		break;
	case OP_BXORK:
		break;
	case OP_SHRI:
		break;
	case OP_SHLI:
		break;
	case OP_ADD:
		argA = iArgs.at("A");
		argB = iArgs.at("B");
		argC = iArgs.at("C");
		std::cout << ",\t\t" << SimpleOpAsString("+", argA, LuaV::StackVarToString(vmState.GetStackBase() + argB), LuaV::StackVarToString(vmState.GetStackBase() + argC));
		break;
	case OP_SUB:
		break;
	case OP_MUL:
		break;
	case OP_MOD:
		break;
	case OP_POW:
		break;
	case OP_DIV:
		break;
	case OP_IDIV:
		break;
	case OP_BAND:
		break;
	case OP_BOR:
		break;
	case OP_BXOR:
		break;
	case OP_SHL:
		break;
	case OP_SHR:
		break;
	default:
		break;
	}
	// Print all instruction arguments literally
	std::cout << "\n\t\t";
	bool printComma = false;
	for (const auto& arg : iArgs)
	{
		// Only print the comma after the first argument
		if (!printComma)
		{
			printComma = true;
		}
		else
		{
			std::cout << ", ";
		}
		std::cout << arg.first << ": " << arg.second;
	}
	std::cout << std::endl;
}

std::string RegisterArgAsString(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer, int arg)
{
	std::stringstream ss;
	ss << "R[" << arg << "]: ";
	ss << LuaV::StackVarToString(vizer.GetStackBase() + arg);
	return ss.str();
}

std::string SimpleOpAsString(std::string operation, int a, std::string bVal, std::string cVal)
{
	std::stringstream ss;
	ss << "R[" << a << "] = " << bVal << ' ' << operation << ' ' << cVal;
	return ss.str();
}

std::string GetStackVarAsString(const LuaV::LuaVMState& vmState, int idx)
{
	return LuaV::StackVarToString(vmState.GetStackBase() + idx);
}
