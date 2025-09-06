cmake_minimum_required(VERSION 3.16)
project(Sphere LANGUAGES CXX)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

add_executable(Sphere main.cpp)

target_include_directories(Sphere
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(Sphere PRIVATE SFML::Graphics SFML::Audio SFML::Network)

