#include <new>

#include "testing/test.h"

void Testing::run() {
    // This example is taken from the C++ standard, section 17.6.4, paragraph 6.
    struct X {
        int n;
    };

    const X* p = new const X{3};
    [[maybe_unused]] const int a = p->n;
    // p does not point to new object ([basic.life]) because its type is const
    new (const_cast<X*>(p)) const X{5};
    //    const int b = p->n; // undefined behavior
    [[maybe_unused]] const int c = std::launder(p)->n;  // OK
    delete std::launder(p);
}
