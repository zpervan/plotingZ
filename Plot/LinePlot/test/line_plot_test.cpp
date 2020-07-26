#include "../src/line_plot.h"

#include "gtest/gtest.h"

class LinePlotTestFixture : public LinePlot, public ::testing::Test {
protected:
    LinePlot line_plot_;
};

TEST(LinePlotTest, GivenLinePlotObject_WhenCreating_ThenSuccessfullyCreated) {
    LinePlot *line_plot = new LinePlot();

    ASSERT_TRUE(line_plot);
}

TEST_F(LinePlotTestFixture, Given_When_Then) {
    FAIL();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
