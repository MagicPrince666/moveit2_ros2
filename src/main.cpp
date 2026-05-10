#include <rclcpp/rclcpp.hpp>
#include "moveit2/moveit2.h"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("imu901m");
    std::unique_ptr<MoveIt2> moveit2(new MoveIt2(node));
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
