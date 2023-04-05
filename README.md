# Lua Visualizer

This is a tool to show you the inner workings of Lua! The current objectives are to display the memory stack, call stack, and instructions. :)

Currently, I am still in the early stages of development. Each instruction gets printed through a `vmcallback(lua_State*, Instruction*)` function right before it is executed, and in addition to the current state of the stack.

Here is the current output based off `testscript.lua`:

```
VM: VARARGPREP A: 0
Stack size: 0

VM: GETTABUP A: 0, B: 0, C: 0
Stack size: 0

VM: LOADK A: 1, Bx: 1
Stack size: 0

VM: CALL A: 0, B: 2, C: 1
Stack size: 0

Hello Lua!
VM: SETTABUP A: 0, B: 2, C: 3
Stack size: 0

VM: GETTABUP A: 0, B: 0, C: 0
Stack size: 3
-1      (string): Hello Lua!
-2      (string): Hello Lua!
-3      (function): 00007FF786634890

VM: LOADK A: 1, Bx: 4
Stack size: 3
-1      (string): Hello Lua!
-2      (string): Hello Lua!
-3      (function): 00007FF786634890

VM: GETTABUP A: 2, B: 0, C: 2
Stack size: 3
-1      (string): Hello Lua!
-2      (string): Variable a =
-3      (function): 00007FF786634890

VM: CALL A: 0, B: 3, C: 1
Stack size: 3
-1      (number): 5
-2      (string): Variable a =
-3      (function): 00007FF786634890

Variable a =    5
VM: RETURN A: 0, B: 1, C: 1, k: 0
Stack size: 0
```