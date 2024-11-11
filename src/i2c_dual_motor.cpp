#include "i2c_dual_motor.h"

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

I2cDualMotor::I2cDualMotor(const uint8_t i2c_address, TwoWire& wire) : i2c_address_(i2c_address), wire_(wire) {
  // do somethings
}

I2cDualMotor::ErrorCode I2cDualMotor::Init(const uint32_t frequency) {
  wire_.beginTransmission(i2c_address_);
  wire_.write(kMemAddrFrequency);
  wire_.write(reinterpret_cast<const uint8_t*>(&frequency), sizeof(frequency));
  return static_cast<ErrorCode>(wire_.endTransmission());
}

I2cDualMotor::ErrorCode I2cDualMotor::Pwm(const PwmChannel ch, uint16_t duty) {
  duty = min(kMaxPwmDuty, duty);
  wire_.beginTransmission(i2c_address_);
  wire_.write(kMemeAddrPwmDuty0 + (ch << 1));
  wire_.write(reinterpret_cast<const uint8_t*>(&duty), sizeof(duty));
  return static_cast<ErrorCode>(wire_.endTransmission());
}

}  // namespace em