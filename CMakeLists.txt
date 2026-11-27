cmake_minimum_required(VERSION 3.29)

project(studatimeYT.deltarune-explosion)

# Geode v6 requires C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Now that mod.json is valid, the Action downloads the SDK correctly
# and find_package will locate it perfectly.
find_package(geode REQUIRED)

setup_geode_mod(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)