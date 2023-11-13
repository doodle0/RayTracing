# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(MyProject LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set up clangd support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories for libraries and executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add fpng library files
add_library(fpng
    fpng/fpng.h
    fpng/fpng.cpp
)

# Add source files from src directory
add_library(raytracing
    src/bitmap.h
    src/color.h
    src/vector.h
    src/object.h
    src/scene.h
    src/tracing.h
    src/bitmap.cpp
    src/color.cpp
    src/vector.cpp
    src/object.cpp
    src/scene.cpp
    src/tracing.cpp
)

# Link the fpng library to raytracing
target_link_libraries(raytracing PUBLIC fpng)

# Additional flags for clangd (optional)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Specify include directories
target_include_directories(fpng PUBLIC ${CMAKE_SOURCE_DIR})

# Add tests dynamically
file(GLOB TEST_SOURCES tests/*.cpp)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE raytracing)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
    add_custom_target(test_${TEST_NAME}
        COMMAND ${TEST_NAME}
        DEPENDS ${TEST_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endforeach()

# Set target architecture and features
set_target_properties(fpng PROPERTIES COMPILE_FLAGS "-march=native -mpclmul")
