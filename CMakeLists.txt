cmake_minimum_required(VERSION 3.20)
project(CardTetris LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(game_core src/Board.cpp src/Game.cpp src/Console.cpp)
target_include_directories(game_core PUBLIC src)

if(MSVC)
    target_compile_options(game_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(game_core PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()

add_executable(card_tetris src/main.cpp)
target_link_libraries(card_tetris PRIVATE game_core)

add_executable(card_tetris_tests tests/BoardTests.cpp src/Board.cpp)
target_include_directories(card_tetris_tests PRIVATE src)
if(MSVC)
    target_compile_options(card_tetris_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(card_tetris_tests PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()

enable_testing()
add_test(NAME CardTetrisUnitTests COMMAND card_tetris_tests)
