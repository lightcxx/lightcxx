cmake_minimum_required(VERSION 3.22)
project(lightcxx VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

option(LIGHTCXX_ENABLE_TESTS "Build lightcxx tests" OFF)

include(cmake/Warnings.cmake)

add_subdirectory(third_party)

function(AddLightCxxCommonOptions lightcxx_target)
    AddTargetCompileWarnings(${lightcxx_target})
    target_include_directories(${lightcxx_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_include_directories(${lightcxx_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(${lightcxx_target} SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_compile_options(${lightcxx_target} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-nostdinc++>)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_options(${lightcxx_target} PUBLIC -nodefaultlibs)
        if (NOT APPLE)
            target_link_libraries(${lightcxx_target} PUBLIC gcc gcc_eh)
        endif ()
    else ()
        target_link_options(${lightcxx_target} PUBLIC -nostdlib++)
    endif ()
    if (APPLE)
        target_link_libraries(${lightcxx_target} PUBLIC System)
    else ()
        target_link_libraries(${lightcxx_target} PUBLIC c pthread)
    endif ()
endfunction()

set(LIGHTCXX_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/any.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cassert.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cerrno.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cstdlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cstring.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/new.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stdexcept.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/typeinfo.cpp)

add_library(lightcxx_static STATIC ${LIGHTCXX_SRCS} $<TARGET_OBJECTS:third_party_libcxxabi_object>)
AddLightCxxCommonOptions(lightcxx_static)

add_library(lightcxx SHARED ${LIGHTCXX_SRCS} $<TARGET_OBJECTS:third_party_libcxxabi_object>)
AddLightCxxCommonOptions(lightcxx)
target_compile_options(lightcxx PRIVATE -fvisibility=hidden -fPIC -D_LIGHTCXX_BUILD_SHARED_LIB)
set_target_properties(lightcxx PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION})

install(DIRECTORY include DESTINATION .)
install(TARGETS lightcxx lightcxx_static DESTINATION lib)

if (LIGHTCXX_ENABLE_TESTS)
    add_library(testing STATIC ${CMAKE_CURRENT_SOURCE_DIR}/testing/testing.c)
    AddTargetCompileWarnings(testing)
    target_include_directories(testing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/testing)
    target_link_libraries(testing PUBLIC lightcxx_static)
    if (NOT APPLE)
        target_link_libraries(testing PRIVATE dl)
    endif ()

    add_executable(test_runner ${CMAKE_CURRENT_SOURCE_DIR}/testing/test_runner.c)
    AddTargetCompileWarnings(test_runner)
    set_target_properties(test_runner PROPERTIES
            OUTPUT_NAME test
            RUNTIME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(test_runner PRIVATE
            -DCOMPILER="${CMAKE_CXX_COMPILER}"
            -DAPPLE_ISYSROOT="${CMAKE_OSX_SYSROOT}"
            -DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            -DLIB_DIR="${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
            -DDEFAULT_TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests"
            -DDEFAULT_BUILD_CACHE_DIR="${CMAKE_CURRENT_BINARY_DIR}/tests")
    if (APPLE)
        target_compile_options(test_runner PRIVATE -DPLATFORM_IS_APPLE=1 -DPLATFORM_IS_LINUX=0)
    else ()
        target_compile_options(test_runner PRIVATE -DPLATFORM_IS_APPLE=0 -DPLATFORM_IS_LINUX=1)
    endif ()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(test_runner PRIVATE -DCOMPILER_IS_CLANG=0 -DCOMPILER_IS_GCC=1)
    else ()
        target_compile_options(test_runner PRIVATE -DCOMPILER_IS_CLANG=1 -DCOMPILER_IS_GCC=0)
    endif ()
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(test_runner PRIVATE -DOPT_IS_DEBUG=1 -DOPT_IS_RELEASE=0)
    elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        target_compile_options(test_runner PRIVATE -DOPT_IS_DEBUG=1 -DOPT_IS_RELEASE=1)
    else ()
        target_compile_options(test_runner PRIVATE -DOPT_IS_DEBUG=0 -DOPT_IS_RELEASE=1)
    endif ()
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests)

    add_custom_target(test
            COMMAND test_runner
            DEPENDS lightcxx_static testing test_runner)

    if ($ENV{CLION_IDE})
        message(STATUS "Adding all test files to a target for CLion")
        file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
        add_library(test_sources EXCLUDE_FROM_ALL OBJECT ${TEST_SOURCES})
        AddTargetCompileWarnings(test_sources)
        target_link_libraries(test_sources PUBLIC testing)
        set_target_properties(test_sources PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests)
        target_compile_options(test_sources PRIVATE -DTESTING_EXPECTED_STEPS="" -DTESTING_EXPECTED_EXIT="")
    endif ()
endif ()
