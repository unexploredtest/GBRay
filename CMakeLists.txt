cmake_minimum_required(VERSION 3.10)

# Set the project name
project(GBRay VERSION 0.1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)


# Add the executable
# add_executable(GBRay main.cpp)

# Include directories (if you have headers in a separate folder)
# include_directories(src/include)

# Link libraries (if you have any external libraries)
# target_link_libraries(GBRay PRIVATE some_library)

# Optionally, you can add subdirectories for larger projects
# add_subdirectory(src)
# add_subdirectory(tests)

# Set the output directory for the executable
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Optionally, you can enable testing
# enable_testing()
# add_subdirectory(tests)
