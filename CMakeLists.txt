cmake_minimum_required(VERSION 4.3)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_PREFIX_PATH "C:/glfw")
find_package(glfw3 CONFIG REQUIRED)

add_executable(Lab1 main.cpp glad.c
        core/Application.cpp
        core/Application.h
        render/Shader.cpp
        render/Shader.h
        core/Color.h
        render/Mesh.cpp
        render/Mesh.h
        core/Input.cpp
        core/Input.h
        game/Creature.cpp
        game/Creature.h
        "core/NdcPoint .h"
)

add_custom_command(TARGET Lab1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Lab1>/assets)

target_include_directories(Lab1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Lab1 PRIVATE glfw)