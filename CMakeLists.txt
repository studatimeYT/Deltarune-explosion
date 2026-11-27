cmake_minimum_required(VERSION 3.29)

project(studatimeYT.deltarune-explosion)

# Geode v6 requires C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make sure the SDK environment variable exists
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! The environment variable is not set.")
endif()

# Load the SDK directly as a subdirectory instead of using find_package
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Set up the mod using the project name
setup_geode_mod(${PROJECT_NAME})

# Link your source file
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)