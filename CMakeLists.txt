PROJECT(Test-Compiler)
cmake_minimum_required(VERSION 3.2)

add_executable(main main.cpp tools/lexical.cpp tools/syntax.cpp tools/semantic.cpp Compiler.cpp)