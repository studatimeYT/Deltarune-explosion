cmake_minimum_required(VERSION 3.25)

project(studatimeYT.deltarune-explosion)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK environment variable!")
endif()

# Explicitly point CMake to the Geode SDK's cmake folder
file(TO_CMAKE_PATH "$ENV{GEODE_SDK}/cmake" GEODE_CMAKE_DIR)
set(geode_DIR "${GEODE_CMAKE_DIR}" CACHE PATH "Geode SDK CMake dir")

find_package(geode REQUIRED)

setup_geode_mod(studatimeYT.deltarune-explosion)
target_sources(studatimeYT.deltarune-explosion PRIVATE src/main.cpp)