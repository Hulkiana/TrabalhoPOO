cmake_minimum_required(VERSION 4.3)
project(Trabalho)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Trabalho
        Fabrica.cpp
        Fabrica.h
        main.cpp
        Posicao.cpp
        Posicao.h
        Settings.h
        Ecra.h
        Ecra.cpp)
