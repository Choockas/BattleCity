cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME battlecity)
project(${PROJECT_NAME})



add_executable(${PROJECT_NAME} src/main.cpp src/resources/resourcesmanager.cpp src/shadeprogramm.cpp src/texture2D.cpp  src/sprite.cpp src/animatesprite.cpp src/game/game.h src/game/game.cpp src/game/tank.h src/game/tank.cpp)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

include_directories( external/glm )

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

target_include_directories(${PROJECT_NAME} PUBLIC inc src/resources/ )


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
