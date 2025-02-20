import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        [
            Node(
                package="joy",
                namespace="comm_converter",
                executable="joy_node",
                output="screen",
            ),
            Node(
                package="hardware_communication_converter",
                namespace="comm_converter",
                executable="joy2mdCtrl",
                output="screen",
            ),
        ]
    )
