#pragma once

#include "Lua.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace LuaV
{

	/*
	  A structure containing all of the information inside the Lua Virtual Machine.
	  This will be updated by a LuaVisualizerState and can be retrieved using its
	  GetLuaVMState() function.

	  These variables are retrieved from the lua_State and the VisualizerExecState,
	  and should reflect its properties while being updated.

	  This class should only be instantiated by LuaVisualizerState.
	*/
	class LuaVMState
	{
		/// <summary>
		/// Represents whether this data is valid. If the VM has been closed or somehow
		/// altered while the data is not updated, this should be marked as false.
		/// 
		/// Every time an update to the visualizer state is called, this flag should be
		/// updated to false until UpdateVMState(lua_State*) is called.
		/// </summary>
		bool valid;

		/// <summary>
		/// The last executed instruction.
		/// </summary>
		Instruction instruction;

		/// <summary>
		/// The display name of the last executed name without the OP_ prefix. This should
		/// match the lastOpCode variable.
		/// </summary>
		std::string opCodeName;

		/// <summary>
		/// Short for "instruction arguments" and represents all of the arguments used for this
		/// instruction. The key is a string representing any of the following values: A, B, C,
		/// k, sB, sC, Ax, Bx, sJ, sBx. To get more information about what these arguments mean,
		/// see both the Lua bytecode reference:
		/// https://the-ravi-programming-language.readthedocs.io/en/latest/lua_bytecode_reference.html
		/// and the "Instructions Table.txt" included in this repository/solution.
		/// </summary>
		std::map<std::string, int> iArgs;

		/// <summary>
		/// All of the stack values copied from the Lua VM. This data is owned by this state and
		/// will not be modified by future instructions. The beginning of the vector is the value
		/// pointed to by base, and the last element is what is pointed to by top. This vector
		/// does not include variable arguments or the closure object.
		/// </summary>
		std::vector<StackValue> stackValues;

		/// <summary>
		/// Pointers to the actual Lua stack base and top in this current frame.
		/// </summary>
		StkId basePtr, topPtr;

	public: // Functions to update fields

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

		/// <summary>
		/// Marks the valid flag as false, telling all readers to ignore the data.
		/// </summary>
		void MarkInvalid();

	public:

		/// <returns>If the data in this state is currently valid</returns>
		inline bool IsValid() const { return valid; }

		inline Instruction GetLastInstruction() const { return instruction; }

		/// <returns>The last instruction that was executed</returns>
		inline OpCode GetLastOperation() const { return GET_OPCODE(instruction); }

		/// <returns>User-friendly name of the last executed instruction without OP_ prefix.</returns>
		inline const std::string& GetLastOperationName() const { return opCodeName; }

		/// <summary>
		/// The instruction args map is a way of accessing all the arguments an instruction contains
		/// without having to know its opcode. These arguments are embedded into the Instruction
		/// object that the Lua VM runs on and, using bitwise manipulation, can be extracted from it.
		/// </summary>
		/// <returns>Map of all the arguments this instruction contains.</returns>
		inline const std::map<std::string, int>& GetInstructionArgs() const { return iArgs; }

		/// <summary>
		/// A vector of all the stack values in this frame. This does not include upvalues, variable
		/// arguments, or the closure object. Index 0 will point to the base of the stack, and the
		/// last index will point to the top of the stack. These values are owned by this state
		/// object.
		/// </summary>
		/// <returns>Vector of copied StackValues.</returns>
		inline const std::vector<StackValue>& GetStackValues() const { return stackValues; }

		inline StkId GetStackBase() const { return basePtr; }

		inline StkId GetStackTop() const { return topPtr; }
	};

}