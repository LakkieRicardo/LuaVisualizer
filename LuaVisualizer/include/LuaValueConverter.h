#pragma once

#include "Lua.h"
#include <string>

namespace LuaV
{
	/// <summary>
	/// Converts a Lua bytecode instruction to a display string.
	/// </summary>
	/// <returns>The name of the operation and its parameters(ex: A, B, C, Bx, etc.). If the opcode
	/// is not recognized, "<unrecognized opcode>" will be returned.</returns>
	std::string InstructionToString(const Instruction& i);

	/// <summary>
	/// Converts the value of a stack variable to a user-friendly string.
	/// </summary>
	/// <param name="idx">Location on the stack</param>
	/// <param name="type">What data is at that location</param>
	std::string StackVarToString(lua_State* L, int idx, int type);
}