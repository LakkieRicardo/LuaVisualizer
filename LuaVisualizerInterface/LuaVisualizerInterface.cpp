#include <iostream>
#include "LuaVisualizerDisplay.h"

void BeginStepThroughLoop(LuaV::LuaVisualizerState& vizer)
{
	for (;;)
	{
		// Wait for user input to execute an instruction
		std::string inputBuffer;
		std::getline(std::cin, inputBuffer);

		vizer.DoSingleInstruction();

		auto vmState = vizer.GetLuaVMState();

		std::cout << vmState.GetLastOperationName();
		PrintInstructionArgs(vmState, vizer);
		std::cout << std::endl;

		// TODO it seems like these stacks values are 1 instruction behind. Investigate what's going on with the VM here
		// This might be intended behavior?
		PrintStackValues(vmState);

		if (vmState.GetLastOperation() == OP_RETURN)
		{
			std::cout << "\nEnding at OP_RETURN...\n";
			break;
		}
	}
}

int main()
{
	std::cout << "Press \"Enter\" to advance the program by 1 instruction. The instruction, its arguments, and the state of the stack will be displayed.\n\n";

	LuaV::LuaVisualizerState vizer;
	vizer.LoadLuaScript("DemoScripts/LogicScript.lua");
	vizer.BeginCallExecution();
	
	BeginStepThroughLoop(vizer);
	
	vizer.FinishCallExecution();
}