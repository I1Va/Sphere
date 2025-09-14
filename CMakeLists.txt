cmake_minimum_required(VERSION 3.16)
project(Sphere LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

add_executable(Sphere main.cpp src/visual.cpp src/calculations.cpp)

target_include_directories(Sphere
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_subdirectory(libs/geometry_module)
target_link_libraries(Sphere PUBLIC geometry_module)


target_link_libraries(Sphere PRIVATE SFML::Graphics SFML::Audio SFML::Network)

