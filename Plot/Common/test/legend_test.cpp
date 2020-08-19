#include "Plot/Common/src/legend.h"

#include "gtest/gtest.h"

class LegendTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<PlottingData> plotting_data_{std::make_unique<PlottingData>()};
    Legend legend_{plotting_data_.get()};

    const std::vector<std::string> legend_labels{"This", "Labels", "Are", "Really", "Cool"};
};

TEST_F(LegendTestFixture, GivenLabelsAreNotSet_WhenCreatingLegend_ThenExceptionIsThrown) {
    ASSERT_THROW(legend_.CreateLegend(), std::invalid_argument);
}

TEST_F(LegendTestFixture, GivenLabels_WhenSettingLegendLabels_ThenCorrectLabelsAreSet) {
    const std::size_t expected_labels_size{5};

    legend_.SetLegendLabels(legend_labels);
    const auto &labels = legend_.GetLabels();

    ASSERT_EQ(labels.size(), expected_labels_size);

    for (std::size_t i{0}; i < expected_labels_size; ++i) {
        EXPECT_EQ(labels[i], legend_labels[i]);
    }
}

TEST_F(LegendTestFixture, GivenLabels_WhenCreatingLegendFrame_ThenFrameSizeIsCorrect) {
    const sf::Vector2f expected_legend_frame_size{200.f, 125.f};

    legend_.SetLegendLabels(legend_labels);
    legend_.CreateLegend();

    ASSERT_FALSE(plotting_data_->GetLegendShapes().empty());

    const auto &legend_frame_shape = plotting_data_->GetLegendShapes().front();

    EXPECT_EQ(legend_frame_shape.getSize(), expected_legend_frame_size);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
