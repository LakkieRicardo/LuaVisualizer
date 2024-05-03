#include "LuaStateManager.h"
#include <iostream>
#include <sstream>

int main()
{
	LuaV::LuaVisualizerState visualizer;
	visualizer.LoadLuaScript("LogicScript.lua");
	visualizer.BeginCallExecution();
	Instruction next = visualizer.GetNextInstruction();
	std::cout << "Next Instruction: " << visualizer.InstructionToDisplayString(next) << std::endl;
}