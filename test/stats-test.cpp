#include "../src/stats.h"

#include "gtest/gtest.h"
#include <math.h>

// Test case to calculate average with normal values 
TEST(Statistics, ReportsAverageMinMax) {
    float values[] = {1.5, 8.9, 3.2, 4.5};
    auto computedStats = compute_statistics(values, 4);
    float epsilon = 0.001;
    EXPECT_LT(fabsf(computedStats.average - 4.525), epsilon);
    EXPECT_LT(fabsf(computedStats.max - 8.9), epsilon);
    EXPECT_LT(fabsf(computedStats.min - 1.5), epsilon);
}

//Test case to ignore one invalid value
TEST(Statistics, AverageIgnoreNaN) {
    float values[] = {1.5, 8.9, 4.5, NAN};
    auto computedStats = compute_statistics(values, 3);
    float epsilon = 0.001;
    EXPECT_LT(fabsf(computedStats.average - 4.967), epsilon);
    EXPECT_LT(fabsf(computedStats.max - 8.9), epsilon);
    EXPECT_LT(fabsf(computedStats.min - 1.5), epsilon);
}

//Test case to check whether all values are invalid
TEST(Statistics, AverageNaNForAllNaN) {
    float values[] = {NAN, NAN, NAN};
    auto computedStats = compute_statistics(values, 3);
    EXPECT_TRUE(isnan(computedStats.average));
    EXPECT_TRUE(isnan(computedStats.max));
    EXPECT_TRUE(isnan(computedStats.min));
}

//Test case to check Absurd value >100000
TEST(Statistics, AbsurdHighValue) {
    float values[] = { 500000.0f, 1.5, 3.2};
    auto computedStats = compute_statistics(values, 3);
    EXPECT_TRUE(isnan(computedStats.average));
    EXPECT_TRUE(isnan(computedStats.max));
    EXPECT_TRUE(isnan(computedStats.min));
}

//Test case to check invalid pointer
TEST(Statistics, NullPointer) {
    auto computedStats = compute_statistics(nullptr, 3);
    EXPECT_TRUE(isnan(computedStats.average));
    EXPECT_TRUE(isnan(computedStats.max));
    EXPECT_TRUE(isnan(computedStats.min));
}
