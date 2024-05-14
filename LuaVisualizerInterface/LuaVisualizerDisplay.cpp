#include <iostream>
#include "LuaVisualizerDisplay.h"

/*
  This file contains all of the functions for writing the VM status as
  strings in a command line console. 
*/

void PrintStackValues(const LuaV::LuaVMState& vmState)
{
	std::cout << "\tStack:";

	for (StkId stkIdx = vmState.GetStackBase(); stkIdx < vmState.GetStackTop(); stkIdx++)
	{
		std::cout << "\n\t" << stkIdx << ": " << LuaV::StackVarToString(stkIdx);
	}

	std::cout << std::endl;
}

void PrintInstructionArgs(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer)
{
	const auto& iArgs = vmState.GetInstructionArgs();
	int argA, argB, argC;
	switch (vmState.GetLastInstruction())
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
		std::cout << ", A: " << argA << "(";
		PrintRegisterArg(vmState, vizer, argA);
		std::cout << "), B: " << argB << ", C: " << argC << "(";
		PrintGlobalKeyArg(vmState, vizer, argC);
		std::cout << ")\n";

		break;
	case OP_SETTABUP:
		/*
		  Similar to OP_GETTABUP, but the key is accessed through B and is set to the
		  constant value at C: UpValue[A][K[B]:string] := RK(C)

		  TODO: decide which format to use:

		  OP_SETTABUP, A: n, B: n (str), C: n (RK[n]: n)

		  or

		  OP_SETTABUP, UpValue[n][K[n]] = RK[n]
					   A: n, B: n, C: n

		  The second is likely more user friendly and tells you more about what the VM
		  is actually doing
		*/
	default:
		// Go through each instruction and print its value
		for (const auto& arg : iArgs)
		{
			std::cout << ", " << arg.first << ": " << arg.second;
		}
		break;
	}
	std::cout << std::endl;
}

void PrintRegisterArg(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer, int arg)
{
	std::string stack_value = LuaV::StackVarToString(vmState.GetStackBase() + arg);
	std::cout << "R[" << arg << "]: " << stack_value;
}

void PrintGlobalKeyArg(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer, int argC)
{
	// Find the key of this global
	TValue* keyValue = vizer.GetConstant(argC);
	// Interpret this value as a string
	TString* keyValueStr = tsvalue(keyValue);
	std::cout << '"' << keyValueStr->contents << '"';
}
