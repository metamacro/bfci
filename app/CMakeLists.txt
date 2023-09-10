set_local_and_parent(BFCI_APP_TARGET "bfci")

add_executable(
    ${BFCI_APP_TARGET}
    app.c)

set_target_properties(
    ${BFCI_APP_TARGET}
    PROPERTIES
    OUTPUT_NAME "bfci"
    SUFFIX "_${CMAKE_PROJECT_VERSION}")

target_include_directories(
    ${BFCI_APP_TARGET}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/src)

target_compile_features(
    ${BFCI_APP_TARGET}
    PRIVATE 
    c_std_17)

target_link_libraries(
    ${BFCI_APP_TARGET}
    PRIVATE 
    ${BFCI_LIB_TARGET})

