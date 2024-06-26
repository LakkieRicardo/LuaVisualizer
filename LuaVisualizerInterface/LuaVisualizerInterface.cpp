#include "include/LuaVisualizerInterface.h"

void BeginStepThroughLoop(LuaV::LuaVisualizerState& vizer)
{
	for (;;)
	{
		// Wait for user input to execute an instruction
		std::string inputBuffer;
		//std::getline(std::cin, inputBuffer);

		vizer.DoSingleInstruction();

		const LuaV::LuaVMState& vmState = vizer.GetLuaVMState();

		std::cout << std::endl << vmState.GetLastOperationName();
		PrintInstructionArgs(vmState, vizer);
		if (vmState.GetLastOperation() == OP_GETTABUP || vmState.GetLastOperation() == OP_SETTABUP)
		{
			// Print globals
			PrintGlobals(vizer);
		}
		std::cout << std::endl;

		PrintStackValues(vizer);

		if (vmState.GetLastOperation() == OP_RETURN)
		{
			std::cout << "\nEnding at OP_RETURN...\n";
			break;
		}
	}
}