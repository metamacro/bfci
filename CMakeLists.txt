cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "BrainFuckCInterpreter")

project(
    ${PROJECT_NAME}
    VERSION 0.1.0
    DESCRIPTION "BrainFuck interpreter written  \
                 in the C programming language"
    LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY C_STANDARD C17)
set_property(GLOBAL PROPERTY C_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY C_EXTENSIONS ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")
include(CompileOptions)
include(Macros)

git_submodule_update_init()

add_subdirectory(src)
add_subdirectory(app)
