//
// Created by paul on 02/01/18.
//

//
// Created by paul on 28/11/15.
//

// #include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char **argv) {

    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    // ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}