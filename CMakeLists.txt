cmake_minimum_required(VERSION 3.26)
project(adventure-game)

set(CMAKE_CXX_STANDARD 17)

add_executable(adventure_game main.cpp
        Player.cpp
        Player.h
        Room.cpp
        Room.h
        Item.cpp
        Item.h
        Enemy.cpp
        Enemy.h
        Objective.cpp
        Objective.h
        GameBuilder.cpp
        GameBuilder.h)
