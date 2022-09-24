set(COMMON_CLANG_GCC_C_CXX_WARNINGS
        -Werror
        -Wall
        -Wextra # reasonable and standard
        -Wunused # warn on anything being unused
        -Wpedantic # warn if non-standard C/C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wsign-compare
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
        )

set(COMMON_CLANG_GCC_CXX_WARNINGS
        ${COMMON_CLANG_GCC_C_CXX_WARNINGS}
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor.
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        )
set(GCC_CXX_WARNINGS
        ${COMMON_CLANG_GCC_CXX_WARNINGS}
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted

        -Wno-unknown-pragmas
        -Wno-attributes
        )
set(CLANG_CXX_WARNINGS
        ${COMMON_CLANG_GCC_CXX_WARNINGS}

        -Wno-unknown-warning-option
        )

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set_property(GLOBAL PROPERTY CXX_WARNINGS "${CLANG_CXX_WARNINGS}")
    set_property(GLOBAL PROPERTY C_WARNINGS "${COMMON_CLANG_GCC_C_CXX_WARNINGS}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_property(GLOBAL PROPERTY CXX_WARNINGS "${GCC_CXX_WARNINGS}")
    set_property(GLOBAL PROPERTY C_WARNINGS "${COMMON_CLANG_GCC_C_CXX_WARNINGS}")
else ()
    # TODO: Windows support!
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
    set_property(GLOBAL PROPERTY CXX_WARNINGS "")
    set_property(GLOBAL PROPERTY C_WARNINGS "")
endif ()

function(AddTargetCompileWarnings TARGET)
    get_property(cxx_warnings GLOBAL PROPERTY CXX_WARNINGS)
    get_property(c_warnings GLOBAL PROPERTY C_WARNINGS)
    if (cxx_warnings)
        target_compile_options(${TARGET} PRIVATE
                $<$<COMPILE_LANGUAGE:CXX>:${cxx_warnings}>)
    endif ()
    if (c_warnings)
        target_compile_options(${TARGET} PRIVATE
                $<$<COMPILE_LANGUAGE:C>:${c_warnings}>)
    endif ()
endfunction()
