cmake_minimum_required(VERSION 3.29)

project(studatimeYT.deltarune-explosion)

# Geode v6 requires C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where the Geode SDK is hiding
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

find_package(geode REQUIRED)

setup_geode_mod(studatimeYT.deltarune-explosion)

target_sources(studatimeYT.deltarune-explosion PRIVATE src/main.cpp)