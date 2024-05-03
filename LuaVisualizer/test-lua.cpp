#include "LuaStateManager.h"
#include <iostream>
#include <sstream>

std::string LuaConstantsToString(lua_State* L, TValue* k, int sizek)
{
	std::stringstream ss;

	for (int i = 0; i < sizek; i++)
	{
		TValue* val = &(k[i]);
		
		if (ttisnil(val))
		{
			ss << "Nil\n";
			continue;
		}

		std::string strValue;

		switch (ttype(val))
		{
		case LUA_TBOOLEAN:
			ss << "Boolean\n";
			break;
		case LUA_TLIGHTUSERDATA:
			ss << "Light User Data\n";
			break;
		case LUA_TNUMBER:
			strValue = lakkie_tostring(L, val);
			if (ttisfloat(val)) {
				ss << "Float: " << strValue << "\n";
				break;
			}
			if (ttisinteger(val)) {
				ss << "Integer: " << strValue << "\n";
				break;
			}
			ss << "Misc number\n";
			break;
		case LUA_TSTRING:
			strValue = svalue(val);
			ss << "String: \"" << strValue << "\"\n";
			break;
		case LUA_TTABLE:
			ss << "Table\n";
			break;
		case LUA_TFUNCTION:
			ss << "Function\n";
			break;
		case LUA_TUSERDATA:
			ss << "User data\n";
			break;
		case LUA_TTHREAD:
			ss << "Thread\n";
			break;
		}
	}

	return ss.str();
}

int main()
{
	LuaV::LuaVisualizerState visualizer;
	visualizer.LoadLuaScript("LogicScript.lua");
	visualizer.BeginCallExecution();
	Instruction next = visualizer.GetNextInstruction();
	std::cout << "Next Instruction: " << visualizer.InstructionToDisplayString(next) << std::endl;
}