#include <iostream>
#include "LuaVisualizerState.h"

int main()
{
	LuaV::LuaVisualizerState vizer;
	vizer.LoadLuaScript("DemoScripts/LogicScript.lua");
	vizer.BeginCallExecution();
	vizer.PrintInstructionsUntilReturn();
}