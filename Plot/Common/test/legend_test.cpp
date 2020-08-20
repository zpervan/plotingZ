#include "Plot/Common/src/legend.h"

#include "gtest/gtest.h"
#include "ThirdParty/fmt/include/fmt/core.h"

class LegendTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<PlottingData> plotting_data_{std::make_unique<PlottingData>()};
    Legend legend_{plotting_data_.get()};

    const std::vector<std::string> legend_labels{"This", "Labels", "Are", "Really", "Cool"};
    const float precision{1e-2};
};

TEST_F(LegendTestFixture, GivenLabelsAreNotSet_WhenCreatingLegend_ThenExceptionIsThrown) {
    ASSERT_THROW(legend_.CreateLegend(), std::invalid_argument);
}

TEST_F(LegendTestFixture, GivenInputDataLabels_WhenSettingLegendLabels_ThenCorrectLabelsAreSet) {
    const std::size_t expected_labels_size{5};

    legend_.SetLegendLabels(legend_labels);
    const auto &labels = legend_.GetLabels();

    ASSERT_EQ(labels.size(), expected_labels_size);

    for (std::size_t i{0}; i < expected_labels_size; ++i) {
        EXPECT_EQ(labels[i], legend_labels[i]);
    }
}

TEST_F(LegendTestFixture, GivenInputDataLabels_WhenCreatingLegendFrame_ThenFrameSizeIsCorrect) {
    const sf::Vector2f expected_legend_frame_size{200.0f, 90.0f};

    legend_.SetLegendLabels(legend_labels);
    legend_.CreateLegend();

    ASSERT_FALSE(plotting_data_->GetLegendShapes().empty());

    const auto &legend_frame_shape = plotting_data_->GetLegendShapes().front();

    EXPECT_EQ(legend_frame_shape.getSize().x, expected_legend_frame_size.x);
    EXPECT_EQ(legend_frame_shape.getSize().y, expected_legend_frame_size.y);
}

TEST_F(LegendTestFixture, GivenInputDataLabels_WhenCreatingLabelText_ThenCorrectLabelTextPosition) {
    const std::array<sf::Vector2f, 5> expected_label_text_positions{{{436.0, 24.0},
                                                                            {436.0, 41.5},
                                                                            {436.0, 59.0},
                                                                            {436.0, 76.5},
                                                                            {436.0, 94.0}}};
    legend_.SetLegendLabels(legend_labels);
    legend_.CreateLegend();

    const auto &legend_label_texts = plotting_data_->GetLegendLabelTexts();

    ASSERT_FALSE(legend_label_texts.empty());

    for (std::size_t i{0}; i < legend_label_texts.size(); i++) {
        EXPECT_EQ(legend_label_texts.at(i).getPosition().x, expected_label_text_positions.at(i).x);
        EXPECT_EQ(legend_label_texts.at(i).getPosition().y, expected_label_text_positions.at(i).y);
    }
}

TEST_F(LegendTestFixture, GivenInputDataLabels_WhenCreatingLabelBoxes_ThenCorrectLabelBoxPosition) {
    const std::array<sf::Vector2f, 5> expected_label_box_positions{{{421.0, 25.92},
                                                                           {421.0, 43.42},
                                                                           {421.0, 60.92},
                                                                           {421.0, 78.42},
                                                                           {421.0, 95.92}}};
    legend_.SetLegendLabels(legend_labels);
    legend_.CreateLegend();

    auto legend_shapes = plotting_data_->GetLegendShapes();
    // Remove legend frame shape as this is not tested
    legend_shapes.erase(legend_shapes.begin() + 0);

    ASSERT_FALSE(legend_shapes.empty());

    for (std::size_t i{0}; i < legend_shapes.size(); i++) {
        EXPECT_NEAR(legend_shapes.at(i).getPosition().x, expected_label_box_positions.at(i).x, precision);
        EXPECT_NEAR(legend_shapes.at(i).getPosition().y, expected_label_box_positions.at(i).y, precision);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
