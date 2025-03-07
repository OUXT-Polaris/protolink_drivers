cmake_minimum_required(VERSION 3.8)
project(protolink_drivers)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

include(FindProtobuf REQUIRED)

add_protolink_message_from_ros_message("hardware_communication_msgs" "MotorControl")
add_protolink_message_from_ros_message("hardware_communication_msgs" "HeartBeat")
add_protolink_message_from_ros_message("hardware_communication_msgs" "SimpleImu")
add_protolink_message_from_ros_message("geographic_msgs" "GeoPose")

generate_parameter_library(
  motor_control_parameters
  params/motor_control.yaml
)

generate_parameter_library(
  heartbeat_publisher_parameters
  params/heartbeat_publisher.yaml
)

generate_parameter_library(
  gps_driver_parameters
  params/gps_driver.yaml
)

generate_parameter_library(
  imu_driver_parameters
  params/imu_driver.yaml
)

ament_auto_add_library(protolink_drivers SHARED
  src/gps_driver_component.cpp
  src/imu_driver_component.cpp
  src/heartbeat_publisher_component.cpp
  src/motor_control_component.cpp
)
target_link_libraries(protolink_drivers
  motor_control_parameters
  heartbeat_publisher_parameters
  gps_driver_parameters
  imu_driver_parameters
  hardware_communication_msgs__MotorControl_proto
  hardware_communication_msgs__HeartBeat_proto
  geographic_msgs__GeoPose_proto
  ${PROTOBUF_LIBRARY})

rclcpp_components_register_nodes(protolink_drivers
  "protolink_drivers::MotorControlComponent")

rclcpp_components_register_nodes(protolink_drivers
  "protolink_drivers::HeartBeatPublisherComponent")

rclcpp_components_register_nodes(protolink_drivers
  "protolink_drivers::GpsDriverComponent")

rclcpp_components_register_nodes(protolink_drivers
  "protolink_drivers::ImuDriverComponent")

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()
