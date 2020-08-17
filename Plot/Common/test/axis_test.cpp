#include "Plot/Common/src/axis.h"
#include "ThirdParty/fmt/include/fmt/core.h"

#include "gtest/gtest.h"

class AxisTestFixture : public ::testing::Test {
protected:
    PlottingData plotting_data_{};
    Axis axis_{plotting_data_};
};

/// @todo: Axis should have a protected constructor which takes a custom config for window height and width,
/// otherwise the test will fail if we change the window size in the config file

TEST_F(AxisTestFixture, GivenAxisSizes_WhenCreating_ThenCorrectNumberOfAxisShapesPresent) {
    // For X and Y axis, it's drawing one extra marker so instead od 72, there are 74
    const std::size_t expected_number_of_shape_elements{74};

    axis_.SetXAxis(23);
    axis_.SetYAxis(47);
    axis_.CreateAxis();

    ASSERT_EQ(plotting_data_.GetAxisShapes().size(), expected_number_of_shape_elements);
}

TEST_F(AxisTestFixture, GivenAxisSizes_WhenCreating_ThenMarkerPositionsAreCorrect) {
    const std::size_t expected_number_of_shape_elements{8};
    const std::array<sf::Vector2f, 6> expected_marker_positions
            {{{40.f, 440.f}, {320.f, 440.f}, {600.f, 440.f}, {40.f, 440.f}, {40.f, 240.f}, {40.f, 40.f}}};

    axis_.SetYAxis(2);
    axis_.SetXAxis(2);
    axis_.CreateAxis();

    ASSERT_EQ(plotting_data_.GetAxisShapes().size(), expected_number_of_shape_elements);

    for (std::size_t i{0}; i < expected_marker_positions.size(); i++) {
        EXPECT_EQ(plotting_data_.GetAxisShapes()[i + 2].getPosition().x, expected_marker_positions[i].x)
                            << fmt::format("X at shape element with index {}", i + 2);
        EXPECT_EQ(plotting_data_.GetAxisShapes()[i + 2].getPosition().y, expected_marker_positions[i].y)
                            << fmt::format("Y at shape element with index {}", i + 2);;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
