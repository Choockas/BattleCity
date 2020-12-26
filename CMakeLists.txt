cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME battlecity)
project(${PROJECT_NAME})

add_executable(battlecity main.cpp)

install(TARGETS battlecity RUNTIME DESTINATION bin)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
