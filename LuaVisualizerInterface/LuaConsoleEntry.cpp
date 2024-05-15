#include "include/LuaVisualizerInterface.h"

int main()
{
	std::cout << "Press \"Enter\" to advance the program by 1 instruction. The instruction, its arguments, and the state of the stack will be displayed.\n\n";

	LuaV::LuaVisualizerState vizer;
	vizer.LoadLuaScript("DemoScripts/LogicScript.lua");
	vizer.BeginCallExecution();

	BeginStepThroughLoop(vizer);

	vizer.FinishCallExecution();
}