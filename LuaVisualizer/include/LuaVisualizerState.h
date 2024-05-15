#pragma once

#include "Lua.h"
#include "LuaVMState.h"

#include <iostream>

namespace LuaV
{

	/*
	  Class which contains a lua_State and a VisualizerExecState. It owns both of
	  these objects and will clean them up when the object destructor is called.

	  Lua's state can be manipulated and interrogated using this class. One example
	  is getting the state, advancing one instruction, then getting the state again.
	*/
	class LuaVisualizerState
	{

		lua_State* m_L; // State with the currently loaded script
		VisualizerExecState m_execState; // The state of the current call execution
		LuaVMState m_vmState; // Interpretation of variables in lua_State

	public: // Functions to update state

		/// <summary>
		/// Creates lua_State and VisualizerExecState objects. It also tells the
		/// lua_State object that the Lua visualizer will be used.
		/// </summary>
		LuaVisualizerState();

		/// <summary>
		/// Closes the lua_State object and cleans up any owned objects.
		/// </summary>
		~LuaVisualizerState();

		/// <summary>
		/// Loads a script into the Lua Virtual Machine according to the filename.
		/// </summary>
		/// <param name="filename">Path to the .lua script file.</param>
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
		/// Advances the program ahead by 1 instruction.
		/// 
		/// This function requires the BeginCallExecution method to be called beforehand so
		/// that the Lua VM is in the proper state. It also requires that there is an available
		/// instruction in this context.
		/// 
		/// After this instruction is called, the current VM state struct will be updated. It
		/// can be retrieved using the GetLuaVMState() function.
		/// </summary>
		void DoSingleInstruction();

		/// <summary>
		/// Prints all of the instruction names until OP_RETURN.
		/// </summary>
		void PrintInstructionsUntilReturn() const;

	public: // Functions to read state

		/// <summary>
		/// Peeks ahead to the next instruction in the program without modifying the current
		/// state.
		/// </summary>
		Instruction GetNextInstruction() const;

		/// <summary>
		/// Retrieves the last updated state of the Lua VM. This is updated when BeginCallExecution(),
		/// DoSingleInstruction(), and FinishCallExecution() are called.
		/// </summary>
		/// <returns></returns>
		inline LuaVMState GetLuaVMState() const { return m_vmState; }

		/// <summary>
		/// Retrieves the current Lua state from the script loaded with LoadLuaScript(string).
		/// This should not be modified directly, only by the helper functions such as 
		/// GetNextInstruction() or DoSingleInstruction().
		/// 
		/// If the valid bool is set to false, then this data may be out of date or wrong. In
		/// this case, it should not be read from.
		/// </summary>
		/// <returns>Pointer to a lua_State.</returns>
		inline lua_State* GetLuaState() const { return m_L; };

		/// <summary>
		/// Retrieves a value from the stack at a given location. The position is relative to
		/// the frame, which is the function which is being called.
		/// </summary>
		/// <param name="offset">The position of this stack value relative to the stack
		/// base in this frame. Can be negative.</param>
		const StackValue* GetValueInStack(int offset) const;

		/// <summary>
		/// Looks up an upvalue using the current context's LClosure variable.
		/// </summary>
		/// <param name="index">The index of the upvalue to access</param>
		TValue* GetUpValue(int index) const;

		/// <summary>
		/// Looks up a constant value within this current execution frame.
		/// </summary>
		TValue* GetConstant(int index) const;

		std::string GetConstantAsString(int index) const;
	};

}