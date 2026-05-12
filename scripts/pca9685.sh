#!/bin/bash

# 循环初始化16通道PWM (0-15)
for i in {0..15}; do
    # 如果已导出则跳过重复导出
    if [ ! -d "/sys/class/pwm/pwmchip16/pwm$i" ]; then
        echo $i > /sys/class/pwm/pwmchip16/export
    fi

    # echo normal > /sys/class/pwm/pwmchip16/pwm$i/polarity
    # echo 20000000 > /sys/class/pwm/pwmchip16/pwm$i/period
    # echo 1500000 > /sys/class/pwm/pwmchip16/pwm$i/duty_cycle
    # echo 1 > /sys/class/pwm/pwmchip16/pwm$i/enable
    # 设置权限
    chmod 666 /sys/class/pwm/pwmchip16/pwm$i/period
    chmod 666 /sys/class/pwm/pwmchip16/pwm$i/duty_cycle
    chmod 666 /sys/class/pwm/pwmchip16/pwm$i/polarity
    chmod 666 /sys/class/pwm/pwmchip16/pwm$i/enable
done
