#include "placeholder.hpp"

#include <gtest/gtest.h>

TEST(PlaceholderTest, SetsNumbers)
{
    Placeholder p;
    EXPECT_EQ(p.a, 2);
    EXPECT_EQ(p.b, 21);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
