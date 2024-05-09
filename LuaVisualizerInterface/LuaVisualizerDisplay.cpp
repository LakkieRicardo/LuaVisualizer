#include <iostream>
#include "LuaVisualizerDisplay.h"

/*
  This file contains all of the functions for writing the VM status as
  strings in a command line console. 
*/

void PrintStackValues(const LuaV::LuaVMState& vmState)
{
	std::cout << "\tStack:";
	
}

void PrintInstructionArgs(const LuaV::LuaVMState& vmState)
{
	const auto& iArgs = vmState.GetInstructionArgs();
	for (const auto& arg : iArgs)
	{
		std::cout << ", " << arg.first << ": " << arg.second;
	}
	std::cout << std::endl;
}