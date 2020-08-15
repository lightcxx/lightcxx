add_library(lightcxx_testing STATIC ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_include_directories(lightcxx_testing PUBLIC ${CMAKE_HOME_DIRECTORY})
target_link_libraries(lightcxx_testing PUBLIC lightcxx)

add_library(lightcxx_mock STATIC ${CMAKE_CURRENT_SOURCE_DIR}/mock.cpp)
target_link_libraries(lightcxx_mock PUBLIC lightcxx)
if (NOT APPLE)
    target_link_libraries(lightcxx_mock PRIVATE dl)
endif ()

add_executable(process_safe_wrapper ${CMAKE_CURRENT_SOURCE_DIR}/process_safe_wrapper.c)
