#include "Plot/Common/src/axis.h"

#include "gtest/gtest.h"

class AxisTestFixture : protected Axis, public ::testing::Test {
};


TEST_F(AxisTestFixture, Given_When_Then) {
    Axis axis;
    axis.SetXAxisSize(10);
    axis.SetYAxisSize(5);
    axis.DrawAxis();

    SUCCEED();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
