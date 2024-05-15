#pragma once
#include "LuaVisualizer.h"

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