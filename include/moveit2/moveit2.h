#ifndef __MOVEIT2_H__
#define __MOVEIT2_H__

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include "gpio.h"
#include "pwm.h"
#include "RemoteFactory.h"

class MoveIt2
{
public:
    MoveIt2(std::shared_ptr<rclcpp::Node> node);
    ~MoveIt2();

    void Init();

    int SetServo(uint32_t chanel, float angle);

private:
    std::shared_ptr<rclcpp::Node> ros_node_;
    std::shared_ptr<Gpio> gpio_;
    std::vector<std::shared_ptr<Pwm>> pwm_vec_;
    std::shared_ptr<RemoteProduct> remote_;
    RemoteConfig_t config_;
    rclcpp::TimerBase::SharedPtr loop_timer_;

    void LoopCallback();
};

#endif
