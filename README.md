# Lua Visualizer

This is a tool to show you the inner workings of Lua! The current objectives are to display the memory stack, call stack, and instructions. :)

Currently, I am still in the early stages of development. Each instruction gets printed through a `vmcallback(lua_State*, Instruction*)` function right before it is executed, and in addition to the current state of the stack.