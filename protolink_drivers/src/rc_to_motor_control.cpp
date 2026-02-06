#include "protolink_drivers/rc_to_motor_control.hpp"
#include <rclcpp_components/register_node_macro.hpp>

namespace protolink_drivers
{
RcToMotorControl::RcToMotorControl(const rclcpp::NodeOptions & options)
: Node("rc_to_motor_control", options)
{
  // --- パラメータ取得 (デフォルト値は環境に合わせて調整してください) ---
  ch_switch_    = declare_parameter<int>("channel_switch", 4);       // Ch5
  ch_man_left_  = declare_parameter<int>("channel_manual_left", 0);  // Ch1
  ch_man_right_ = declare_parameter<int>("channel_manual_right", 2); // Ch3
  ch_auto_left_ = declare_parameter<int>("channel_auto_left", 5);    // Ch6 (Auto指令用)
  ch_auto_right_= declare_parameter<int>("channel_auto_right", 6);   // Ch7 (Auto指令用)

auto qos = rclcpp::QoS(rclcpp::KeepLast(1));//.best_effort().durability_volatile();
qos.reliable();
qos.durability_volatile();

  // --- パブリッシャー作成 ---
  // 手動ドライバ (8888) へ
  pub_man_left_  = create_publisher<hardware_communication_msgs::msg::MotorControl>("manual/left/command", qos);
  pub_man_right_ = create_publisher<hardware_communication_msgs::msg::MotorControl>("manual/right/command", qos);
  
  // 自動ドライバ (8889) へ
  pub_auto_left_  = create_publisher<hardware_communication_msgs::msg::MotorControl>("auto/left/command", qos);
  pub_auto_right_ = create_publisher<hardware_communication_msgs::msg::MotorControl>("auto/right/command", qos);
  // --- サブスクライバー ---
  sub_rc_ = create_subscription<mavros_msgs::msg::RCOut>(
    "mavros/rc/out", //rclcpp::SensorDataQoS(),
    qos,
    [=](const mavros_msgs::msg::RCOut::SharedPtr msg) {
      
      // データ長チェック
      size_t max_idx = std::max({ch_switch_, ch_man_left_, ch_man_right_, ch_auto_left_, ch_auto_right_});
      if (msg->channels.size() <= max_idx) return;

      // 1. モード判定 (スイッチの状態)
      // スイッチ < 1300: Manual (mode=1)
      // スイッチ > 1700: Auto   (mode=0)
      // その他: Disable (mode=2)
      int current_mode = 2; 
      uint16_t sw_val = msg->channels[ch_switch_];
      
      if (sw_val < 1300) current_mode = 1;      
      else if (sw_val > 1700) current_mode = 0; 

      // ----------------------------------------------------
      // 2. 手動ドライバ (Port 8888) への送信
      // ----------------------------------------------------
      // 手動ドライバには常に「現在のモード」と「手動スティックの値」を送る
      {
          hardware_communication_msgs::msg::MotorControl msg_l, msg_r;
          
          msg_l.mode = current_mode;
          msg_r.mode = current_mode;
          msg_l.motor_enable = true; 
          msg_r.motor_enable = true;

          // PWM -> Speed計算
          double raw_l = (static_cast<double>(msg->channels[ch_man_left_]) - 1500.0) / 400.0;
          double raw_r = (static_cast<double>(msg->channels[ch_man_right_]) - 1500.0) / 400.0;
          
          msg_l.motor_speed = std::clamp(raw_l, -1.0, 1.0);
          msg_r.motor_speed = std::clamp(raw_r, -1.0, 1.0);

          pub_man_left_->publish(msg_l);
          pub_man_right_->publish(msg_r);
      }

      // ----------------------------------------------------
      // 3. 自動ドライバ (Port 8889) への送信
      // ----------------------------------------------------
      // 自動ドライバには、常に mode=0 (Auto) として「自動用CHの値」を送る
      // (Teensy側で Manualモード時は無視されるため安全)
      {
          hardware_communication_msgs::msg::MotorControl msg_l, msg_r;
          
          msg_l.mode = 0; // 常にAuto扱い
          msg_r.mode = 0;
          msg_l.motor_enable = true;
          msg_r.motor_enable = true;

          // 自動用チャンネルの計算
          double raw_l = (static_cast<double>(msg->channels[ch_auto_left_]) - 1500.0) / 400.0;
          double raw_r = (static_cast<double>(msg->channels[ch_auto_right_]) - 1500.0) / 400.0;

          msg_l.motor_speed = std::clamp(raw_l, -1.0, 1.0);
          msg_r.motor_speed = std::clamp(raw_r, -1.0, 1.0);

          pub_auto_left_->publish(msg_l);
          pub_auto_right_->publish(msg_r);
      }
    });
}
} // namespace
RCLCPP_COMPONENTS_REGISTER_NODE(protolink_drivers::RcToMotorControl)
