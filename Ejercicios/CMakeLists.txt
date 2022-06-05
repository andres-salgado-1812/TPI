cmake_minimum_required(VERSION 3.21)
project(Ejercicios)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Ejercicios
        auxiliares.cpp
        auxiliares.h
        definiciones.h
        flota.cpp)
