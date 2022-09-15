function(init_testing_script)
    file(WRITE ${CMAKE_BINARY_DIR}/tests.sh
            "#!/usr/bin/env sh\n"
            "\n"
            "set -e\n"
            "\n"
            "${CMAKE_MAKE_PROGRAM} -C ${CMAKE_BINARY_DIR}\n"
            "\n"
            )
    if (APPLE)
        file(APPEND ${CMAKE_BINARY_DIR}/tests.sh "export MallocNanoZone=0\n\n")
    endif ()

    file(CHMOD ${CMAKE_BINARY_DIR}/tests.sh PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
endfunction()

function(append_to_testing_script)
    file(APPEND ${CMAKE_BINARY_DIR}/tests.sh "${ARGN}\n\n")
endfunction()

function(finish_testing_script)
    file(APPEND ${CMAKE_BINARY_DIR}/tests.sh "echo 'All tests passed!'\n\n")
endfunction()

macro(add_lightcxx_test_common_options target)
    AddTargetCompileWarnings(${target})
    target_link_libraries(${target} PUBLIC lightcxx_testing)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests)
endmacro()

function(add_lightcxx_test filename section name)
    # Parse expectations from test file comments.
    file(STRINGS ${filename} lines)
    set(SKIP_TEST OFF)
    set(EXIT "")
    set(STEPS "")
    set(NO_COMPILE "")
    foreach (line ${lines})
        if (NOT (line MATCHES "^//[\ ]*([A-Z_]*):([A-Z_]*) (.*)$"))
            break()
        endif ()
        set(keyword ${CMAKE_MATCH_1})
        set(argument ${CMAKE_MATCH_2})
        if ("${keyword}" STREQUAL "EXPECT" AND (("${argument}" STREQUAL "NO_COMPILE") OR ("${argument}" STREQUAL "EXIT") OR ("${argument}" STREQUAL "STEPS")))
            set(${argument} "${CMAKE_MATCH_3}")
        elseif ("${keyword}" STREQUAL "REQUEST" AND "${argument}" STREQUAL "SKIP")
            string(LENGTH "${CMAKE_MATCH_3}" REASON_LEN)
            math(EXPR REASON_LEN "${REASON_LEN} - 2")
            string(SUBSTRING "${CMAKE_MATCH_3}" 1 ${REASON_LEN} REASON)
            message(STATUS "Section [${section}] '${name}' ${REASON}")
            set(SKIP_TEST ON)
        endif ()
    endforeach ()

    if (SKIP_TEST)
        return()
    endif ()

    if (NOT (NO_COMPILE STREQUAL ""))
        set(NO_COMPILE_COUNT 1)
        set(NO_COMPILE_MESSAGE "\".*\"")
        if (NO_COMPILE MATCHES "^[0-9]+$")
            set(NO_COMPILE_COUNT ${NO_COMPILE})
        else ()
            set(NO_COMPILE_MESSAGE "${NO_COMPILE}")
        endif ()
        set(test_name ${section}.${name}.COMPILE_FAIL)
        append_to_testing_script("${CMAKE_BINARY_DIR}/negative_compile_test ${NO_COMPILE_COUNT} ${NO_COMPILE_MESSAGE} ${filename} ${CMAKE_CXX_COMPILER} -std=c++20 -isystem ${CMAKE_SOURCE_DIR}/include -I ${CMAKE_SOURCE_DIR}/testing -nostdinc++")
        return()
    endif ()

    set(test_name ${section}.${name})
    set(test_exe_name ${section}.${name})
    add_executable(${test_exe_name} ${filename})
    add_lightcxx_test_common_options(${test_exe_name})
    target_compile_options(${test_exe_name} PRIVATE
            -DTESTING_EXPECTED_STEPS="${STEPS}"
            -DTESTING_EXPECTED_EXIT="${EXIT}")
    append_to_testing_script(${CMAKE_CURRENT_BINARY_DIR}/tests/${test_exe_name})
endfunction()

function(scan_for_lightcxx_tests directory)
    init_testing_script()

    file(GLOB_RECURSE test_files ${directory}/**/*.cpp)
    foreach (test_file ${test_files})
        if (test_file MATCHES "^.*/([a-z.]*)/([^/]*).cpp$")
            if (CMAKE_MATCH_2 STREQUAL "skipped")
                message(STATUS "Section [${CMAKE_MATCH_1}] needs tests")
            elseif (NOT (CMAKE_MATCH_2 STREQUAL "nothing_to_do"))
                add_lightcxx_test(${test_file} ${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
            endif ()
        else ()
            message(WARNING "Test path not recognized: ${test_file}")
        endif ()
    endforeach ()

    finish_testing_script()
endfunction()
