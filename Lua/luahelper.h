#pragma once

#include "include\lua.h"
#include "include\luaconf.h"
#include "include\lualib.h"
#include "include\llimits.h"

void usehelper(lua_State* L, void (*vmcallback)(lua_State* L, Instruction i))
{
	L->usehelpers = 1;
}