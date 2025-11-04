#include <gtest/gtest.h>
#include "villageRNG_Interface.h"

TEST(RNGTest, GeneratesNumbersInRange) {
    auto myRNG = GetVillageRNGInterface();
    int val = myRNG->next(0, 10); // example function
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
