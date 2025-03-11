cmake_minimum_required(VERSION 3.10)

project(GBRay VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(externals/raylib)

add_subdirectory(src)

# Optionally, you can add subdirectories for larger projects
# add_subdirectory(src)
# add_subdirectory(tests)

# Optionally, you can enable testing
# enable_testing()
# add_subdirectory(tests)
