#include <any>

#include "counted_type.h"
#include "testing.h"

TEST(reset) {
    cnttype::reset();
    {
        std::any val(std::in_place_type<cnttype>);
        {
            std::any val_cpy(val);
            ASSERT(cnttype::dtor_count == 0);
            val_cpy.reset();
            ASSERT(cnttype::dtor_count == 1);
        }
        ASSERT(cnttype::dtor_count == 1);
        {
            std::any val_mv(std::move(val));
            ASSERT(cnttype::dtor_count == 1);
            val_mv.reset();
            ASSERT(cnttype::dtor_count == 2);
        }
        ASSERT(cnttype::dtor_count == 2);
    }
    ASSERT(cnttype::dtor_count == 2);  // deleted moved-from instance
}
