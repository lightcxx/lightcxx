cmake_minimum_required(VERSION 3.16)
project(lightcxx)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIGHTCXX_ENABLE_TESTS ON)

add_library(lightcxx STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cstdlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/new.cpp
        )
target_include_directories(lightcxx PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(lightcxx INTERFACE SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(lightcxx PUBLIC -nostdinc++)
target_link_options(lightcxx PUBLIC --no-standard-libraries)
target_link_libraries(lightcxx PUBLIC c PUBLIC c++abi)

if (LIGHTCXX_ENABLE_TESTS)
    add_subdirectory(testing)
    add_subdirectory(tests)
endif ()
