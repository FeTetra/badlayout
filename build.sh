#!/bin/bash

CSRCS="main.c layout.c"
INCLUDE="-lraylib"
INCLUDE_BREW="-I/opt/homebrew/include -L/opt/homebrew/lib"
INCLUDE_DARWIN="-framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL"
GCCFLAGS="-g"

# TODO: macos isnt the only thing out there
gcc $CSRCS $INCLUDE $INCLUDE_DARWIN $INCLUDE_BREW $GCCFLAGS