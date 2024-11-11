/**
 * @example i2c_dual_motor.ino
 */

#include "i2c_dual_motor.h"

#define INFINITE_LOOP_ON_FAILURE InfiniteLoopOnFailure(__FUNCTION__, __LINE__)

namespace {

em::I2cDualMotor g_i2c_dual_motor;

void InfiniteLoopOnFailure(const char* function, const uint32_t line_number) {
  Serial.println(String(F("entering an infinite loop due to failure in ")) + function + F(", at line number: ") + line_number);
  while (true) {
    yield();
  }
}

}  // namespace

void setup() {
  Serial.begin(115200);
  Serial.println(F("setup"));
  Serial.println(String(F("i2c dual motor lib version: ")) + em::I2cDualMotor::Version());

  Wire.begin();

  const auto ret = g_i2c_dual_motor.Init();

  if (em::I2cDualMotor::kOK == ret) {
    Serial.println(F("i2c dual motor initialization successful"));
  } else {
    Serial.print(F("i2c dual motor initialization failed: "));
    Serial.println(ret);
    INFINITE_LOOP_ON_FAILURE;
  }

  Serial.println(F("setup successful"));
}

void loop() {
  g_i2c_dual_motor.Pwm(em::I2cDualMotor::kCh0, 0);
  g_i2c_dual_motor.Pwm(em::I2cDualMotor::kCh1, 4095);
  g_i2c_dual_motor.Pwm(em::I2cDualMotor::kCh2, 0);
  g_i2c_dual_motor.Pwm(em::I2cDualMotor::kCh3, 4095);
  Serial.println("F");
  delay(1000);

  g_i2c_dual_motor.Pwm(em::I2cDualMotor::kCh0, 4095);
  g_i2c_dual_motor.Pwm(em::I2cDualMotor::kCh1, 0);
  g_i2c_dual_motor.Pwm(em::I2cDualMotor::kCh2, 4095);
  g_i2c_dual_motor.Pwm(em::I2cDualMotor::kCh3, 0);
  Serial.println("B");
  delay(1000);
}
