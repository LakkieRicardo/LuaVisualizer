#include "include/LuaVisualizerInterface.h"

void BeginStepThroughLoop(LuaV::LuaVisualizerState& vizer)
{
	for (;;)
	{
		// Wait for user input to execute an instruction
		std::string inputBuffer;
		std::getline(std::cin, inputBuffer);

		vizer.DoSingleInstruction();

		auto vmState = vizer.GetLuaVMState();

		std::cout << std::endl << vmState.GetLastOperationName();
		PrintInstructionArgs(vmState, vizer);
		std::cout << std::endl;

		PrintStackValues(vizer);

		if (vmState.GetLastOperation() == OP_RETURN)
		{
			std::cout << "\nEnding at OP_RETURN...\n";
			break;
		}
	}
}