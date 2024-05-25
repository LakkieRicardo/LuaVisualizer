#pragma once

// Util functions to help print certain parts of the current Lua VM state

#include "LuaVisualizer.h"

#include <iostream>
#include <sstream>

void PrintStackValues(const LuaV::LuaVisualizerState& vizer);

void PrintInstructionArgs(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer);

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