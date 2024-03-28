
#include "PublisherTest.h"
#include "rclcpp/rclcpp.hpp"
//#include "rosa/publisher/Publisher.h"

#include "gtest/gtest.h"


TEST(PublisherTest, publishmessage)
{
    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
