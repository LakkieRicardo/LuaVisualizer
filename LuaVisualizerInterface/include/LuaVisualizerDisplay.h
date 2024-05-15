#pragma once

// Util functions to help print certain parts of the current Lua VM state

#include "LuaVisualizer.h"

#include <iostream>
#include <sstream>

/*
  This file contains all of the functions for writing the VM status as
  strings in a command line console.
*/

void PrintStackValues(const LuaV::LuaVMState& vmState);

void PrintInstructionArgs(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer);

/// <summary>
/// Writes out an argument as a register in the following format: R[arg] = x
/// </summary>
/// <param name="arg">Register value</param>
std::string RegisterArgAsString(const LuaV::LuaVMState& vmState, const LuaV::LuaVisualizerState& vizer, int arg);