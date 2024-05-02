#pragma once

extern "C" {
#include <lua.h>
#include <lvm.h>
#include <lualib.h>
#include <lauxlib.h>
#include <lstate.h>
#include <lopcodes.h>
#include <lopnames.h>
}

#include <string>
#include <sstream>

namespace LuaV
{

	class LuaDebugState
	{

		lua_State* m_L; // Local state of the virtual machine.
		VisualizerExecState m_execState;

	public:

		LuaDebugState();

		~LuaDebugState();

		std::string InstructionToDisplayString(const Instruction& i);

		/// <summary>
		/// Converts the value of a stack variable to a user-friendly string.
		/// </summary>
		/// <param name="idx">Location on the stack</param>
		/// <param name="type">What data is at that location</param>
		std::string LuaStackValueToString(int idx, int type);

		/// <summary>
		/// Initializes a new Lua state using the luaL_newstate function, and defines its VM callbacks.
		/// </summary>
		void CreateDebugLuaState();

		/// <summary>
		/// Prepares the interpreter loop.
		/// </summary>
		void BeginCallExecution();

		/// <summary>
		/// Peeks ahead to the next instruction in the program without modifying the current state.
		/// </summary>
		Instruction GetNextInstruction();

		/// <summary>
		/// Advances the program ahead by 1 instruction.
		/// </summary>
		void DoSingleInstruction();
	};

}