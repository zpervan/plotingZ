#include "Plot/Common/src/legend.h"

#include "ThirdParty/fmt/include/fmt/core.h"
#include "gtest/gtest.h"

#include <array>

class LegendTestFixture : public ::testing::Test {
protected:
  const std::vector<std::string> legend_labels{"This", "Labels", "Are", "Really", "Cool"};
  const float precision{1e-2};
};

TEST_F(LegendTestFixture, GivenLabelsAreNotSet_WhenCreatingLegend_ThenExceptionIsThrown) {
  Legend legend;
  ASSERT_THROW(legend.CreateLegend(), std::invalid_argument);
}

TEST_F(LegendTestFixture, GivenInputDataLabels_WhenSettingLegendLabels_ThenCorrectLabelsAreSet) {
  constexpr std::size_t expected_labels_size{5};

  Legend legend;
  legend.SetLegendLabels(legend_labels);

  const auto &labels = legend.GetLabels();

  ASSERT_EQ(labels.size(), expected_labels_size);

  for (std::size_t i{0}; i < expected_labels_size; ++i) {
    EXPECT_EQ(labels[i], legend_labels[i]);
  }
}

TEST_F(LegendTestFixture,
       GivenInputDataLabels_WhenCreatingLegendFrame_ThenFramePositionAndDimensionAreCorrect) {
  const sf::Vector2f expected_legend_frame_dimension{54.13, 90.0};
  const sf::Vector2f expected_legend_frame_position{575.86, 14.0};

  PlottingData plotting_data;
  Legend legend{&plotting_data};
  legend.SetLegendLabels(legend_labels);
  legend.CreateLegend();

  ASSERT_FALSE(plotting_data.GetLegendShapes().empty());

  const auto &legend_frame_shape = plotting_data.GetLegendShapes().front();

  EXPECT_NEAR(legend_frame_shape.getSize().x, expected_legend_frame_dimension.x, precision);
  EXPECT_NEAR(legend_frame_shape.getSize().y, expected_legend_frame_dimension.y, precision);
  EXPECT_NEAR(legend_frame_shape.getPosition().x, expected_legend_frame_position.x, precision);
  EXPECT_NEAR(legend_frame_shape.getPosition().y, expected_legend_frame_position.y, precision);
}

TEST_F(LegendTestFixture, GivenInputDataLabels_WhenCreatingLabelText_ThenCorrectLabelTextPosition) {
  const std::array<sf::Vector2f, 5> expected_label_text_positions{
      {{589.86, 14.0}, {589.86, 32.0}, {589.86, 50.0}, {589.86, 68.0}, {589.86, 86.0}}};

  PlottingData plotting_data;
  Legend legend{&plotting_data};
  legend.SetLegendLabels(legend_labels);
  legend.CreateLegend();

  const auto &legend_label_texts = plotting_data.GetLegendLabelTexts();

  ASSERT_FALSE(legend_label_texts.empty());

  for (std::size_t i{0}; i < legend_label_texts.size(); i++) {
    EXPECT_NEAR(legend_label_texts.at(i).getPosition().x, expected_label_text_positions.at(i).x, precision);
    EXPECT_NEAR(legend_label_texts.at(i).getPosition().y, expected_label_text_positions.at(i).y, precision);
  }
}

TEST_F(LegendTestFixture, GivenInputDataLabels_WhenCreatingLabelBoxes_ThenCorrectLabelBoxPosition) {
  const std::array<sf::Vector2f, 5> expected_label_box_positions{
      {{576.86, 16.5}, {576.86, 34.5}, {576.86, 52.5}, {576.86, 70.5}, {576.86, 88.5}}};

  PlottingData plotting_data;
  Legend legend{&plotting_data};
  legend.SetLegendLabels(legend_labels);
  legend.CreateLegend();

  auto legend_shapes = plotting_data.GetLegendShapes();
  // Remove legend frame shape as this is not tested
  legend_shapes.erase(legend_shapes.begin());

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
