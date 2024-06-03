cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

project(
    LAPJV-algorithm-c
    VERSION 1.1
    DESCRIPTION "Code for Linear Assignment Problem"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory and run CMake from there."
    )
endif()

# ---- Add dependencies via CPM ----

# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)
include(cmake/tools.cmake)

# Fetch all dependcies using CPM

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
    NAME PackageProject.cmake
    GITHUB_REPOSITORY TheLartians/PackageProject.cmake
    VERSION 1.5.0
)

CPMAddPackage(
    NAME Format.cmake
    VERSION 1.6
    GITHUB_REPOSITORY TheLartians/Format.cmake
    OPTIONS # enable cmake formatting (optional)
            "FORMAT_CHECK_CMAKE ON"
)

# ---- Create library ----

set(sources "src/lap.cpp")

add_library(LAPJV ${sources})

target_include_directories(
    LAPJV PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                 $<INSTALL_INTERFACE:src/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

packageProject(
    NAME LAPJV
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAME}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src
    INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
    DEPENDENCIES ""
)
