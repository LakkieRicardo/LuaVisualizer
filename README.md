# Lua Visualizer

This is a tool to show you the inner workings of Lua! The current objectives are to display the memory stack, call stack, and instructions. 😊

Currently, the project is structured like this:

| Project                  | Description                                                     |
|--------------------------|-----------------------------------------------------------------|
| Lua                      | Modified Lua repository from github.com/lua/lua.                |
| Lua Visualizer           | Interrogates and updates the Lua VM state.                      |
| Lua Visualizer Test      | Ensures the behavior of the visualizer is correct.              |
| Lua Visualizer Interface | Displays the VM state in a somewhat user-friendly manner.       |

The plans are to display the contents of the stack, the list of instructions, the instruction pointer, global variables, upvalues, constants, registers, and any other information relevant to program execution.

The purpose of this program isn't *necessarily* to debug Lua programs, but instead it's to help understand how Lua works in general, and also to be able to extend that knowledge to other languages!

Right now, this program doesn't have any published binaries nor any proper visualization. All there is right now is the list of instructions that will be executed in the current context of the script.

## Build System

This project uses a `.sln` file generated using Visual Studio 2022. It uses the included MS build tools and VC++, and can be built on either x86 or x64 architectures. There are no other guarantees for support.

I plan on moving to another build system, or maybe even creating a build system by referencing the Lua Visualizer binary in a language like Python.