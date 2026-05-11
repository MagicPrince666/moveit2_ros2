import os
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

from launch_ros.actions import LifecycleNode
from launch.actions import DeclareLaunchArgument
from launch.actions import LogInfo

import lifecycle_msgs.msg

def generate_launch_description():

    moveit2_cfg = os.path.join(get_package_share_directory('moveit2'), 'params', 'moveit2.yaml')

    ROS_DISTRO=''
    ROS_DISTRO = os.getenv('ROS_DISTRO')
    print("Current ROS2 Version: ",ROS_DISTRO)
    if ROS_DISTRO == 'humble' or ROS_DISTRO == 'galactic' or ROS_DISTRO == 'foxy' or ROS_DISTRO == 'iron':
        return LaunchDescription([
            Node(namespace='/', package='moveit2', executable='moveit2_node', name='moveit2_node', parameters=[moveit2_cfg], output='screen'),
            Node(package='tf2_ros', executable='static_transform_publisher', arguments=['0', '0', '0.02','0', '0', '0', '1','base_link','imu_link']),
        ])
    else:
        return LaunchDescription([
            Node(node_namespace='/', package='moveit2', node_executable='moveit2_node', node_name='moveit2_node', parameters=[moveit2_cfg], output='screen'),
            Node(package='tf2_ros', node_executable='static_transform_publisher', arguments=['0', '0', '0.02','0', '0', '0', '1','base_link','imu_link']),
        ])
