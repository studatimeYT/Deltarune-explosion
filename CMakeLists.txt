cmake_minimum_required(VERSION 3.25)

project(studatimeYT.deltarune-explosion)

# Geode v6 requires C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make sure the SDK environment variable exists
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! The environment variable is not set.")
endif()

# Load the SDK directly as a subdirectory
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Create the mod library target
add_library(${PROJECT_NAME} SHARED src/main.cpp)

# Setup the Geode mod
setup_geode_mod(${PROJECT_NAME})