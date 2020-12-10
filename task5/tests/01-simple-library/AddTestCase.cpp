//
// Created by akhtyamovpavel on 5/1/20.
//

#include "AddTestCase.h"
#include "Functions.h"

TEST_F(AddTestCase, SimpleAddTestCase) {
    ASSERT_EQ(4, Add(2, 2));
}
