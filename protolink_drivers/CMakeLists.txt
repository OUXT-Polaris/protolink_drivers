cmake_minimum_required(VERSION 3.8)
project(protolink_drivers)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

add_protolink_message_from_ros_message("hardware_communication_msgs" "MotorControl")

ament_auto_add_library(protolink_drivers SHARED
  src/motor_control_component.cpp
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()
