cmake_minimum_required(VERSION 3.28)

project(Engine VERSION ${PROJECT_VERSION})

message("VERSION ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 26)
set(TARGET Engine)
set(TARGET_LIB EngineLib)

configure_file(EngineConfig.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Sources/EngineConfig.h)

set(SOURCES Sources/EngineConfig.h)

add_library(${TARGET_LIB} ${SOURCES})

find_package(fmt CONFIG REQUIRED)
find_package(bgfx CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(indicators CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

target_link_libraries(${TARGET_LIB} PRIVATE fmt::fmt)
target_link_libraries(${TARGET_LIB} PRIVATE spdlog::spdlog)
target_link_libraries(${TARGET_LIB} PRIVATE indicators::indicators)
target_link_libraries(${TARGET_LIB} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${TARGET_LIB} PRIVATE bgfx::bx bgfx::bgfx bgfx::bimg bgfx::bimg_decode)
target_link_libraries(${TARGET_LIB} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_executable(${TARGET} Sources/main.cpp)
target_link_libraries(${TARGET_LIB} PUBLIC)

add_test(AllTestsInMain ${TARGET})