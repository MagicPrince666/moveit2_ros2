#!/bin/bash

# 循环初始化16通道PWM (0-15)
for i in {0..15}; do
    echo $i > /sys/class/pwm/pwmchip16/export
    echo 20000000 > /sys/class/pwm/pwmchip16/pwm$i/period
    echo 1500000 > /sys/class/pwm/pwmchip16/pwm$i/duty_cycle
    echo invert > /sys/class/pwm/pwmchip16/pwm$i/polarity
    echo 1 > /sys/class/pwm/pwmchip16/pwm$i/enable
    # 设置权限
    chmod 666 /sys/class/pwm/pwmchip16/pwm$i/period
    chmod 666 /sys/class/pwm/pwmchip16/pwm$i/duty_cycle
    chmod 666 /sys/class/pwm/pwmchip16/pwm$i/polarity
    chmod 666 /sys/class/pwm/pwmchip16/pwm$i/enable
done
