// Copyright (c) 2025 OUXT Polaris
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "hardware_communication_converter/joy2mdCtrl.hpp"

namespace hardware_communication_converter
{
Joy2MdCtrl::Joy2MdCtrl(const rclcpp::NodeOptions & options)
: Node("joy2mdCtrl", options),
  pub_right_(create_publisher<hardware_communication_msgs::msg::MotorControl>(
    "/protolink/motor/right/command", 1)),
  pub_left_(create_publisher<hardware_communication_msgs::msg::MotorControl>(
    "/protolink/motor/left/command", 1)),
  sub_(create_subscription<sensor_msgs::msg::Joy>("joy", 1, [this](sensor_msgs::msg::Joy msg) {
    auto mc_right = std::make_unique<hardware_communication_msgs::msg::MotorControl>();
    auto mc_left = std::make_unique<hardware_communication_msgs::msg::MotorControl>();
    mc_right->motor_enable = true;
    mc_left->motor_enable = true;
    mc_right->motor_speed = msg.axes[3];
    mc_left->motor_speed = msg.axes[1];

    pub_right_->publish(std::move(mc_right));
    pub_left_->publish(std::move(mc_left));
  }))
{
}
}  // namespace hardware_communication_converter

int main(int argc, char * argv[])
{
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  try {
    const rclcpp::NodeOptions options;
    auto node = std::make_shared<hardware_communication_converter::Joy2MdCtrl>(options);
    rclcpp::spin(node);
  } catch (std::exception & e) {
    std::cout << e.what() << std::endl;
  }
  rclcpp::shutdown();
  return 0;
}
