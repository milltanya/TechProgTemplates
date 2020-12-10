//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"

#include <Functions.h>

TEST_F(LeapTestCase, InvalidYear) {
    ASSERT_THROW(IsLeap(0), std::invalid_argument);
}

TEST_F(LeapTestCase, SimpleNotLeap) {
    ASSERT_FALSE(IsLeap(2017));
}

TEST_F(LeapTestCase, SimpleLeap) {
    ASSERT_TRUE(IsLeap(2016));
}

TEST_F(LeapTestCase, MultipleOf100) {
    ASSERT_FALSE(IsLeap(2100));
}

TEST_F(LeapTestCase, MultipleOf400) {
    ASSERT_TRUE(IsLeap(2400));
}
