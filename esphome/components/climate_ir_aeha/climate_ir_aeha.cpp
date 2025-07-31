#include "climate_ir_aeha.h"
#include "esphome/components/remote_base/remote_base.h"

namespace esphome {
namespace climate_ir_aeha {

void AehaClimate::transmit_state() {
  uint8_t data[12] = {
    static_cast<uint8_t>(address_ >> 8),
    static_cast<uint8_t>(address_ & 0xFF),
    0x64, 0x80, 0x00, 0x26, 0xC0, 0xF0, 0xA0, 0x00, 0x00, 0x00
  };
  
  // Ajusta según modo/temperatura (ejemplo para COOL 24°C)
  data[4] = (this->mode == climate::CLIMATE_MODE_COOL) ? 0x00 : 0x08;
  data[5] = static_cast<uint8_t>(this->target_temperature);
  
  // Checksum (suma de bytes 0-10)
  uint8_t sum = 0;
  for (int i = 0; i < 11; i++) sum += data[i];
  data[11] = sum;

  // Envía la señal IR
  auto transmit = this->transmitter_->transmit();
  auto data_struct = transmit.get_data();
  data_struct->set_carrier_frequency(38000);
  // ... (código de transmisión completo como en tu archivo)
}

}  // namespace climate_ir_aeha
}  // namespace esphome
