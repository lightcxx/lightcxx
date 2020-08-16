function(add_lightcxx_test filename section name)
    # Parse expectations from test file comments.
    file(STRINGS ${filename} lines)
    set(EXIT "CODE = 0")
    foreach (line ${lines})
        if (NOT (line MATCHES "^//[\ ]*EXPECT:([A-Z_]*) (.*)$"))
            break()
        endif ()
        set(argument ${CMAKE_MATCH_1})
        if (("${argument}" STREQUAL "NO_COMPILE") OR ("${argument}" STREQUAL "EXIT"))
            set(${argument} "${CMAKE_MATCH_2}")
        elseif ("${argument}" STREQUAL "STEPS")
            string(LENGTH "${CMAKE_MATCH_2}" STEPS_LEN)
            math(EXPR STEPS_LEN "${STEPS_LEN} - 2")
            string(SUBSTRING "${CMAKE_MATCH_2}" 1 ${STEPS_LEN} RAW_STEPS)
            set(STEPS "")
            foreach (step ${RAW_STEPS})
                string(APPEND STEPS "STEP: ${step}\n")
            endforeach()
        endif ()
    endforeach ()

    if (NO_COMPILE)
        foreach (fail_index RANGE ${NO_COMPILE})
            set(test_name ${section}.${name}_${fail_index})
            add_executable(${test_name} ${filename})
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

    set(test_name ${section}.${name})
    add_executable(${test_name} ${filename})
    target_link_libraries(${test_name} lightcxx_testing lightcxx_mock)
    add_test(
            NAME ${test_name}
            COMMAND process_safe_wrapper
            $<TARGET_FILE:${test_name}>)
    add_dependencies(check ${test_name})

    set_tests_properties(${test_name} PROPERTIES FAIL_REGULAR_EXPRESSION "EXPECTATION FAILED")
    set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION "^${STEPS}\n----\nPROCESS EXIT ${EXIT}")
endfunction()

function (scan_for_lightcxx_tests directory)
    file(GLOB_RECURSE test_files ${directory}/**/*.cpp)
    foreach(test_file ${test_files})
        if (test_file MATCHES "^.*/([0-9.]*)/(.*).cpp$")
            add_lightcxx_test(${test_file} ${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
        else ()
            message(WARNING "Test path not recognized: ${test_file}")
        endif ()
    endforeach()
endfunction ()