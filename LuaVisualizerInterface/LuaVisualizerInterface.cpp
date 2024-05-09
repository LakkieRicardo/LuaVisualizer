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

		std::cout << vmState.GetLastInstructionName();
		PrintInstructionArgs(vmState);
		std::cout << std::endl;
		PrintStackValues(vmState);
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