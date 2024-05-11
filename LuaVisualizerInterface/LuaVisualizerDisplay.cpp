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
	for (const auto& arg : iArgs)
	{
		std::cout << ", " << arg.first << ": " << arg.second;
		StkId value = vmState.GetStackBase() + arg.second;
		std::string interpreted_value = LuaV::StackVarToString(value);
		std::cout << " (R[" << arg.second << "] = " << interpreted_value << ")";
	}
	std::cout << std::endl;
}