#pragma once
#include "LuaVisualizer.h"

/*
  This file contains all of the functions for writing the VM status as
  strings in a command line console.
*/

void PrintStackValues(const LuaV::LuaVMState& vmState);

void PrintInstructionArgs(const LuaV::LuaVMState& vmState);