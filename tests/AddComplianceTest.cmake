function(add_compliance_test SECTION NAME)
    cmake_parse_arguments(ARGS "" "NO_COMPILE;EXIT_CODE;SIGNAL_CODE;OUTPUT_CONTAINS;OUTPUT_NOT_CONTAINS" "" ${ARGN})

    if (ARGS_NO_COMPILE)
        foreach (fail_index RANGE ${ARGS_NO_COMPILE})
            set(test_name compliance.${SECTION}.${NAME}_${fail_index})
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
        return()
    endif ()

    set(test_name compliance.${SECTION}.${NAME})
    add_executable(${test_name} ${CMAKE_SOURCE_DIR}/tests/compliance/${SECTION}/${NAME}.cpp)
    target_link_libraries(${test_name} lightcxx_testing)
    if (ARGS_EXIT_CODE OR ARGS_SIGNAL_CODE OR ARGS_OUTPUT_CONTAINS OR ARGS_OUTPUT_NOT_CONTAINS)
        add_test(NAME ${test_name} COMMAND wrap_test $<TARGET_FILE:${test_name}>)
    else ()
        add_test(NAME ${test_name} COMMAND ${test_name})
    endif ()
    add_dependencies(check ${test_name})

    if (ARGS_OUTPUT_NOT_CONTAINS)
        set_tests_properties(${test_name} PROPERTIES FAIL_REGULAR_EXPRESSION
                "${ARGS_OUTPUT_NOT_CONTAINS}")
    endif ()

    if (ARGS_OUTPUT_CONTAINS)
        if (ARGS_EXIT_CODE)
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "${ARGS_OUTPUT_CONTAINS}.*\n----\nTEST EXITED WITH CODE: ${ARGS_EXIT_CODE}")
        elseif (ARGS_SIGNAL_CODE)
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "${ARGS_OUTPUT_CONTAINS}.*\n----\nTEST EXITED BY SIGNAL: ${ARGS_SIGNAL_CODE}")
        else ()
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "${ARGS_OUTPUT_CONTAINS}")
        endif ()
    else ()
        if (ARGS_EXIT_CODE)
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "\n----\nTEST EXITED WITH CODE: ${ARGS_EXIT_CODE}")
        elseif (ARGS_SIGNAL_CODE)
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "\n----\nTEST EXITED BY SIGNAL: ${ARGS_SIGNAL_CODE}")
        endif ()
    endif ()
endfunction()
