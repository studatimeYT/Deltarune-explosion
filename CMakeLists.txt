cmake_minimum_required(VERSION 3.25)

# Set the project name to your exact mod ID
project(studatimeYT.deltarune-explosion)

# Geode v6 requires C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure the SDK environment variable exists
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()

# Load the SDK directly
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Create the mod library target with the exact same name
add_library(studatimeYT.deltarune-explosion SHARED src/main.cpp)

# Setup the Geode mod
setup_geode_mod(studatimeYT.deltarune-explosion)