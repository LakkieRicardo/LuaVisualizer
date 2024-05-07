#pragma once

#include "LuaValueConverter.h"
#include <string>
#include <sstream>

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			std::wstring ToString(const OpCode& opcode)
			{
				std::wstringstream output;
				if (opcode < 0 || opcode >= NUM_OPCODES)
				{
					output << "<unrecognized>";
				}
				else
				{
					output << opnames[opcode];
				}

				output << " (" << opcode << ")";
				return output.str();
			}
		}
	}
}