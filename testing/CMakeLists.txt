add_library(lightcxx_testing STATIC ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_include_directories(lightcxx_testing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(lightcxx_testing INTERFACE lightcxx)
target_compile_options(lightcxx_testing PUBLIC -nostdinc++)
target_link_options(lightcxx_testing PUBLIC --no-standard-libraries)
target_link_libraries(lightcxx_testing PUBLIC c PUBLIC c++abi)

add_library(lightcxx_mock SHARED ${CMAKE_CURRENT_SOURCE_DIR}/mock.cpp)
target_compile_options(lightcxx_mock PUBLIC -nostdinc++)
target_link_options(lightcxx_mock PUBLIC --no-standard-libraries)
target_link_libraries(lightcxx_mock PUBLIC c PUBLIC c++abi)

add_executable(process_safe_wrapper ${CMAKE_CURRENT_SOURCE_DIR}/process_safe_wrapper.c)
