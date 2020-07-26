enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND} --output-on-failure)

include(AddComplianceTest.cmake)

add_subdirectory(compliance)
