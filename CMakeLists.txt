cmake_minimum_required(VERSION 3.28)
SET(CMAKE_TOOLCHAIN_FILE,  "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(game_framework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(GAME_SOURCE_FOLDER Games)

message("-----------------------------------")
message("PLATFORM ${CMAKE_SYSTEM_NAME}")
message("-----------------------------------")
message("BUILD TYPE ${CMAKE_BUILD_TYPE}")
message("-----------------------------------")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(WINDOWS)
endif ()

add_subdirectory(Engine)
add_subdirectory(Editor)

set(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)