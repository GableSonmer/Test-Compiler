PROJECT(Test-Compiler)
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
add_executable(main main.cpp Compiler.cpp
        lib/lexical/lexical.cpp lib/semantic/semantic.cpp lib/machine/machine.cpp)