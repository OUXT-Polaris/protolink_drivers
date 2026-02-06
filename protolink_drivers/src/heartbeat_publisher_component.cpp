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
    hardware_communication_msgs::build<hardware_communication_msgs::msg::GroundStationHeartBeat>().sequence(1)),
  params_(heartbeat_publisher::ParamListener(get_node_parameters_interface()).get_params()),
  sock_(protolink::udp_protocol::create_socket(io_context_, params_.from_port)),
  protolink_publisher_(sock_, params_.ip_address, params_.port, this->get_logger()),
  publish_timer_(
    create_wall_timer(std::chrono::duration<double>(1.0 / params_.publish_rate), [&]() {
      protolink_publisher_.send(protolink__hardware_communication_msgs__GroundStationHeartBeat::convert(data_));
      data_.sequence = data_.sequence + 1;
    }))
{
  rcin_sub = this->create_subscription<mavros_msgs::msg::RCIn>(
  "/mavros/rc/in", 10, std::bind(&HeartBeatPublisherComponent::rcInCallback, this, std::placeholders::_1));
}
// namespace protolink_drivers

void HeartBeatPublisherComponent::rcInCallback(const mavros_msgs::msg::RCIn::SharedPtr msg)
{
  // 例: プロポの 6ch (インデックスは 5) に割り当てたスイッチで mode を変更
  // channelsのサイズチェック（念のため）
  if (msg->channels.size() < 6) return;

  uint16_t sw_value = msg->channels[4]; // 6chの値を取得

  if (sw_value < 1300) {
    data_.mode = 1; // スイッチが下のとき
  } else if (sw_value > 1700) {
    data_.mode = 0; // スイッチが上のときsource /opt/ros/humble/setup.bash
  } else {
    data_.mode = 3; // スイッチが真ん中のとき（3ポジションスイッチの場合）
  }
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(protolink_drivers::HeartBeatPublisherComponent)
