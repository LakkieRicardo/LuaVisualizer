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