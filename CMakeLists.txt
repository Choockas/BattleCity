cmake_minimum_required(VERSION 3.0)

project(battlecity)

add_executable(battlecity main.cpp)

install(TARGETS battlecity RUNTIME DESTINATION bin)
