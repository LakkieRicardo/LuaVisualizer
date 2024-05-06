#pragma once

#include "Lua.h"
#include <string>
#include <sstream>
#include <vector>

namespace LuaV
{

	/*
	  A structure containing all of the information inside the Lua Virtual Machine.
	  This will be updated by a LuaVisualizerState and can be retrieved using its
	  GetLuaVMState() function.

	  These variables are retrieved from the lua_State and the VisualizerExecState,
	  and should reflect its properties while being updated.
	*/
	struct LuaVMState
	{
		/// <summary>
		/// Represents whether this data is valid. If the VM has been closed or somehow
		/// altered while the data is not updated, this should be marked as false.
		/// 
		/// This almost acts as a lock on the state object, and it should not be read
		/// from if flagged as false.
		/// </summary>
		bool valid;

		/// <summary>
		/// The opcode of the last executed instruction.
		/// </summary>
		OpCode opCode;

		/// <summary>
		/// The display name of the last executed name without the OP_ prefix. This should
		/// match the lastOpCode variable.
		/// </summary>
		std::string opCodeName;

		/// <summary>
		/// This variable represents k in the bytecode notation, and in the Lua VM is retrieved
		/// using the macro GETARG_k. It looks up a variable in the constant table according to
		/// this index.
		/// </summary>
		int constantIdx;

		/// <summary>
		/// Registers A-C, represented using a tagged value.
		/// </summary>
		TValue regA, regB, regC;

	public: // Update functions

		/// <summary>
		/// Reads all of the variables from the VisualizerExecState and lua_State, interpreting
		/// their values and writing them in a user-friendly way into LuaVMState.
		/// </summary>
		void UpdateVMState(lua_State* L);

		/// <summary>
		/// Marks the LuaVMState as inoperative, meaning that it is not currently executing a
		/// script, or that the lua_State is somehow inactive, errored, etc.
		/// </summary>
		void ClearVMState();
	};

	/*
	  Class which contains a lua_State and a VisualizerExecState. It owns both of
	  these objects and will clean them up when the object destructor is called.
	*/
	class LuaVisualizerState
	{

		lua_State* m_L; // State with the currently loaded script
		VisualizerExecState m_execState; // The state of the current call execution
		LuaVMState m_vmState; // Interpretation of variables in lua_State

	public:

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
		/// <param name="filename">Name of the .lua script file.</param>
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
		/// Retrieves the last updated state of the Lua VM. This is updated when BeginCallExecution(),
		/// DoSingleInstruction(), and FinishCallExecution() are called.
		/// </summary>
		/// <returns></returns>
		inline const LuaVMState& GetLuaVMState() const { return m_vmState; }

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

		/// <summary>
		/// Retrieves the current Lua state from the script loaded with LoadLuaScript(string).
		/// This should not be modified directly, only by the helper functions such as 
		/// GetNextInstruction() or DoSingleInstruction().
		/// 
		/// If the valid bool is set to false, then this data may be out of date or wrong. In
		/// this case, it should not be read from.
		/// </summary>
		/// <returns>Pointer to a lua_State.</returns>
		lua_State* GetLuaState() const;
	};

}