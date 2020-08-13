enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND} --output-on-failure)

add_executable(wrap_test wrap_test.c)
add_dependencies(check wrap_test)

include(ComplianceTests.cmake)

scan_for_compliance_tests(${CMAKE_CURRENT_SOURCE_DIR}/compliance)
