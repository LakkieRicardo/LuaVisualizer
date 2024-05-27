#pragma once

// Util functions to help print certain parts of the current Lua VM state

#include "LuaVisualizer.h"

#include <iostream>
#include <sstream>

/// <summary>
/// Prints all of the values in the stack from base to top pointer.
/// 
/// This will print the values after they have been modified by
/// LuaVMState::GetLastOperation. If there are relevant stack values in this
/// operation that need to be retrieved from before the current instruction,
/// the method PrintInstructionArgs will handle this.
/// </summary>
void PrintStackValues(const LuaV::LuaVisualizerState& vizer);

/// <summary>
/// Prints the logic behind the current operation if applicable, and also prints
/// the raw values of all of the arguments in this instruction.
/// </summary>
void PrintInstructionArgs(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer);

/// <summary>
/// Prints all of the global values. This takes up lots of screen space, so only
/// do this when the globals are updated using an instruction like SETTABUP.
/// </summary>
void PrintGlobals(const LuaV::LuaVisualizerState& vizer);

/// <summary>
/// Writes out an argument as a register in the following format:
/// 
/// R[arg] = x
/// </summary>
/// <param name="arg">Register value</param>
std::string RegisterArgAsString(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer, int arg);

/// <summary>
/// Renders a simple operation like add, multiply, subtract, etc. as a string.
/// Utilizes the following format:
/// 
/// R[a] = bVal _ cVal
/// 
/// Where the underscores represent the operation parameter.
/// </summary>
/// <param name="operation">Symbol for the operation that is taking place</param>
/// <param name="a">Register index of the target</param>
/// <param name="bVal">Display value of this operand</param>
/// <param name="cVal">Display value of this operand</param>
std::string SimpleOpAsString(std::string operation, int a, std::string bVal, std::string cVal);

/// <summary>
/// Reads the VM state stack and returns the value at that location.
/// </summary>
std::string GetStackVarAsString(const LuaV::LuaVMState& vmState, int idx);