*Meson build for LuaJIT 2*

This repository mirrors the source code for LuaJIT 2 with the addition of a Meson build.

You can find more information about LuaJIT in the [LuaJIT's homepage](http://luajit.org/).

## Why Meson ?

Because it is better than Makefiles and works better with [Little Library Helper](https://github.com/franko/lhelper) to build and install LuaJIT without any hassle, on Linux or Windows.

The .pc files installed with original Makefiles is installed in the wrong directory on Debian systems.

## How to use it?

From the source directory:

```sh
meson setup build
ninja -C build
ninja -C build install
```
more information from the [Meson Quick guide](https://mesonbuild.com/Quick-guide.html).

## What is LuaJIT? (extract from LuaJIT's README)

LuaJIT is a Just-In-Time (JIT) compiler for the Lua programming language.

Project Homepage: http://luajit.org/

LuaJIT is Copyright (C) 2005-2017 Mike Pall.
LuaJIT is free software, released under the MIT license.
See full Copyright Notice in the COPYRIGHT file or in luajit.h.

Documentation for LuaJIT is available in HTML format.
Please point your favorite browser to:

 doc/luajit.html
