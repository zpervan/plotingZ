#include "Plot/Common/src/axis.h"
#include "ThirdParty/fmt/include/fmt/core.h"

#include "gtest/gtest.h"

class AxisTestFixture : public Axis, public ::testing::Test {
};

/// @todo: Axis should have a protected constructor which takes a custom config for window height and width,
/// otherwise the test will fail if we change the window size in the config file

TEST_F(AxisTestFixture, GivenAxisSizes_WhenCreating_ThenCorrectNumberOfAxisShapesPresent) {
    // For X and Y axis, it's drawing one extra marker so instead od 72, there are 74
    const std::size_t expected_number_of_shape_elements{74};

    SetXAxis(23);
    SetYAxis(47);
    CreateAxis();

    ASSERT_EQ(GetAxisShapes().size(), expected_number_of_shape_elements);
}

TEST_F(AxisTestFixture, GivenAxisSizes_WhenCreating_ThenMarkerPositionsAreCorrect) {
    const std::size_t expected_number_of_shape_elements{8};
    const std::array<sf::Vector2f, 6> expected_marker_positions
            {{{40.f, 440.f}, {320.f, 440.f}, {600.f, 440.f}, {40.f, 440.f}, {40.f, 240.f}, {40.f, 40.f}}};

    SetYAxis(2);
    SetXAxis(2);
    CreateAxis();

    ASSERT_EQ(GetAxisShapes().size(), expected_number_of_shape_elements);

    for (std::size_t i{0}; i < expected_marker_positions.size(); i++) {
        EXPECT_EQ(GetAxisShapes()[i + 2].getPosition().x, expected_marker_positions[i].x)
                            << fmt::format("X at shape element with index {}", i + 2);
        EXPECT_EQ(GetAxisShapes()[i + 2].getPosition().y, expected_marker_positions[i].y)
                            << fmt::format("Y at shape element with index {}", i + 2);;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
