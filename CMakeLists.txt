cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeBuild")

project(MiniRenderer LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_definitions(-DUNICODE -D_UNICODE)
if (WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

file(GLOB_RECURSE SOURCE_FILE CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.inl"
    "${PROJECT_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE EXAMPLE_FILE CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/example/*.cpp")

source_group(TREE ${PROJECT_SOURCE_DIR}/src FILES ${SOURCE_FILE})

add_library(MiniRenderer STATIC ${SOURCE_FILE})
target_include_directories(MiniRenderer PUBLIC src)

foreach(example_main ${EXAMPLE_FILE})
    string(REGEX MATCHALL "[0-9A-Za-z_]*.cpp" tmp ${example_main})
    string(REGEX REPLACE ".cpp" "" file_name ${tmp})

    add_executable(${file_name} ${example_main})
    target_link_libraries(${file_name} PUBLIC MiniRenderer)
    target_include_directories(${file_name} PUBLIC src)
    set_target_properties(${file_name} PROPERTIES FOLDER "Example")
endforeach()


# VS startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example1_triangle)