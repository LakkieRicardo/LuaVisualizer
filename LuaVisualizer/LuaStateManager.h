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

	class LuaVisualizerState
	{

		lua_State* m_L; // Local state of the virtual machine.
		VisualizerExecState m_execState;

	public:

		LuaVisualizerState();

		~LuaVisualizerState();

		// TODO move these to another location

		std::string InstructionToDisplayString(const Instruction& i);

		/// <summary>
		/// Converts the value of a stack variable to a user-friendly string.
		/// </summary>
		/// <param name="idx">Location on the stack</param>
		/// <param name="type">What data is at that location</param>
		std::string LuaStackValueToString(int idx, int type);

		void LoadLuaScript(const std::string& filename);

		/// <summary>
		/// Prepares the interpreter loop.
		/// </summary>
		void BeginCallExecution();

		/// <summary>
		/// Finishes the current call by decrementing nCcalls. This can only be run when the call is finished.
		/// </summary>
		void FinishCallExecution();

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