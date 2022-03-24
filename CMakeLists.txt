cmake_minimum_required(VERSION 3.16)
project(lightcxx)

cmake_policy(SET CMP0110 OLD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIGHTCXX_ENABLE_TESTS ON)

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

if (LIGHTCXX_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(testing)
    add_subdirectory(tests)
endif ()
