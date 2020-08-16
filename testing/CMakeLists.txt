add_library(lightcxx_testing STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/interceptor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_include_directories(lightcxx_testing PUBLIC ${CMAKE_HOME_DIRECTORY})
target_link_libraries(lightcxx_testing PUBLIC lightcxx)
if (NOT APPLE)
    target_link_libraries(lightcxx_testing PRIVATE dl)
endif ()

add_executable(process_safe_wrapper ${CMAKE_CURRENT_SOURCE_DIR}/process_safe_wrapper.c)
