#ifndef __MOVEIT2_H__
#define __MOVEIT2_H__

#include <memory>
#include <rclcpp/rclcpp.hpp>

class MoveIt2
{
public:
    MoveIt2(std::shared_ptr<rclcpp::Node> node);
    ~MoveIt2();
private:
    std::shared_ptr<rclcpp::Node> ros_node_;
};

#endif
