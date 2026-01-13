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

#include <protolink_drivers/gps_driver_component.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace protolink_drivers
{
GpsDriverComponent::GpsDriverComponent(const rclcpp::NodeOptions & options)
: Node("gps_driver_component", options),
  params_(gps_driver::ParamListener(get_node_parameters_interface()).get_params()),
  publisher_(create_publisher<geographic_msgs::msg::GeoPose>("geopose", 1))
{
  int port = params_.port;

  try {
    sock_ = protolink::udp_protocol::create_socket(io_context_, port);
    RCLCPP_INFO(this->get_logger(), "UDP open port: %d", port);
  } catch (const std::exception & e) {
    RCLCPP_ERROR(this->get_logger(), "Failed to initialize udp publisher: %s", e.what());
    RCLCPP_ERROR(this->get_logger(), "UDP don't open port %d", port);
    exit(1);
  }

  subscriber_ = std::make_shared<protolink::udp_protocol::Subscriber<
    protolink__geographic_msgs__GeoPose::geographic_msgs__GeoPose>>(
    sock_, [this](const auto & msg) {
      publisher_->publish(protolink__geographic_msgs__GeoPose::convert(msg));
    });
}
}  // namespace protolink_drivers

RCLCPP_COMPONENTS_REGISTER_NODE(protolink_drivers::GpsDriverComponent)
