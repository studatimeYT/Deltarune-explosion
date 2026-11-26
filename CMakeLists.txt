cmake_minimum_required(VERSION 3.29)

project(deltarune-explosion)

# Load the Geode SDK directly instead of searching for it
include($ENV{GEODE_SDK}/cmake/GeodeFile.cmake)

setup_geode_mod(studatimeYT.deltarune-explosion)

target_sources(studatimeYT.deltarune-explosion PRIVATE src/main.cpp) PRIVATE src/main.cpp)
