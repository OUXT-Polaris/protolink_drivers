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

#include <protolink_drivers/imu_driver_component.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace protolink_drivers
{
ImuDriverComponent::ImuDriverComponent(const rclcpp::NodeOptions & options)
: Node("imu_driver_component", options),
  params_(imu_driver::ParamListener(get_node_parameters_interface()).get_params()),
  publisher_(create_publisher<hardware_communication_msgs::msg::SimpleImu>("imu", 1)),
  subscriber_(io_, params_.port, [this](const auto & msg) { publisher_->publish(convert(msg)); })
{
}
}  // namespace protolink_drivers

RCLCPP_COMPONENTS_REGISTER_NODE(protolink_drivers::ImuDriverComponent)
