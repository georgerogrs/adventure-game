cmake_minimum_required(VERSION 3.26)
project(adventure-game)

set(CMAKE_CXX_STANDARD 17)

add_executable(adventure_game GameEngine.cpp
        Player.cpp
        Player.h
        Room.cpp
        Room.h
        Object.h
        Object.cpp
        Enemy.cpp
        Enemy.h
)

include_directories(include)