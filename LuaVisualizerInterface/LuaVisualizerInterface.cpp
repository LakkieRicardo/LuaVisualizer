#include <iostream>
#include "LuaVisualizerState.h"

int main()
{
	LuaV::LuaVisualizerState vizer;
	vizer.LoadLuaScript("LogicScript.lua");
	vizer.BeginCallExecution();
	vizer.PrintInstructionsUntilReturn();
}