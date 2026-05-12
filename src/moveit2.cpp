#include "moveit2/moveit2.h"
#include "gpio_chip.h"

MoveIt2::MoveIt2(std::shared_ptr<rclcpp::Node> node) : ros_node_(node)
{
    RCLCPP_INFO(ros_node_->get_logger(), "MoveIt2 node has been started.");
    // Initialize MoveIt! components here
}

MoveIt2::~MoveIt2()
{
}

void MoveIt2::Init()
{
    gpio_ = std::make_shared<GpioChip>("/dev/gpiochip4", 7);
    gpio_->Init();
    gpio_->SetDirection(true);
    gpio_->SetValue(false);

    for(uint32_t i = 0; i < 16; i++) {
        PwmPram servo_pwm;
        servo_pwm.chip = 16;
        servo_pwm.channel = i;
        servo_pwm.polarity = true;
        servo_pwm.period = 20000000;
        servo_pwm.dutycycle = 20000000 - 1500000;
        std::shared_ptr<Pwm> pwm = std::make_shared<Pwm>(servo_pwm); // pwm1 20ms周期
        pwm_vec_.push_back(pwm);
    }
}

int MoveIt2::SetServo(uint32_t chanel, float angle)
{
    int32_t duty_cycle = 20000000 - (1500000 - (angle * 2000000 / M_PI));
    if (pwm_vec_[chanel]) {
        pwm_vec_[chanel]->PwmDutyCycle(duty_cycle);
    }
    return 0;
}
