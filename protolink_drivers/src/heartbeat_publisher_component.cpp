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

#include <protolink_drivers/heartbeat_publisher_component.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace protolink_drivers
{
HeartBeatPublisherComponent::HeartBeatPublisherComponent(const rclcpp::NodeOptions & options)
: Node("heartbeat_publisher_component", options),
  data_(
    hardware_communication_msgs::build<hardware_communication_msgs::msg::HeartBeat>().sequence(1)),
  params_(heartbeat_publisher::ParamListener(get_node_parameters_interface()).get_params()),
  protolink_publisher_(io_, params_.ip_address, params_.port, params_.from_port),
  publish_timer_(
    create_wall_timer(std::chrono::duration<double>(1.0 / params_.publish_rate), [&]() {
      protolink_publisher_.send(convert(data_));
      data_.sequence = data_.sequence + 1;
    }))
{
}
}  // namespace protolink_drivers

RCLCPP_COMPONENTS_REGISTER_NODE(protolink_drivers::HeartBeatPublisherComponent)
