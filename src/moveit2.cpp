#include "moveit2/moveit2.h"
#include "gpio_chip.h"
#include "Gamepad.hpp"

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
    std::string oe_chip;
    int32_t oe_line;
    ros_node_->declare_parameter("pca_oe.chip", "");
    ros_node_->get_parameter("pca_oe.chip", oe_chip);
    ros_node_->declare_parameter("pca_oe.line", -1);
    ros_node_->get_parameter("pca_oe.line", oe_line);

    if (!oe_chip.empty() && oe_line != -1) {
        RCLCPP_INFO(ros_node_->get_logger(), "oe_chip = %s, oe_line = %d", oe_chip.c_str(), oe_line);
        gpio_ = std::make_shared<GpioChip>(oe_chip, oe_line);
        gpio_->Init();
        gpio_->SetDirection(true);
        gpio_->SetValue(false);
    }

    for(uint32_t i = 0; i < 16; i++) {
        PwmPram servo_pwm;
        servo_pwm.chip = 16;
        servo_pwm.channel = i;
        servo_pwm.polarity = true;
        servo_pwm.period = 20000000;
        servo_pwm.dutycycle = 1500000;
        std::shared_ptr<Pwm> pwm = std::make_shared<Pwm>(servo_pwm); // pwm1 20ms周期
        pwm_vec_.push_back(pwm);
    }

    ros_node_->declare_parameter("remote.type", "");
    ros_node_->get_parameter("remote.type", config_.type);

    ros_node_->declare_parameter("remote.port", "/dev/ttyUSB0");
    ros_node_->get_parameter("remote.port", config_.port);

    ros_node_->declare_parameter("remote.baudrate", 100000);
    ros_node_->get_parameter("remote.baudrate", config_.baudrate);

    ros_node_->declare_parameter("remote.data_len", 25);
    ros_node_->get_parameter("remote.data_len", config_.data_len);

    ros_node_->declare_parameter("remote.joy_var_max", 1800);
    ros_node_->get_parameter("remote.joy_var_max", config_.joy_var_max);

    ros_node_->declare_parameter("remote.joy_var_min", 200);
    ros_node_->get_parameter("remote.joy_var_min", config_.joy_var_min);

    ros_node_->declare_parameter("remote.max_x_vel", 1.0);
    ros_node_->get_parameter("remote.max_x_vel", config_.max_x_vel);

    ros_node_->declare_parameter("remote.max_w_vel", 1.0);
    ros_node_->get_parameter("remote.max_w_vel", config_.max_w_vel);

    ros_node_->declare_parameter("remote.max_angle", 1.0);
    ros_node_->get_parameter("remote.max_angle", config_.max_angle);

    std::unique_ptr<RemoteFactory> factory(new GamePadRemote());
    std::shared_ptr<RemoteProduct> gamepad(factory->CreateRemoteProduct(config_, false));
    remote_ = gamepad;

    loop_timer_ = ros_node_->create_wall_timer(
        std::chrono::milliseconds(20), std::bind(&MoveIt2::LoopCallback, this));
}

int MoveIt2::SetServo(uint32_t chanel, float angle)
{
    int32_t duty_cycle = 1500000 - (angle * 2000000 / M_PI);
    if (pwm_vec_[chanel]) {
        pwm_vec_[chanel]->PwmDutyCycle(duty_cycle);
        return 0;
    }
    return -1;
}

void MoveIt2::LoopCallback()
{
    RemoteState rc_data;
    if (remote_) {
        remote_->Request(rc_data);
    } else {
        return;
    }
    // RCLCPP_INFO(ros_node_->get_logger(), "Driver lx = %f, ly = %f, rx = %f, ry = %f",
    //                 rc_data.adslx, rc_data.adsly, rc_data.adsrx, rc_data.adsry);
    
    SetServo(0, rc_data.adsly * 90.0);
    SetServo(1, rc_data.adslx * 90.0);
    SetServo(2, rc_data.adsrx * 90.0);
    SetServo(3, rc_data.adsry * 90.0);
}
