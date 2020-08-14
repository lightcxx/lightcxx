enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND} --output-on-failure)
add_dependencies(check lightcxx_testing lightcxx_mock process_safe_wrapper)

include(LightCXXTests.cmake)

scan_for_lightcxx_tests(${CMAKE_CURRENT_SOURCE_DIR}/compliance)
