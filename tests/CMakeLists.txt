enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND} --output-on-failure)

add_executable(wrap_test wrap_test.c)
add_dependencies(check wrap_test)

include(AddComplianceTest.cmake)

add_subdirectory(compliance)
