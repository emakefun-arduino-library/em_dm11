#include "dm11.h"

#include <Arduino.h>

namespace {
enum MemoryAddress : uint8_t {
  kMemeAddrPwmDuty0 = 0x50,
  kMemeAddrPwmDuty1 = 0x52,
  kMemeAddrPwmDuty2 = 0x54,
  kMemeAddrPwmDuty3 = 0x56,
  kMemAddrFrequency = 0x60,
};
}

Dm11::Dm11(const uint8_t i2c_address, TwoWire& wire) : i2c_address_(i2c_address), wire_(wire) {
}

Dm11::ErrorCode Dm11::Init(const uint16_t frequency_hz) {
  if (frequency_hz < kMinFrequencyHz || frequency_hz > kMaxFrequencyHz) {
    return kInvalidParameter;
  }

  wire_.beginTransmission(i2c_address_);
  wire_.write(kMemAddrFrequency);
  wire_.write(reinterpret_cast<const uint8_t*>(&frequency_hz), sizeof(frequency_hz));
  return static_cast<ErrorCode>(wire_.endTransmission());
}

Dm11::ErrorCode Dm11::Pwm(const uint8_t ch, uint16_t duty) {
  if (ch >= kPwmChannelNum) {
    return kInvalidParameter;
  }
  duty = min(kMaxPwmDuty, duty);
  wire_.beginTransmission(i2c_address_);
  wire_.write(kMemeAddrPwmDuty0 + (ch << 1));
  wire_.write(reinterpret_cast<const uint8_t*>(&duty), sizeof(duty));
  return static_cast<ErrorCode>(wire_.endTransmission());
}
