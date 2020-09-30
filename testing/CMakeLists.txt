add_library(lightcxx_testing STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/interceptor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/testing.c)
target_include_directories(lightcxx_testing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lightcxx_testing PUBLIC lightcxx)
if (NOT APPLE)
    target_link_libraries(lightcxx_testing PRIVATE dl)
endif ()

add_executable(process_safe_wrapper ${CMAKE_CURRENT_SOURCE_DIR}/process_safe_wrapper.c)

add_library(lightcxx_testing_interceptors_libc ${CMAKE_CURRENT_SOURCE_DIR}/interceptors/libc.cpp)
target_link_libraries(lightcxx_testing_interceptors_libc PUBLIC lightcxx_testing)
