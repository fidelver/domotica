# Componente ESPHome para LG AEHA (Protocolo Panasonic-like)

## Configuración en YAML
```yaml
climate:
  - platform: climate_ir_aeha
    name: "LG AEHA AC"
    address: 0xC4D3  # Opcional
    transmitter_id: ir_transmitter
