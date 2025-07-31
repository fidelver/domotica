#pragma once
#include "esphome/components/climate/climate.h"
#include "esphome/components/remote_base/remote_base.h"

namespace esphome {
namespace climate_ir_aeha {

class AehaClimate : public climate::Climate, public Component {
 public:
  void setup() override;
  void control(const climate::ClimateCall &call) override;
  void set_transmitter(remote_base::RemoteTransmitter *transmitter) { transmitter_ = transmitter; }
  void set_address(uint16_t address) { address_ = address; }

 protected:
  void transmit_state_();
  uint8_t calculate_checksum_(const uint8_t *data, size_t length);
  remote_base::RemoteTransmitter *transmitter_;
  uint16_t address_ = 0xC4D3;  // Default LG AEHA address
  bool turbo_ = false;
};

}  // namespace climate_ir_aeha
}  // namespace esphome
