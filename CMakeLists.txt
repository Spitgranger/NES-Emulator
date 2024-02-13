cmake_minimum_required(VERSION 3.27)
project(NES_EMU)

set(CMAKE_CXX_STANDARD 14)

add_executable(NES_EMU main.cpp
        Bus.cpp
        Bus.h
        CPU6502.cpp
        CPU6502.h)
