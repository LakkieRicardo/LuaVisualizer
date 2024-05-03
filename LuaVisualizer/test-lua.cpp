#include "LuaStateManager.h"
#include <iostream>
#include <sstream>

int main()
{
	// Begin call and get next instruction demo

	LuaV::LuaVisualizerState visualizer;
	visualizer.LoadLuaScript("LogicScript.lua");
	visualizer.BeginCallExecution();
	visualizer.PrintInstructionsUntilReturn();

	// Run demo script

	/*lua_State* L;
	L = luaL_newstate();
	luaL_dofile(L, "LogicScript.lua");

	lua_close(L);*/
}