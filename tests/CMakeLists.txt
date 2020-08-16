add_custom_target(check ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS lightcxx_testing lightcxx_mock process_safe_wrapper
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_custom_target(check_and_upload ${CMAKE_CTEST_COMMAND} -D Experimental
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

include(LightCXXTests.cmake)

scan_for_lightcxx_tests(${CMAKE_CURRENT_SOURCE_DIR})
