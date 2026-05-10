#include "moveit2/moveit2.h"

MoveIt2::MoveIt2(std::shared_ptr<rclcpp::Node> node) : ros_node_(node)
{
    RCLCPP_INFO(ros_node_->get_logger(), "MoveIt2 node has been started.");
    // Initialize MoveIt! components here
}

MoveIt2::~MoveIt2()
{
}
