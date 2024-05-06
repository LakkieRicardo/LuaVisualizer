#pragma once

#include "Lua.h"
#include <string>
#include <sstream>
#include <vector>

namespace LuaV
{
	class LuaVisualizerState
	{

		lua_State* m_L; // State with the currently loaded script
		VisualizerExecState m_execState;

	public:

		LuaVisualizerState();

		~LuaVisualizerState();

		void LoadLuaScript(const std::string& filename);

		/// <summary>
		/// Prepares the interpreter loop.
		/// </summary>
		void BeginCallExecution();

		/// <summary>
		/// Finishes the current call by decrementing nCcalls. This can only be run when the
		/// call is finished.
		/// </summary>
		void FinishCallExecution();

		/// <summary>
		/// Peeks ahead to the next instruction in the program without modifying the current
		/// state.
		/// </summary>
		Instruction GetNextInstruction() const;

		/// <summary>
		/// Advances the program ahead by 1 instruction.
		/// </summary>
		void DoSingleInstruction();

		/// <summary>
		/// Prints all of the instruction names until OP_RETURN.
		/// </summary>
		void PrintInstructionsUntilReturn() const;

		/// <summary>
		/// Retrieves the current Lua state from the script loaded with LoadLuaScript(string).
		/// This should not be modified directly, only by the helper functions such as 
		/// GetNextInstruction() or DoSingleInstruction().
		/// </summary>
		/// <returns>Pointer to a lua_State.</returns>
		lua_State* GetLuaState() const;
	};

}