cmake_minimum_required(VERSION 3.22)
project(lightcxx VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LIGHTCXX_ENABLE_TESTS "Build lightcxx tests" OFF)

add_subdirectory(third_party)

function(AddLightCxxCommonOptions lightcxx_target)
    target_include_directories(${lightcxx_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(${lightcxx_target} SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_compile_options(${lightcxx_target} PUBLIC -nostdinc++)
    target_link_options(${lightcxx_target} PUBLIC -nostdlib++)
    if (APPLE)
        target_link_libraries(${lightcxx_target} PUBLIC System)
    else ()
        target_link_libraries(${lightcxx_target} PUBLIC c PUBLIC pthread)
    endif ()
endfunction()

set(LIGHTCXX_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cstdlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/new.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/typeinfo.cpp)

add_library(lightcxx_static STATIC ${LIGHTCXX_SRCS} $<TARGET_OBJECTS:third_party_libcxxabi_object>)
AddLightCxxCommonOptions(lightcxx_static)
set_target_properties(lightcxx_static PROPERTIES OUTPUT_NAME lightcxx)

add_library(lightcxx SHARED ${LIGHTCXX_SRCS} $<TARGET_OBJECTS:third_party_libcxxabi_object>)
AddLightCxxCommonOptions(lightcxx)
target_compile_options(lightcxx PRIVATE -fvisibility=hidden -fPIC)
set_target_properties(lightcxx PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION})

install(DIRECTORY include DESTINATION .)
install(TARGETS lightcxx lightcxx_static DESTINATION lib)

if (LIGHTCXX_ENABLE_TESTS)
    enable_testing()
    include(cmake/Tests.cmake)

    add_library(lightcxx_testing STATIC testing/testing.c)
    target_include_directories(lightcxx_testing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/testing)
    target_link_libraries(lightcxx_testing PUBLIC lightcxx_static)
    if (NOT APPLE)
        target_link_libraries(lightcxx_testing PRIVATE dl)
    endif ()

    scan_for_lightcxx_tests(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif ()
