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

# TODO: Move these warnings to a text file, shared with the test runner.
set(COMMON_CLANG_GCC_C_CXX_WARNINGS
        -Werror
        -Wall
        -Wextra # reasonable and standard
        -Wunused # warn on anything being unused
        -Wpedantic # warn if non-standard C/C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wsign-compare
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
        )
set(COMMON_CLANG_GCC_CXX_WARNINGS
        ${COMMON_CLANG_GCC_C_CXX_WARNINGS}
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor.
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        )
set(GCC_CXX_WARNINGS
        ${COMMON_CLANG_GCC_CXX_WARNINGS}
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
        -Wno-unknown-pragmas
        -Wno-attributes
        )
set(CLANG_CXX_WARNINGS
        ${COMMON_CLANG_GCC_CXX_WARNINGS}
        -Wno-unknown-warning-option
        )

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set_property(GLOBAL PROPERTY CXX_WARNINGS "${CLANG_CXX_WARNINGS}")
    set_property(GLOBAL PROPERTY C_WARNINGS "${COMMON_CLANG_GCC_C_CXX_WARNINGS}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_property(GLOBAL PROPERTY CXX_WARNINGS "${GCC_CXX_WARNINGS}")
    set_property(GLOBAL PROPERTY C_WARNINGS "${COMMON_CLANG_GCC_C_CXX_WARNINGS}")
else ()
    # TODO: Windows support!
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
    set_property(GLOBAL PROPERTY CXX_WARNINGS "")
    set_property(GLOBAL PROPERTY C_WARNINGS "")
endif ()

function(AddTargetCompileWarnings TARGET)
    get_property(cxx_warnings GLOBAL PROPERTY CXX_WARNINGS)
    get_property(c_warnings GLOBAL PROPERTY C_WARNINGS)
    if (cxx_warnings)
        target_compile_options(${TARGET} PRIVATE
                $<$<COMPILE_LANGUAGE:CXX>:${cxx_warnings}>)
    endif ()
    if (c_warnings)
        target_compile_options(${TARGET} PRIVATE
                $<$<COMPILE_LANGUAGE:C>:${c_warnings}>)
    endif ()
endfunction()

set(third_party_libcxxabi_object_src
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/abort_message.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_aux_runtime.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_demangle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_exception_storage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_guard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_personality.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_vector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_virtual.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/fallback_malloc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/private_typeinfo.cpp)
if ((UNIX OR FUCHSIA) AND NOT (APPLE OR CYGWIN))
    list(APPEND third_party_libcxxabi_object_src
            ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/src/cxa_thread_atexit.cpp)
endif ()

add_library(third_party_libcxxabi_object OBJECT ${third_party_libcxxabi_object_src})
target_include_directories(third_party_libcxxabi_object PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxx/src
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxx/include)
target_compile_options(third_party_libcxxabi_object PRIVATE -nostdinc++ -fPIC -D_LIBCPP_BUILDING_LIBRARY)

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

    add_executable(test_runner ${CMAKE_CURRENT_SOURCE_DIR}/testing/test_runner.c)
    AddTargetCompileWarnings(test_runner)
    set_target_properties(test_runner PROPERTIES
            OUTPUT_NAME test
            RUNTIME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(test_runner PRIVATE
            -DCOMPILER="${CMAKE_CXX_COMPILER}"
            -DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            -DLIB_DIR="${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
            -DDEFAULT_TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests"
            -DDEFAULT_CACHE_DIR="${CMAKE_CURRENT_BINARY_DIR}/tests")
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
        message(STATUS "Adding all test files to a target for CLion integration")
        file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
        add_library(test_sources EXCLUDE_FROM_ALL OBJECT ${TEST_SOURCES})
        AddTargetCompileWarnings(test_sources)
        target_link_libraries(test_sources PUBLIC testing)
    endif ()
endif ()
