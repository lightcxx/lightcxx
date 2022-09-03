set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include_directories(${CMAKE_SOURCE_DIR}/src/)

set(COMMON_CLANG_GCC_WARNINGS
        -Werror
        -Wall
        -Wextra # reasonable and standard
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor.
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wpedantic # warn if non-standard C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wsign-compare
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
        )
set(GCC_WARNINGS
        ${COMMON_CLANG_GCC_WARNINGS}
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted

        -Wno-unknown-pragmas
        -Wno-attributes
        )
set(CLANG_WARNINGS
        ${COMMON_CLANG_GCC_WARNINGS}

        -Wno-unknown-warning-option
        )

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set_property(GLOBAL PROPERTY PROJECT_WARNINGS "${CLANG_WARNINGS}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_property(GLOBAL PROPERTY PROJECT_WARNINGS "${GCC_WARNINGS}")
else ()
    # TODO: Windows support!
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
    set_property(GLOBAL PROPERTY PROJECT_WARNINGS "")
endif ()

function(AddTargetCompileWarnings TARGET)
    get_property(warnings GLOBAL PROPERTY PROJECT_WARNINGS)
    if (warnings)
        target_compile_options(${TARGET} PRIVATE
                $<$<COMPILE_LANGUAGE:CXX>:${warnings}>)
    endif ()
endfunction()
