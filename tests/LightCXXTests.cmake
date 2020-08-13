function(add_lightcxx_test filename section name)
    # Parse expectations from test file comments.
    file(STRINGS ${filename} lines)
    foreach (line ${lines})
        if (NOT (line MATCHES "^//EXPECT:.*$"))
            break()
        endif ()
        foreach(argument NO_COMPILE EXIT_CODE SIGNAL_CODE)
            if (line MATCHES "^//EXPECT:${argument} (.*)$")
                string(REPLACE "\\n" "\n" ${argument} "${CMAKE_MATCH_1}")
            endif ()
        endforeach()
        foreach(argument OUTPUT_CONTAINS OUTPUT_NOT_CONTAINS)
            if (line MATCHES "^//EXPECT:${argument} \"(.*)\"$")
                string(REPLACE "\\n" "\n" ${argument} "${CMAKE_MATCH_1}")
            endif ()
        endforeach()
    endforeach ()

    if (NO_COMPILE)
        foreach (fail_index RANGE ${NO_COMPILE})
            set(test_name compliance.${section}.${name}_${fail_index})
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

    set(test_name compliance.${section}.${name})
    add_executable(${test_name} ${filename})
    target_link_libraries(${test_name} lightcxx_testing)
    if (EXIT_CODE OR SIGNAL_CODE OR OUTPUT_CONTAINS OR OUTPUT_NOT_CONTAINS)
        add_test(NAME ${test_name} COMMAND process_safe_wrapper $<TARGET_FILE:${test_name}>)
    else ()
        add_test(NAME ${test_name} COMMAND ${test_name})
    endif ()
    add_dependencies(check ${test_name})

    if (OUTPUT_NOT_CONTAINS)
        set_tests_properties(${test_name} PROPERTIES FAIL_REGULAR_EXPRESSION
                "${OUTPUT_NOT_CONTAINS}")
    endif ()

    if (OUTPUT_CONTAINS)
        if (EXIT_CODE)
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "${OUTPUT_CONTAINS}.*\n----\nPROCESS EXITED WITH CODE: ${EXIT_CODE}")
        elseif (SIGNAL_CODE)
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "${OUTPUT_CONTAINS}.*\n----\nPROCESS EXITED BY SIGNAL: ${SIGNAL_CODE}")
        else ()
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "${OUTPUT_CONTAINS}")
        endif ()
    else ()
        if (EXIT_CODE)
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "\n----\nPROCESS EXITED WITH CODE: ${EXIT_CODE}")
        elseif (SIGNAL_CODE)
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION
                    "\n----\nPROCESS EXITED BY SIGNAL: ${SIGNAL_CODE}")
        endif ()
    endif ()
endfunction()

function (scan_for_lightcxx_tests directory)
    file(GLOB_RECURSE test_files LIST_DIRECTORIES false ${directory}/**/*.cpp)
    foreach(test_file ${test_files})
        if (test_file MATCHES "^.*/([0-9.]*)/(.*).cpp$")
            add_lightcxx_test(${test_file} ${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
        else ()
            message(WARNING "Compliance test path not recognized: ${test_file}")
        endif ()
    endforeach()
endfunction ()
