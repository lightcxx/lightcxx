set(third_party_libcxxabi_object_src
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/abort_message.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_aux_runtime.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_demangle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_exception_storage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_guard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_personality.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_vector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_virtual.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/fallback_malloc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/private_typeinfo.cpp)
if ((UNIX OR FUCHSIA) AND NOT (APPLE OR CYGWIN))
    list(APPEND third_party_libcxxabi_object_src
            ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/src/cxa_thread_atexit.cpp)
endif()

add_library(third_party_libcxxabi_object OBJECT ${third_party_libcxxabi_object_src})
target_include_directories(third_party_libcxxabi_object PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxx/src
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxxabi/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libcxx/include)
target_compile_options(third_party_libcxxabi_object PRIVATE -nostdinc++ -fPIC)
