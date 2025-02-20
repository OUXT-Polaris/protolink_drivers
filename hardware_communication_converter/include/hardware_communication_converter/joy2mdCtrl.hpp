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

#ifndef JOY2MDCTRL_HPP_
#define JOY2MDCTRL_HPP_

#include <hardware_communication_msgs/msg/motor_control.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>

namespace hardware_communication_converter
{
class Joy2MdCtrl : public rclcpp::Node
{
public:
  explicit Joy2MdCtrl(const rclcpp::NodeOptions & optinos);

private:
  rclcpp::Publisher<hardware_communication_msgs::msg::MotorControl>::SharedPtr pub_right_;
  rclcpp::Publisher<hardware_communication_msgs::msg::MotorControl>::SharedPtr pub_left_;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
};
}  // namespace hardware_communication_converter

#endif  // DEBUG
