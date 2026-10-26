# mkdir -p ./bin
# g++ src/main.c -o bin/my_game $(pkg-config --cflags --libs sdl3)
# exec ./bin/my_game

#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE="${1:-Debug}"

cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
cmake --build build -j
# exec ./build/mygame
