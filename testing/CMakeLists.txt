add_library(lightcxx_testing STATIC ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_include_directories(lightcxx_testing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(lightcxx_testing INTERFACE lightcxx)
