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

#ifndef PROTOLINK_DRIVERS__MOTOR_CONTROL_COMPONENT_HPP_
#define PROTOLINK_DRIVERS__MOTOR_CONTROL_COMPONENT_HPP_

#include <protolink_drivers/visibility_control.h>

#include <conversion_hardware_communication_msgs__MotorControl.hpp>
#include <rclcpp/rclcpp.hpp>

namespace protolink_drivers
{
class MotorControlComponent : public rclcpp::Node
{
public:
  PROTOLINK_DRIVERS_PUBLIC
  explicit MotorControlComponent(const rclcpp::NodeOptions & options);
};
}  // namespace protolink_drivers

#endif  // PROTOLINK_DRIVERS__MOTOR_CONTROL_COMPONENT_HPP_