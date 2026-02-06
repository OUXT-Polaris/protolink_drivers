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

#ifndef PROTOLINK_DRIVERS__HEARTBEAT_PUBLISHER_GroundStationCOMPONENT_HPP_
#define PROTOLINK_DRIVERS__HEARTBEAT_PUBLISHER_COMPONENT_HPP_

#include <protolink_drivers/visibility_control.h>

#include <proto_files/conversion_hardware_communication_msgs__GroundStationHeartBeat.hpp>
#include <protolink/client.hpp>
#include <protolink_drivers/heartbeat_publisher_parameters.hpp>
#include <rclcpp/rclcpp.hpp>
#include <hardware_communication_msgs/msg/ground_station_heart_beat.hpp>
#include <mavros_msgs/msg/rc_in.hpp>

namespace protolink_drivers
{
class HeartBeatPublisherComponent : public rclcpp::Node
{
public:
  PROTOLINK_DRIVERS_PUBLIC
  explicit HeartBeatPublisherComponent(const rclcpp::NodeOptions & options);

private:
  hardware_communication_msgs::msg::GroundStationHeartBeat data;
  
  rclcpp::Subscription<mavros_msgs::msg::RCIn>::SharedPtr rcin_sub;
  
  void rcInCallback(const mavros_msgs::msg::RCIn::SharedPtr msg);

private:
  hardware_communication_msgs::msg::GroundStationHeartBeat data_;
  const heartbeat_publisher::Params params_;
  protolink::IoContext io_context_;
  std::shared_ptr<protolink::udp_protocol::soket> sock_;
  protolink::udp_protocol::Publisher<
    protolink__hardware_communication_msgs__GroundStationHeartBeat::hardware_communication_msgs__GroundStationHeartBeat>
    protolink_publisher_;
  const rclcpp::TimerBase::SharedPtr publish_timer_;
};
}  // namespace protolink_drivers

#endif  // PROTOLINK_DRIVERS__HEARTBEAT_PUBLISHER_COMPONENT_HPP_
