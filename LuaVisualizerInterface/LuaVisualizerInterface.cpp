#include <iostream>
#include "LuaVisualizerState.h"
#include "LuaValueConverter.h"

int main()
{
	LuaV::LuaVisualizerState vizer;
	vizer.LoadLuaScript("DemoScripts/LogicScript.lua");
	vizer.BeginCallExecution();
	
	LuaV::LuaVMState state = vizer.GetLuaVMState();
	do
	{
		vizer.DoSingleInstruction();
		state = vizer.GetLuaVMState();
		// Print instruction and its arguments while executing
		std::cout << "Executed instruction: " << state.GetLastInstructionName();
		const auto& args = state.GetInstructionArgs();
		for (auto it = args.begin(); it != args.end(); it++)
		{
			std::cout << ", " << it->first << " = " << it->second;
		}
		std::cout << std::endl;
	} while (state.IsValid() && LuaV::GetInstructionOpCode(state.GetLastInstruction()) != OP_RETURN);
	
	vizer.FinishCallExecution();
}