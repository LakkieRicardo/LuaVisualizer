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