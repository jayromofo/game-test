mkdir -p ./bin
g++ src/main.c -o bin/my_game $(pkg-config --cflags --libs sdl3)
exec ./bin/my_game
