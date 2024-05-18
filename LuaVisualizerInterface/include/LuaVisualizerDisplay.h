#pragma once

// Util functions to help print certain parts of the current Lua VM state

#include "LuaVisualizer.h"

#include <iostream>
#include <sstream>

void PrintStackValues(const LuaV::LuaVisualizerState& vizer);

void PrintInstructionArgs(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer);

/// <summary>
/// Writes out an argument as a register in the following format: R[arg] = x
/// </summary>
/// <param name="arg">Register value</param>
std::string RegisterArgAsString(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer, int arg);

/// <summary>
/// 
/// </summary>
/// <param name="operation"></param>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="bVal"></param>
/// <param name="cVal"></param>
std::string SimpleOpAsString(std::string operation, int a, int b, int c, std::string bVal, std::string cVal);

/// <summary>
/// 
/// </summary>
/// <param name="vmState"></param>
/// <param name="idx"></param>
std::string GetStackVarAsString(const LuaV::LuaVMState& vmState, int idx);