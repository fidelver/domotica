#pragma once
#include "esphome/components/climate/climate_ir.h"

namespace esphome {
namespace climate_ir_aeha {

class AehaClimate : public climate::ClimateIR {
 public:
  void transmit_state() override;
  void set_address(uint16_t address) { address_ = address; }
  
 protected:
  uint16_t address_ = 0xC4D3;
};

}  // namespace climate_ir_aeha
}  // namespace esphome
