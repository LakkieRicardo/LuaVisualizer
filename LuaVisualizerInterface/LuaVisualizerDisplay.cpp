#include "include/LuaVisualizerDisplay.h"

/*
  This file contains all of the functions for writing the VM status as
  strings in a command line console. 
*/

void PrintStackValues(const LuaV::LuaVisualizerState& vizer)
{
	std::cout << "\tStack:";

	for (StkId stkIdx = vizer.GetStackBase(); stkIdx < vizer.GetStackTop(); stkIdx++)
	{
		std::cout << "\n\t" << stkIdx << ": " << LuaV::StackVarToString(stkIdx);
	}

	std::cout << std::endl;
}

void PrintInstructionArgs(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer)
{
	const auto& iArgs = vmState.GetInstructionArgs();
	int argA, argB, argC;
	switch (vmState.GetLastOperation())
	{
	case OP_GETTABUP:
		/*
		  This instruction follows this logic: R[A] := UpValue[B][K[C]:string] and takes the
		  arguments A, B, C. It should be printed as:

		  OP_GETTABUP, A: n (R[n]: n), B: n, C: n (str)
		*/
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
			std::cout << LuaV::StackVarToString(vizer.GetStackBase() + argC);
		}
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