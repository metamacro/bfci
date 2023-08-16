set_local_and_parent(
    BFCI_LIB_TARGET
    "libbfci"
)

set(HEADER_LIST 
    "${PROJECT_SOURCE_DIR}/include/bfci/bfci.h"
    "${PROJECT_SOURCE_DIR}/include/bfci/data.h"
    "${PROJECT_SOURCE_DIR}/include/bfci/debug.h"
    "${PROJECT_SOURCE_DIR}/include/bfci/intermediate.h"
    "${PROJECT_SOURCE_DIR}/include/bfci/io.h"
    "${PROJECT_SOURCE_DIR}/include/bfci/memory.h"
    "${PROJECT_SOURCE_DIR}/include/bfci/utils.h")

set(SOURCE_LIST
    bfci.c
    data.c
    intermediate.c
    io.c
    memory.c)

add_library(
    ${BFCI_LIB_TARGET}
    ${SOURCE_LIST}
    ${HEADER_LIST})

set_target_properties(
    ${BFCI_LIB_TARGET}
    PROPERTIES
    PREFIX "")

target_include_directories(
    ${BFCI_LIB_TARGET} 
    PUBLIC
    ${PROJECT_SOURCE_DIR}/deps/uthash/include
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/misc)

if(ENABLE_DEBUG)
    target_compile_definitions(
        ${BFCI_LIB_TARGET} 
        PRIVATE 
        DEBUG)
endif()

target_compile_features(
    ${BFCI_LIB_TARGET} 
    PUBLIC 
    c_std_17)

