cmake_minimum_required(VERSION 3.24)
project(mygame C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG)

add_library(util STATIC src/util/str.c)
target_include_directories(util PUBLIC src)

add_library(engine STATIC
    src/engine/window.c src/engine/input.c src/engine/renderer.c
    src/engine/assets.c src/engine/audio.c src/engine/timing.c
    src/engine/scene.c)
target_link_libraries(engine PUBLIC util SDL3::SDL3)

file(GLOB_RECURSE GAME_SRC CONFIGURE_DEPENDS src/game/*.c)
add_executable(mygame src/main.c src/app.c ${GAME_SRC})
target_link_libraries(mygame PRIVATE engine)

target_compile_options(mygame PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>)
target_compile_options(mygame PRIVATE
    $<$<AND:$<CONFIG:Debug>,$<C_COMPILER_ID:GNU,Clang>>:-fsanitize=address,undefined>)
target_link_options(mygame PRIVATE
    $<$<AND:$<CONFIG:Debug>,$<C_COMPILER_ID:GNU,Clang>>:-fsanitize=address,undefined>)

add_custom_command(TARGET mygame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:mygame>/assets)
