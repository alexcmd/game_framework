cmake_minimum_required(VERSION 3.28)

project(Engine VERSION ${PROJECT_VERSION})

message("VERSION ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 26)
set(TARGET Engine)
set(TARGET_LIB EngineLib)

enable_testing()

configure_file(EngineConfig.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Sources/EngineConfig.h)

set(SOURCES Sources/EngineConfig.h Sources/Engine.h)

find_package(fmt CONFIG REQUIRED)
find_package(bgfx CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(indicators CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

add_library(${TARGET_LIB} ${SOURCES})

target_link_libraries(${TARGET_LIB} PUBLIC glfw)
target_link_libraries(${TARGET_LIB} PUBLIC fmt::fmt)
target_link_libraries(${TARGET_LIB} PUBLIC spdlog::spdlog)
target_link_libraries(${TARGET_LIB} PUBLIC indicators::indicators)
target_link_libraries(${TARGET_LIB} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${TARGET_LIB} PUBLIC bgfx::bx bgfx::bgfx bgfx::bimg bgfx::bimg_decode)
target_link_libraries(${TARGET_LIB} PUBLIC GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(${TARGET_LIB} PUBLIC Vulkan::Vulkan)
target_link_libraries(${TARGET_LIB} PUBLIC GPUOpen::VulkanMemoryAllocator)

add_executable(${TARGET} Sources/main.cpp)
target_link_libraries(${TARGET} PRIVATE ${TARGET_LIB})

add_test(AllTestsInMain ${TARGET})

