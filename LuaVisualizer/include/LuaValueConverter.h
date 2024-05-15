#pragma once

#include "Lua.h"

#include <string>
#include <sstream>

namespace LuaV
{
	/// <summary>
	/// Converts a Lua bytecode instruction to a display string.
	/// </summary>
	/// <returns>The name of the operation and its parameters(ex: A, B, C, Bx, etc.). If the opcode
	/// is not recognized, "<unrecognized opcode>" will be returned.</returns>
	std::string InstructionToString(const Instruction& i);

	/// <summary>
	/// Reads the type tag in the StackValue and converts the value to a string. This will produce
	/// a string in teh same format as StackVarToString(lua_State*, int, int).
	/// </summary>
	/// <param name="idx">Pointer to a StackValue</param>
	/// <returns>Displayable StackValue</returns>
	std::string StackVarToString(const StkId idx);

	/// See StackVarToString(const StkId)
	std::string StackVarToString(const TValue* idx);

	/// <summary>
	/// Uses Lua macros to retrieve the opcode out of an instruction.
	/// </summary>
	OpCode GetInstructionOpCode(Instruction i);
}