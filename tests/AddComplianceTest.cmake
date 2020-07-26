function(add_compliance_test SECTION NAME)
    cmake_parse_arguments(ARGS "WILL_FAIL" "NO_COMPILE;OUTPUT_CONTAINS" "" ${ARGN})

    if (NOT ARGS_NO_COMPILE)
        set(test_name compliance.${SECTION}.${NAME})
        add_executable(${test_name} ${CMAKE_SOURCE_DIR}/tests/compliance/${SECTION}/${NAME}.cpp)
        target_link_libraries(${test_name} lightcxx_testing)
        add_test(NAME ${test_name} COMMAND ${test_name})
        add_dependencies(check ${test_name})
        if (ARGS_OUTPUT_CONTAINS)
            set_tests_properties(${test_name} PROPERTIES
                    PASS_REGULAR_EXPRESSION ${ARGS_OUTPUT_CONTAINS})
        endif ()
        if (ARGS_WILL_FAIL)
            set_tests_properties(${test_name} PROPERTIES WILL_FAIL TRUE)
        endif ()
    else ()
        foreach (fail_index RANGE ${ARGS_NO_COMPILE})
            set(test_name test.compliance.${SECTION}.${NAME}_${fail_index})
            add_executable(${test_name}
                    ${CMAKE_SOURCE_DIR}/tests/compliance/${SECTION}/${NAME}.cpp)
            target_link_libraries(${test_name} PUBLIC lightcxx_testing)
            target_compile_definitions(${test_name} PUBLIC NC_TEST_ID=${fail_index})
            set_target_properties(${test_name} PROPERTIES
                    EXCLUDE_FROM_ALL TRUE
                    EXCLUDE_FROM_DEFAULT_BUILD TRUE)
            add_test(NAME ${test_name}
                    COMMAND ${CMAKE_COMMAND}
                    --build .
                    --target ${test_name}
                    --config $<CONFIGURATION>
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
            set_tests_properties(${test_name} PROPERTIES WILL_FAIL TRUE)
        endforeach ()
    endif ()
endfunction()
