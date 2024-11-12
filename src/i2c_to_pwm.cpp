#include "i2c_to_pwm.h"

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

namespace em {

I2cToPwm::I2cToPwm(const uint8_t i2c_address, TwoWire& wire) : i2c_address_(i2c_address), wire_(wire) {
}

I2cToPwm::ErrorCode I2cToPwm::Init(const uint16_t frequency) {
  if (frequency == 0 || kMaxFrequencyHz < frequency) {
    return kInvalidParameter;
  }

  wire_.beginTransmission(i2c_address_);
  wire_.write(kMemAddrFrequency);
  wire_.write(reinterpret_cast<const uint8_t*>(&frequency), sizeof(frequency));
  return static_cast<ErrorCode>(wire_.endTransmission());
}

I2cToPwm::ErrorCode I2cToPwm::Pwm(const uint8_t ch, uint16_t duty) {
  if (ch >= kPwmChannelNum) {
    return kInvalidParameter;
  }
  duty = min(kMaxPwmDuty, duty);
  wire_.beginTransmission(i2c_address_);
  wire_.write(kMemeAddrPwmDuty0 + (ch << 1));
  wire_.write(reinterpret_cast<const uint8_t*>(&duty), sizeof(duty));
  return static_cast<ErrorCode>(wire_.endTransmission());
}

}  // namespace em