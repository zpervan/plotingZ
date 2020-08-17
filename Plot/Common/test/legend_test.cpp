#include "Plot/Common/src/legend.h"

#include "gtest/gtest.h"

class LegendTestFixture : public Legend, public ::testing::Test {

};

TEST_F(LegendTestFixture, GivenLegendLabels_WhenSetting_ThenCorrectLabelsAreSet) {
    const std::size_t expected_labels_size{5};
    const std::vector<std::string> legend_labels{"This", "Labels", "Are", "Really", "Cool"};

    SetLegendLabels(legend_labels);

    ASSERT_EQ(labels_.size(), expected_labels_size);

    for (std::size_t i{0}; i < expected_labels_size; ++i) {
        EXPECT_EQ(labels_[i], legend_labels[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
