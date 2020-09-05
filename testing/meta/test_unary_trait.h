#ifndef TESTING_META_TEST_UNARY_TRAIT_H
#define TESTING_META_TEST_UNARY_TRAIT_H

#include <type_traits>

class Class {
    [[maybe_unused]] int x[2];
    [[maybe_unused]] char y[4];
};

union Union {
    [[maybe_unused]] int x[2];
    [[maybe_unused]] char y[4];
};

enum [[maybe_unused]] Enum{
  e_ok,
  e_error,
};

enum class [[maybe_unused]] EnumClass{
  ok,
  error,
};

struct incomplete_type;

#define TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, TP)                                         \
    static_assert(std::is_base_of_v<std::bool_constant<EXPECTED>, TRAIT<TP>>,                      \
                  #TRAIT "<" #TP "> must derive from from std::bool_constant<" #EXPECTED ">");     \
    static_assert(TRAIT<TP>::value == EXPECTED, #TRAIT "<" #TP ">::value must equal " #EXPECTED);  \
    static_assert(std::is_same_v<TRAIT<TP>::type, std::bool_constant<EXPECTED>>,                   \
                  #TRAIT "<" #TP ">::type must be same as std::bool_constant<" #EXPECTED ">");     \
    static_assert(TRAIT##_v<TP> == EXPECTED, #TRAIT "_v<" #TP "> must equal " #EXPECTED);          \
    static_assert(std::is_same_v<TRAIT##_t<TP>, std::bool_constant<EXPECTED>>,                     \
                  #TRAIT "_t<" #TP "> must be same as std::bool_constant<" #EXPECTED ">")

#define TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, TP)                                      \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, TP);                                            \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, TP const);                                      \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, TP volatile);                                   \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, TP const volatile)

#define TEST_UNARY_TRAIT_AGAINST_VOID(EXPECTED, TRAIT)                                             \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, void)

#define TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(EXPECTED, TRAIT)                                        \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, decltype(nullptr))

#define TEST_UNARY_TRAIT_AGAINST_INTEGRAL(EXPECTED, TRAIT)                                         \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, bool);                                       \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, char);                                       \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, char8_t);                                    \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, char16_t);                                   \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, char32_t);                                   \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, wchar_t);                                    \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, signed char);                                \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, short int);                                  \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, int);                                        \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, long int);                                   \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, long long int);                              \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, unsigned char);                              \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, unsigned short int);                         \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, unsigned int);                               \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, unsigned long int);                          \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, unsigned long long int)

#define TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(EXPECTED, TRAIT)                                   \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, float);                                      \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, double);                                     \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, long double)

#define TEST_UNARY_TRAIT_AGAINST_ARRAY(EXPECTED, TRAIT)                                            \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int[10]);                                       \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const int[10]);                                 \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, volatile int[10]);                              \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const volatile int[10]);                        \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int[10][10]);                                   \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int[]);                                         \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const int[]);                                   \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, volatile int[]);                                \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const volatile int[]);                          \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int[][10]);                                     \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int[][10][10])

#define TEST_UNARY_TRAIT_AGAINST_POINTER(EXPECTED, TRAIT)                                          \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, void*);                                      \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, const void*);                                \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, volatile void*);                             \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, const volatile void*);                       \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, int*);                                       \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, int**);                                      \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, int***);                                     \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, incomplete_type*);                           \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (**)(int));                                 \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (*volatile* const volatile)(int));          \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (*const* const)(int));                      \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (*)(int));                                  \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (*const)(int));                             \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (*volatile)(int));                          \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (*const volatile)(int))

#define TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(EXPECTED, TRAIT)                                 \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int&);                                          \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const int&);                                    \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, volatile int&);                                 \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const volatile int&);                           \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (&)(int));                                  \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int*&);                                         \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int* const&);                                   \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int* volatile&);                                \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int* const volatile&);                          \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, incomplete_type&);                              \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const incomplete_type&);                        \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, volatile incomplete_type&);                     \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const volatile incomplete_type&)

#define TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(EXPECTED, TRAIT)                                 \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int&&);                                         \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const int&&);                                   \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, volatile int&&);                                \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const volatile int&&);                          \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int(&&)(int));                                  \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int*&&);                                        \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int* const&&);                                  \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int* volatile&&);                               \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int* const volatile&&);                         \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, incomplete_type&&);                             \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const incomplete_type&&);                       \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, volatile incomplete_type&&);                    \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, const volatile incomplete_type&&)

#define TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(EXPECTED, TRAIT)                            \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, int Class::*);                               \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, Class Class::*);                             \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, Class* Class::*)

#define TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(EXPECTED, TRAIT)                          \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (Class::*)(int, int));                      \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (Class::*const)(int, int));                 \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (Class::*volatile)(int, int));              \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int (Class::*const volatile)(int, int));        \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, Class (Class::*)(int, Class Class::*));         \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, Class (Class::*const)(int, Class Class::*));    \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, Class (Class::*volatile)(int, Class Class::*)); \
    TEST_UNARY_TRAIT_AGAINST_TYPE(                                                                 \
      EXPECTED, TRAIT, Class (Class::*const volatile)(int, Class Class::*));                       \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, Class Class::* (Class::*)(int, int));           \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, Class Class::* (Class::*const)(int, int));      \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, Class Class::* (Class::*volatile)(int, int));   \
    TEST_UNARY_TRAIT_AGAINST_TYPE(                                                                 \
      EXPECTED, TRAIT, Class Class::* (Class::*const volatile)(int, int))

#define TEST_UNARY_TRAIT_AGAINST_ENUM(EXPECTED, TRAIT)                                             \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, Enum);                                       \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, EnumClass)

#define TEST_UNARY_TRAIT_AGAINST_UNION(EXPECTED, TRAIT)                                            \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, Union)

#define TEST_UNARY_TRAIT_AGAINST_CLASS(EXPECTED, TRAIT)                                            \
    TEST_UNARY_TRAIT_AGAINST_CV_TYPE(EXPECTED, TRAIT, Class)

#define TEST_UNARY_TRAIT_AGAINST_FUNCTION(EXPECTED, TRAIT)                                         \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, void());                                        \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int());                                         \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int(int));                                      \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int(int, int));                                 \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int(int()));                                    \
    TEST_UNARY_TRAIT_AGAINST_TYPE(EXPECTED, TRAIT, int(...))

#endif
