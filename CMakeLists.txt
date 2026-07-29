cmake_minimum_required(VERSION 4.3)
project(ChessC)

set(CMAKE_CXX_STANDARD 23)

add_executable(ChessC main.cpp
        piece.h
        piece.cpp)
