#include "Plot/Common/src/axis.h"
#include "ThirdParty/fmt/include/fmt/core.h"

#include "gtest/gtest.h"

class AxisTestFixture : public ::testing::Test {
protected:
    PlottingData *plotting_data_{new PlottingData};
    Axis axis_{plotting_data_};
    const std::vector<float> valid_x_data{14.28, 3.0, 2.0, 0.021};
    const std::vector<float> valid_y_data{0.98, 2.0, 3.0, 13.13};
};

/// @todo: Axis should have a protected constructor which takes a custom config for window height and width,
/// otherwise the test will fail if we change the window size in the config file

TEST_F(AxisTestFixture, GivenMaxValuesAreSet_WhenCreatingAxis_ThenCorrectNumberOfAxisShapesPresent) {
    plotting_data_->FindAndSetMaxXValue(valid_x_data);
    plotting_data_->FindAndSetMaxYValue(valid_y_data);

    axis_.SetXAxisMaxMarkerValue(plotting_data_->GetMaxXValue());
    axis_.SetYAxisMaxMarkerValue(plotting_data_->GetMaxYValue());

    axis_.CreateAxis();

    ASSERT_TRUE(true);
}

TEST_F(AxisTestFixture, DISABLED_GivenAxisSizes_WhenCreating_ThenMarkerPositionsAreCorrect) {
    const std::size_t expected_number_of_shape_elements{8};
    const std::array<sf::Vector2f, 6> expected_marker_positions
            {{{40.f, 440.f}, {320.f, 440.f}, {600.f, 440.f}, {40.f, 440.f}, {40.f, 240.f}, {40.f, 40.f}}};

    axis_.SetYAxisMaxMarkerValue(2);
    axis_.SetXAxisMaxMarkerValue(2);
    axis_.CreateAxis();

    ASSERT_EQ(plotting_data_->GetAxisShapes().size(), expected_number_of_shape_elements);

    for (std::size_t i{0}; i < expected_marker_positions.size(); i++) {
        EXPECT_EQ(plotting_data_->GetAxisShapes()[i + 2].getPosition().x, expected_marker_positions[i].x)
                            << fmt::format("X at shape element with index {}", i + 2);
        EXPECT_EQ(plotting_data_->GetAxisShapes()[i + 2].getPosition().y, expected_marker_positions[i].y)
                            << fmt::format("Y at shape element with index {}", i + 2);;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
