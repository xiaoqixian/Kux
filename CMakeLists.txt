cmake_minimum_required(VERSION 2.6)
project(Kux)

file(GLOB SOURCES "src/*.c")
set((CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-g -Wall -lpthread"))
add_executable(kux ${SOURCES})
