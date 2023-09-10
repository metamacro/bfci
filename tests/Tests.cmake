include(CTest)

enable_testing()

set(TEST_HELP help)
add_test(
    NAME ${TEST_HELP}
    COMMAND $<TARGET_FILE:${BFCI_APP_TARGET}>
)

set_tests_properties(
    ${TEST_HELP}
    PROPERTIES
    WILL_FAIL TRUE
)
