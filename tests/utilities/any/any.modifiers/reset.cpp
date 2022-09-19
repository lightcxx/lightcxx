#include <any>

#include "counted_type.h"
#include "testing.h"

TEST(reset) {
    cnttype::reset();
    {
        std::any val(std::in_place_type<cnttype>);
        {
            std::any val_cpy(val);
            expect(cnttype::dtor_count == 0);
            val_cpy.reset();
            expect(cnttype::dtor_count == 1);
        }
        expect(cnttype::dtor_count == 1);
        {
            std::any val_mv(std::move(val));
            expect(cnttype::dtor_count == 1);
            val_mv.reset();
            expect(cnttype::dtor_count == 2);
        }
        expect(cnttype::dtor_count == 2);
    }
    expect(cnttype::dtor_count == 2);  // deleted moved-from instance
}
