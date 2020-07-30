#include "../src/line_plot.h"

#include "gtest/gtest.h"

TEST(LinePlotTest, GivenLinePlotObject_WhenCreating_ThenSuccessfullyCreated) {
    LinePlot *line_plot = new LinePlot();

    ASSERT_TRUE(line_plot);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
