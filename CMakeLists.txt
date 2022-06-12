cmake_minimum_required(VERSION 3.22)
project(lightcxx)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LIGHTCXX_ENABLE_TESTS "Build lightcxx tests" OFF)

add_subdirectory(third_party)

add_library(lightcxx STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cstdlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/new.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/typeinfo.cpp

        $<TARGET_OBJECTS:third_party_libcxxabi_object>
        )
target_include_directories(lightcxx
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libcxxabi/include)
target_include_directories(lightcxx SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(lightcxx PUBLIC -nostdinc++)
target_link_options(lightcxx PUBLIC -nostdlib++)
if (APPLE)
    target_link_libraries(lightcxx PUBLIC System)
else ()
    target_link_libraries(lightcxx PUBLIC c PUBLIC pthread)
endif ()

install(DIRECTORY include DESTINATION .)
install(TARGETS lightcxx DESTINATION lib)

if (LIGHTCXX_ENABLE_TESTS)
    enable_testing()
    include(cmake/Tests.cmake)

    add_library(lightcxx_testing STATIC testing/interceptor.c testing/testing.c)
    target_include_directories(lightcxx_testing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/testing)
    target_link_libraries(lightcxx_testing PUBLIC lightcxx)
    if (NOT APPLE)
        target_link_libraries(lightcxx_testing PRIVATE dl)
    endif ()

    add_executable(process_safe_wrapper testing/process_safe_wrapper.c)

    add_library(lightcxx_testing_interceptors_libc testing/interceptors/libc.cpp)
    target_link_libraries(lightcxx_testing_interceptors_libc PUBLIC lightcxx_testing)

    scan_for_lightcxx_tests(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif ()
