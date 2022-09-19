cmake_minimum_required(VERSION 3.22)
project(lightcxx VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cstdlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/new.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stdexcept.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/typeinfo.cpp)

add_library(lightcxx_static STATIC ${LIGHTCXX_SRCS} $<TARGET_OBJECTS:third_party_libcxxabi_object>)
AddLightCxxCommonOptions(lightcxx_static)
set_target_properties(lightcxx_static PROPERTIES OUTPUT_NAME lightcxx)

add_library(lightcxx SHARED ${LIGHTCXX_SRCS} $<TARGET_OBJECTS:third_party_libcxxabi_object>)
AddLightCxxCommonOptions(lightcxx)
target_compile_options(lightcxx PRIVATE -fvisibility=hidden -fPIC -D_LIGHTCXX_BUILD_SHARED_LIB)
set_target_properties(lightcxx PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION})

install(DIRECTORY include DESTINATION .)
install(TARGETS lightcxx lightcxx_static DESTINATION lib)

if (LIGHTCXX_ENABLE_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Tests.cmake)

    add_library(lightcxx_testing STATIC ${CMAKE_CURRENT_SOURCE_DIR}/testing/testing.c)
    AddTargetCompileWarnings(lightcxx_testing)
    target_include_directories(lightcxx_testing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/testing)
    target_link_libraries(lightcxx_testing PUBLIC lightcxx_static)
    if (NOT APPLE)
        target_link_libraries(lightcxx_testing PRIVATE dl)
    endif ()

    add_executable(negative_compile_test ${CMAKE_CURRENT_SOURCE_DIR}/testing/negative_compile_test.c)

    scan_for_lightcxx_tests(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif ()
