#include "climate_ir_aeha.h"
#include <IRremoteESP8266.h>

namespace esphome {
namespace climate_ir_aeha {

void AehaClimate::transmit_state_() {
  uint8_t data[12] = {
    static_cast<uint8_t>(address_ >> 8),  // 0xC4
    static_cast<uint8_t>(address_ & 0xFF), // 0xD3
    0x64, 0x80,                           // Bytes fijos
    turbo_ ? 0x02 : 0x00,                 // Turbo ON/OFF
    static_cast<uint8_t>(this->target_temperature),  // Temp
    turbo_ ? 0xC2 : 0xC0,                // Fan + Turbo
    0xF0, 0xA0, 0x00, 0x00, 0x00         // Resto de bytes
  };

  data[11] = calculate_checksum_(data, 11);  // Checksum

  auto transmit = this->transmitter_->transmit();
  auto *data_struct = transmit.get_data();
  data_struct->set_carrier_frequency(38000);

  for (uint8_t byte : data) {
    for (int8_t i = 7; i >= 0; i--) {
      data_struct->mark(600);
      data_struct->space((byte & (1 << i)) ? 1600 : 600);
    }
  }
  data_struct->mark(600);
  transmit.perform();
}

uint8_t AehaClimate::calculate_checksum_(const uint8_t *data, size_t length) {
  uint8_t sum = 0;
  for (size_t i = 0; i < length; i++) sum += data[i];
  return sum;
}

}  // namespace climate_ir_aeha
}  // namespace esphome
