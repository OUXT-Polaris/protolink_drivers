#ifndef PROTOLINK_DRIVERS__RC_TO_MOTOR_CONTROL_HPP_
#define PROTOLINK_DRIVERS__RC_TO_MOTOR_CONTROL_HPP_

#include <protolink_drivers/visibility_control.h>

#include <rclcpp/rclcpp.hpp>
#include <mavros_msgs/msg/rc_out.hpp>
#include <hardware_communication_msgs/msg/motor_control.hpp>

namespace protolink_drivers
{

class RcToMotorControl : public rclcpp::Node
{
public:
  PROTOLINK_DRIVERS_PUBLIC
  explicit RcToMotorControl(const rclcpp::NodeOptions & options);

private:
  // サブスクライバ (MAVROS)
  rclcpp::Subscription<mavros_msgs::msg::RCOut>::SharedPtr sub_rc_;

  // パブリッシャ (Manual系統 -> 8888用)
  rclcpp::Publisher<hardware_communication_msgs::msg::MotorControl>::SharedPtr pub_man_left_;
  rclcpp::Publisher<hardware_communication_msgs::msg::MotorControl>::SharedPtr pub_man_right_;

  // パブリッシャ (Auto系統 -> 8889用)
  rclcpp::Publisher<hardware_communication_msgs::msg::MotorControl>::SharedPtr pub_auto_left_;
  rclcpp::Publisher<hardware_communication_msgs::msg::MotorControl>::SharedPtr pub_auto_right_;

  // パラメータ変数
  int ch_switch_;
  int ch_man_left_;
  int ch_man_right_;
  int ch_auto_left_;
  int ch_auto_right_;
};

}  // namespace protolink_drivers

#endif  // PROTOLINK_DRIVERS__RC_TO_MOTOR_CONTROL_HPP_
