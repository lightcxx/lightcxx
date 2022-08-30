#ifndef _LIGHTCXX_GUARD_SRC_EXPORT_H
#define _LIGHTCXX_GUARD_SRC_EXPORT_H

#ifdef _WIN32
#    define _EXPORT __declspec(dllexport)
#    define _EXPORT_WEAK __declspec(dllexport)
#else
#    ifdef __CYGWIN__
#        define _EXPORT __declspec(dllexport)
#        define _EXPORT_WEAK __declspec(dllexport)
#    else
#        if __GNUC__ >= 4
#            define _EXPORT __attribute__((visibility("default")))
#            define _EXPORT_WEAK __attribute__((visibility("default"), weak))
#        else
#            define _EXPORT
#            define _EXPORT_WEAK
#        endif
#    endif
#endif

#endif
